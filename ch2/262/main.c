#include <stdio.h>

int int_shifts_are_arithmetic(void)
{
  return !!(-1 >> (sizeof(int) << 3));
}

int main(void)
{
  printf("%d\n", int_shifts_are_arithmetic());
  return 0;
}

