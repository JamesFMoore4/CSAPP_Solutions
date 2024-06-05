#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
  int i;
  for (i = 0; i < len; i++)
      printf("%.2x ", start[i]);    
  printf("\n");
}

void show_short(short x)
{
  show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x)
{
  show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x)
{
  show_bytes((byte_pointer) &x, sizeof(double));
}

int main(void)
{

  show_short((short) 16);
  show_long((long) 16);
  show_double(16.75);

  
  return 0;
}
