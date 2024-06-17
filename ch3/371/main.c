#include <stdio.h>

void good_echo()
{
  char buf[256];
  if (!fgets(buf, sizeof(buf), stdin))
    return;
  puts(buf);
}

int main(void)
{
  good_echo();
  return 0;
}
