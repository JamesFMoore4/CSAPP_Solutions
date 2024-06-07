#include <stdio.h>
#include <limits.h>

int main(void)
{
  int x = 1;

  // K = 17
  printf("%d\n", (x << 4) + x);
  // K = -7
  printf("%d\n", x - (x << 3));
  // K = 60
  printf("%d\n", (x << 6) - (x << 2));
  // K = -112
  printf("%d\n", (x << 4) - (x << 7));

  
  return 0;
}
