#include <stdio.h>
#include <limits.h>

int any_odd_one(unsigned x)
{
  return !!(x & 0xAAAAAAAA);
}

int main(void)
{
  printf("%d", any_odd_one(1));
  return 0;
}
