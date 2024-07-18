#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
  struct stat statbuf;
  int fd = open("./hello.txt", O_RDWR);
  fstat(fd, &statbuf);

  void* buf = mmap(NULL, statbuf.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
  *(char*)buf = 'J';
  write(fd, buf, statbuf.st_size);

  close(fd);
  
  return 0;
}
