#include "csapp.h"
#include "jobs.h"
#define MAXARGS 128

extern job_lst* jlst;
static pid_t fgpgid = 0;
char fg_cmd[MAXLINE];

void eval(char* cmdline);
int parseline(char* buf, char** argv);
int builtin_command(char** argv);
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void cont_proc(char** argv, int g);
void reap(int sig);

int main(void)
{
  char cmdline[MAXLINE];

  signal(SIGINT, sigint_handler);
  signal(SIGTSTP, sigtstp_handler);
  signal(SIGCHLD, reap);

  jlst_init();
  
  while (1)
  {
    printf("> ");
    Fgets(cmdline, MAXLINE, stdin);
    strcpy(fg_cmd, cmdline);
    if (feof(stdin))
      exit(0);

    eval(cmdline);
  }
}

void eval(char* cmdline)
{
  char* argv[MAXARGS];
  char buf[MAXLINE];
  int bg;
  pid_t pid;

  strcpy(buf, cmdline);
  bg = parseline(buf, argv);
  if (!argv[0])
    return;

  if (!builtin_command(argv))
  {
    if (!(pid = Fork()))
    {
      if (execve(argv[0], argv, environ) < 0)
      {
	printf("%s: Command not found.\n", argv[0]);
	exit(0);
      }
    }
    
    if (!bg)
    {
      Setpgid(pid, 0);
      fgpgid = pid;
      if (waitpid(pid, NULL, WUNTRACED) < 0)
	unix_error("waitfg: waitpid error");
      fgpgid = 0;
    }
    else
    {
      printf("%d %s", pid, cmdline);
      jlst_add(pid, cmdline);
      Setpgid(pid, 0);
    }
  }
}

int builtin_command(char** argv)
{
  if (!strcmp(argv[0], "quit"))
  {
    jlst_del();
    exit(0);  
  }
  if (!strcmp(argv[0], "&"))
    return 1;
  if (!strcmp(argv[0], "jobs"))
  {
    jlst_print();
    return 1;
  }
  if (!strcmp(argv[0], "bg"))
  {
    cont_proc(argv, 0);
    return 1;
  }
  if (!strcmp(argv[0], "fg"))
  {
    cont_proc(argv, 1);
    return 1;
  }
  return 0;
}

int parseline(char* buf, char** argv)
{
  char* delim;
  int argc, bg;

  buf[strlen(buf)-1] = ' ';
  while (*buf && (*buf == ' '))
    buf++;

  argc = 0;
  while ((delim = strchr(buf, ' ')))
  {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' '))
      buf++;
  }
  argv[argc] = NULL;

  if (!argc)
    return 1;

  if ((bg = (*argv[argc-1] == '&')))
    argv[--argc] = NULL;

  return bg;
}

void sigint_handler(int sig)
{
  if (fgpgid > 0)
  {
    Kill(-fgpgid, SIGINT);
    jlst_rem(fgpgid);
  }
}

void sigtstp_handler(int sig)
{
  if (fgpgid > 0)
  {
    Kill(-fgpgid, SIGTSTP);
    jlst_add(fgpgid, fg_cmd);
    (jlst_getp(fgpgid))->stat = STOPPED;
  }
}

void cont_proc(char** argv, int g)
{
  int id, proc_status;
  job* jb;
    
  if (!argv[1])
  {
    char* usg_str = g ? "Usage: fg %(jid) OR fg (pid)" : "Usage: bg %(jid) OR bg (pid)";
    printf("%s\n", usg_str);
  }
  else if (argv[1][0] == '%')
  {
    if (!(id = atoi(argv[1] + 1)))
      printf("Invalid argument: %s\n", argv[1]);
    else
    {
      jb = jlst_get(id);
      if (jb)
      {
       jb->stat = RUNNING;
       Kill(jb->pid, SIGCONT);
       if (g)
       {
	 fgpgid = jb->pid;
	 Waitpid(jb->pid, &proc_status, WUNTRACED);
	 fgpgid = 0;
       }
	 
      }
      else
	printf("Job not found\n");
    }
  }
  else
  {
    if (!(id = atoi(argv[1])))
      printf("Invalid argument: %s\n", argv[1]);
    else
    {
      jb = jlst_getp(id);
      if (jb)
      {
       jb->stat = RUNNING;
       Kill(jb->pid, SIGCONT);
       if (g)
       {
	 fgpgid = jb->pid;
	 Waitpid(jb->pid, &proc_status, WUNTRACED);
	 fgpgid = 0;
       }
	 
      }
      else
	printf("Job not found\n");
    }
  }
}

void reap(int sig)
{
  int proc_stat, olderrno = errno;
  pid_t proc_id;

  while ((proc_id = waitpid(-1, &proc_stat, 0)) > 0)
  {
    jlst_rem(proc_id);
    if (WIFSIGNALED(proc_stat))
    {
      char buf[128];
      sprintf(buf, "Process %d terminated by signal %d", proc_id, WTERMSIG(proc_stat));
      psignal(WTERMSIG(proc_stat), buf);
    }
  }

  if (errno != ECHILD)
    Sio_error("waitpid error");
  Sleep(1);
  errno = olderrno;
}
