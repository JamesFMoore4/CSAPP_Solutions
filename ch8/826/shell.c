#include "shell.h"
#define MAXARGS 128

char cmdline[MAXLINE];
int fgpgid = 0;
extern job_lst* jlst;

void eval()
{
  char* argv[MAXARGS];
  char buf[MAXLINE];
  int bg;
  pid_t pid;
  fgpgid = 0;

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

    fgpgid = setpgid(pid, 0);
    
    if (!bg)
    {
      int stat;
      waitpid(pid, &stat, WUNTRACED);
      print_if_signaled(stat, pid);
    }
    else
    {
      printf("%d %s", pid, cmdline);
      sigset_t prev_mask = block_signals();
      jlst_add(pid, cmdline, RUNNING);
      unblock_signals(prev_mask);
    }
  }
  return;
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
  if (!strcmp(argv[0], "bg"))
  {
    proc_cont(argv, 1);
    return 1;
  }
  if (!strcmp(argv[0], "fg"))
  {
    proc_cont(argv, 0);
    return 1;
  }
  if (!strcmp(argv[0], "jobs"))
  {
    jlst_print();
    return 1;
  }
  return 0;
}

int parseline(char* buf, char** argv)
{
  char* delim;
  int argc;
  int bg;

  buf[strlen(buf) - 1] = ' ';
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

void proc_cont(char** argv, int bg)
{
  if (!argv[1])
  {
    char* usg_str = bg ? "Usage: bg %(jid) OR bg (pid)\n" : "Usage: fg %(jid) OR fg (pid)\n";
    printf("%s", usg_str);
    return;
  }

  int is_jid = (argv[1][0] == '%');
  int id = is_jid ? atoi(argv[1] + 1) : atoi(argv[1]);

  if (!id)
  {
    printf("Invalid argument.\n");
    return;
  }

  sigset_t prev_mask = block_signals();
  
  job* jb = is_jid ? jlst_get(id) : jlst_getp(id);

  if (!jb)
  {
    unblock_signals(prev_mask);
    printf("Job not found.\n");
    return;
  }

  Kill(jb->pid, SIGCONT);
  jb->stat = RUNNING;

  if (bg)
  {
    unblock_signals(prev_mask);
    return;
  }

  fgpgid = jb->pid;
  jlst_rem(jb->pid);
  unblock_signals(prev_mask);

  int stat;
  waitpid(fgpgid, &stat, WUNTRACED);
  print_if_signaled(stat, fgpgid);
}

sigset_t block_signals()
{
  sigset_t mask, prev_mask;
    
  Sigfillset(&mask);
  Sigprocmask(SIG_BLOCK, &mask, &prev_mask);

  return prev_mask;
}

void unblock_signals(sigset_t prev_mask)
{
  Sigprocmask(SIG_SETMASK, &prev_mask, NULL);
}

void print_if_signaled(int stat, pid_t pid)
{
  if (WIFSIGNALED(stat))
  {
    char err_buf[128];
    sprintf(err_buf, "Child %d terminated by signal %d", pid, WTERMSIG(stat));
    psignal(WTERMSIG(stat), err_buf);
  }
}

void stop(int sig)
{
  if (fgpgid)
  {
    Kill(-fgpgid, SIGTSTP);
    
    sigset_t prev_mask = block_signals();

    jlst_add(fgpgid, cmdline, STOPPED);
    
    unblock_signals(prev_mask);
  }
}

void intr(int sig)
{
  if (fgpgid)
    Kill(-fgpgid, SIGINT);
}

void reap(int sig)
{
  int olderrno = errno, stat;
  sigset_t prev_mask;
  pid_t pid;
  
  while ((pid = waitpid(-1, &stat, 0)) > 0)
  {
    prev_mask = block_signals();
    jlst_rem(pid);
    unblock_signals(prev_mask);
    
    print_if_signaled(stat, pid);
  }
  if (errno != ECHILD)
    Sio_error("waitpid error");
  errno = olderrno;
}
