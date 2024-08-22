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

  uint16_t arg = (uint16_t)atoi(argv[1]);
  printf("0x%x\n", ntohs(arg));
}
