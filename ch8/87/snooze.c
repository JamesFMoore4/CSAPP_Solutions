#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig)
{
  return;
}

unsigned snooze(unsigned secs)
{
  unsigned secs_left = sleep(secs);
  printf("Slept for %i of %i secs.\n", secs - secs_left, secs);
  return secs_left;
}

int main(int argc, char** argv)
{
  
  if (argc != 2)
  {
    fprintf(stderr, "Invalid arguments.\n");
    exit(0);
  }

  if (signal(SIGINT, sigint_handler) == SIG_ERR)
  {
    fprintf(stderr, "Signal Error.\n");
    exit(0);
  }
    
  int secs;
  if (secs = atoi(argv[1]))
  {
    if (secs < 0)
    {
      fprintf(stderr, "Invalid argument.\n");
      exit(0);
    }
    else
      snooze((unsigned)secs);
  }
  else
    fprintf(stderr, "Invalid argument.\n");
  
  return 0;
}
