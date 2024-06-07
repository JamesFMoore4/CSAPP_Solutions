#include <stdio.h>
#include <limits.h>

unsigned rotate_left(unsigned x, int n)
{
  int mask_shift = (sizeof(int) << 3) - n;
  unsigned mask = ((1 << n - 1) - 1) << 1 | 1; // Least significant n bits set to 1
  mask <<= mask_shift; // Mask is shifted to most sig n positions
  mask &= x; // Most significant n positions of x are saved in mask
  mask >>= mask_shift; // Mask shifted back to first n positions
  x <<= n; // x shifted left by n bits
  return x | mask; // Least sig n bits of x set to mask
}

int main(void)
{
  printf("%.8x\n", rotate_left(0x00FF0000, 0));
  return 0;
}
