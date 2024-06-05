#include <stdio.h>

int main(void)
{
  int x = 0x89ABCDEF, y = 0x76543210;
  printf("%x", (x & 0xFF) | (y >> 8 << 8));
  return 0;
}
