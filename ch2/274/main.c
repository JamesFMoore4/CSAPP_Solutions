#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y)
{
  int result = x - y;
  return result <= x;
}

int main(void)
{
  printf("%d\n", tsub_ok(INT_MIN, 1));
  return 0;
}
