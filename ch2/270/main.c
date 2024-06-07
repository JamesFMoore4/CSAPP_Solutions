#include <stdio.h>
#include <limits.h>

int fits_bits(int x, int n)
{
  int mask = ((1 << n - 1) - 1) << 1 | 1;
  mask &= x;
  return x == mask;
}

int main(void)
{
  printf("%d", fits_bits(INT_MIN, 32));
  return 0;
}
