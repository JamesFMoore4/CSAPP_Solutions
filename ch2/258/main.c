#include <stdio.h>

typedef unsigned char* byte_pointer;

int is_little_endian(void)
{
  int x = 1;
  byte_pointer first_byte = (byte_pointer) &x;
  return *first_byte == 1;
}

int main(void)
{
  printf("%d", is_little_endian());
  return 0;
}
