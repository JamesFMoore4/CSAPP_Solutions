#include <stdio.h>
#include <limits.h>

int int_size_is_32()
{
  int set_msb = 1 << 31;
  return !(set_msb & (set_msb << 1));
}

int int_size_is_32_v2()
{
  int set_msb = 1 << 15;
  set_msb <<= 15;
  set_msb <<= 1;
  return !(set_msb & (set_msb << 1));
}


int main(void)
{
  
  return 0;
}
