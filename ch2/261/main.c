#include <stdio.h>

int main(void)
{

  int x = 0;

  // !! converts any nonzero integer value into a 1
  printf("%d\n", !!(x & ~0));
  printf("%d\n", !!(x ^ ~0));
  printf("%d\n", !!(x & 0xFF));
  int shift_value = (sizeof(int) - 1) << 3;
  printf("%d\n", !!(((unsigned)x >> shift_value) ^ 0xFF));

  return 0;
}
