#include <stdio.h>
#include <limits.h>

int leftmost_one(unsigned x)
{
  // Slightly improved version of the following solution:
  /* https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.66/ */
  
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;

  return (x >> 1) ^ x;
}


int main(void)
{
  printf("%.8x", leftmost_one(~0 & 0x0F000000));
  return 0;
}
