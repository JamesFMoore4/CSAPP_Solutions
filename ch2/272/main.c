#include <stdio.h>
#include <limits.h>
#include <string.h>

void copy_int(int val, void* buf, int maxbytes)
{
  if (maxbytes >= (int) sizeof(val))  // The comparison must be changed. sizeof(val) is cast to an int to prevent overflow given a negative value for maxbytes
    memcpy(buf, (void*) &val, sizeof(val));
}

