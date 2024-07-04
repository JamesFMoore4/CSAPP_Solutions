#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 2

int main(void)
{
  int status, i;
  pid_t pid;

  for (i = 0; i < N; i++)
    if (!(pid = fork()))
      raise(SIGSEGV);

  while ((pid = waitpid(-1, &status, 0)) > 0)
  {
    if (WIFEXITED(status))
      printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
    {
      char buf[128];
      sprintf(buf, "child %d terminated by signal %d", pid, WTERMSIG(status));
      psignal(WTERMSIG(status), buf);
    } 
  }

  if (errno != ECHILD)
    fprintf(stderr, "waitpid error.");

  exit(0);
}
