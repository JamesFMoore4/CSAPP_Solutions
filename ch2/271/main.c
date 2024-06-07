#include <stdio.h>
#include <limits.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
  //return (char) (word >> (bytenum << 3)); This also seems to work
   return (int) word << ((3 - bytenum) << 3) >> 24;  // Left shift the selected byte into the leftmost position, and then arithmetic right shift it to the rightmost position in order to preserve the correct sign
}

int main(void)
{
  printf("%.8x\n", xbyte(0x000F0000, 2));
  return 0;
}
