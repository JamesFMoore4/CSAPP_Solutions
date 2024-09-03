#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <pthread.h>

static jmp_buf buf;
static volatile sig_atomic_t flag;
static pid_t child_proc;

void chld_handler(int sig)
{
  while (waitpid(-1, NULL, 0) > 0);
  if (!flag)
    longjmp(buf, 1);
  return;
}

static void handler_init(void)
{
  signal(SIGCHLD, chld_handler);
}

char* tfgets(char* s, int size, FILE* stream)
{
  static pthread_once_t once;

  once = PTHREAD_ONCE_INIT;
  pthread_once(&once, handler_init);
  flag = 0;

  if (!fork())
  {
    sleep(5);
    exit(0);
  }

  if (!setjmp(buf))
  {
    fgets(s, size, stream);
    flag = 1;
    return s;
  }
  else
    return NULL;
}
