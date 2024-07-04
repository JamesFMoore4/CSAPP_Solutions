#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int mysystem(char* command)
{
  char* argv[] = {"/bin/sh", "-c", command, NULL};
  int* status;
 
  if (!fork())
  {
    if (execve("/bin/sh", argv, NULL) < 0)
    {
      fprintf(stderr, "Execve error.");
      exit(0);
    }
  }
  else
  {
    if (wait(status) < 0)
    {
      fprintf(stderr, "Wait error.");
      exit(0);
    }
  }
  
  return *status;
}


