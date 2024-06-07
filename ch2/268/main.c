#include <stdio.h>
#include <limits.h>

int lower_one_mask(int n)
{
  int mask = (1 << (n - 1)) - 1;
  mask <<= 1;
  return mask | 1;
}

int main(void)
{
  printf("%.8x", lower_one_mask(32));
  return 0;
}
