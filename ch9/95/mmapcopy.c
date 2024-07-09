#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{

  if (argc != 2)
  {
    fprintf(stderr, "Usage: mmapcopy <filename>\n");
    exit(0);
  }

  int fd;
  struct stat file_stat;
  
  if ((fd = open(argv[1], 0)) < 0)
  {
    fprintf(stderr, "File not found\n");
    exit(0);
  }
  
  fstat(fd, &file_stat);
  char* ptr = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  write(1, ptr, file_stat.st_size);
  
  return 0;
}
