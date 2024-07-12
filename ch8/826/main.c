#include "csapp.h"
#include "shell.h"
#include "jobs.h"

extern char cmdline[MAXLINE];
extern job_lst* jlst;
extern int fgpgid;

int main(void)
{
  jlst_init();

  signal(SIGTSTP, stop);
  signal(SIGINT, intr);
  signal(SIGCHLD, reap);
  
  while (1)
  {
    fgpgid = 0;
    printf("> ");
    Fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin))
      exit(0);
    eval();
  }
}

