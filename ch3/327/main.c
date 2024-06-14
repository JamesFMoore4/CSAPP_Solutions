#include <stdio.h>

// jump-to-middle
void fibonacci(int n)
{
  int i = 0, fib1 = 0, fib2 = 1;
  goto test;
 loop:
  printf("%d\n", fib1);
  fib2 += fib1;
  fib1 = fib2 - fib1;
  i++;
 test:
  if (i <= n)
    goto loop;
}

// guarded-do
void fibonacci_gd(int n)
{
  int i = 0, fib1 = 0, fib2 = 1;
  if (n < 0)
    goto done;
 loop:
  printf("%d\n", fib1);
  fib2 += fib1;
  fib1 = fib2 - fib1;
  i++;
  if (i <= n) goto loop;
 done:
}
