#include <stdio.h>

// xp in %rdi, yp in %rsi, zp in %rdx
void decode1(long* xp, long* yp, long* zp)
{
  long x = *xp; // %r8
  long y = *yp; // %rcx
  long z = *zp; // %rax

  *yp = x;
  *zp = y;
  *xp = z;
}

