#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>


char* tfgets(char* s, int size, FILE* stream)
{
  fd_set read_set;
  struct timeval time;

  FD_ZERO(&read_set);
  FD_SET(0, &read_set);
  time.tv_sec = 5;
  time.tv_usec = 0;
 
  select(1, &read_set, NULL, NULL, &time);

  if (FD_ISSET(0, &read_set))
  {
    fgets(s, size, stream);
    return s;
  }
  else
    return NULL;
}
