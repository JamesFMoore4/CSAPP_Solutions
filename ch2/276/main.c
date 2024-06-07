#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


void* mycalloc(size_t nmemb, size_t size)
{
  size_t result = nmemb * size;
  if (!nmemb || !size || result / nmemb != size)
    return NULL;
  
  void* ptr = malloc(nmemb * size);
  memset(ptr, 0, nmemb * size);
  return ptr;
}


int main(void)
{
  return 0;
}
