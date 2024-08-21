#include "../../include/csapp.h"

int main(void)
{
  int n;
  char buf[MAXBUF];

  while (n = rio_readn(0, buf, MAXBUF))
    rio_writen(1, buf, n);

  return 0;
}
