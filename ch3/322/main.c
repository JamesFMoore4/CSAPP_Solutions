#include <stdio.h>
#include <inttypes.h>

int mult_ok(int x, int y)
{
  int result = x * y;
  return !x || result / x == y;
}


int fact_do(int n)
{
  int result = 1;
  do
  {
    if (!mult_ok(result, n))
      return 0;
    result *= n;
    n = n - 1;
  } while(n > 1);
  return result;
}

int64_t mult_ok_l(int64_t x, int64_t y)
{
  int64_t result = x * y;
  return !x || result / x == y;
}

int64_t fact_do_l(int64_t n)
{
  int64_t result = 1;
  do
  {
    if (!mult_ok_l(result, n))
      return 0;
    result *= n;
    n = n - 1;
  } while (n > 1);
  return result;
}

int main(void)
{
  int fact_14 = fact_do(14);
  if (fact_14)
    printf("%d\n", fact_14);
  else
    printf("Computation overflowed.\n");
  
  int64_t fact_14_l = fact_do_l(14);
  if (fact_14_l)
    printf("%d\n", fact_14_l);
  else
    printf("Computation overflowed.\n");
  
  return 0;
}
