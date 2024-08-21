#include "../../include/csapp.h"

int main(int argc, char** argv)
{
  struct stat file_stat;
  char* type, *readok;
  int fd;

  if (argc != 2)
  {
    fprintf(stderr, "Invalid argument(s).\n");
    return 0;
  }

  fd = atoi(argv[1]);
  if(fstat(fd, &file_stat))
  {
    fprintf(stderr, "Invalid file descriptor.\n");
    return 0;
  }

  if (S_ISREG(file_stat.st_mode))
    type = "regular";
  else if (S_ISDIR(file_stat.st_mode))
    type = "directory";
  else
    type = "other";

  readok = file_stat.st_mode & S_IRUSR ? "yes" : "no";

  printf("type: %s, read: %s\n", type, readok);

  return 0;
}
