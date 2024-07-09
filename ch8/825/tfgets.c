#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf buf;
volatile sig_atomic_t flag;

void alrm_handlr(int sig)
{
  if (!flag)
    longjmp(buf, 1);
  return;
}

char* tfgets(char* s, int size, FILE* stream)
{
  flag = 0;
  signal(SIGALRM, alrm_handlr);
  alarm(5);
  
  if (!setjmp(buf))
  {
    fgets(s, size, stream);
    flag = 1;
    return s;
  }
  else
    return NULL; 
}

