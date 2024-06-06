#include <stdio.h>
#include <limits.h>

unsigned srl(unsigned x, int k)
{
  unsigned xsra = (int) x >> k;
  return xsra & ((1 << (8 * sizeof(int) - k)) - 1);
}

int sra(int x, int k)
{
  int xsrl = (unsigned) x >> k;
  int most_sig_bit = !!(x & INT_MIN);
  int mask = ((most_sig_bit)*((1<<k) - 1)) << (8 * sizeof(int) - k);
  return xsrl | mask;
  
}

int main(void)
{
  printf("%.8x\n", srl(UINT_MAX, 8));
  printf("%.8x\n", sra(-1, 8));
  return 0;

}
