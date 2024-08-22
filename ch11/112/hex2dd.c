#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid arguments.\n");
    return 0;
  }
  
  int base = argv[1][0] == '0' && argv[1][1] == 'x' ? 0 : 16;
  uint16_t arg = (uint16_t)strtol(argv[1], NULL, base);
  printf("%u\n", htons(arg));

  return 0;
}
