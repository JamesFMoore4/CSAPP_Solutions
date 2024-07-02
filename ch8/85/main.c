#include <unistd.h>

unsigned int wakeup(unsigned int secs)
{
  int secs_left = sleep(secs);
  printf("Woke up at %i seconds\n", secs - secs_left);
  return secs_left;
}
