#include <stdio.h>

typedef unsigned char* byte_pointer;

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
  byte_pointer byte = ((byte_pointer) &x) + i;
  *byte = b;
  return x;
}

int main(void)
{
  printf("%x", replace_byte(0x12345678, 0, 0xAB));
  return 0;
}
