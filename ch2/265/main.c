#include <stdio.h>
#include <limits.h>

int odd_ones(unsigned x)
{
  /* https://stackoverflow.com/questions/9133279/bitparity-finding-odd-number-of-bits-in-an-integer/9133406#9133406 */
  // Not my solution...

  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  x &= 0x1;
  return x;

int main(void)
{
  printf("%d\n", odd_ones(10));
  printf("%d", odd_ones(1));
  return 0;
}
