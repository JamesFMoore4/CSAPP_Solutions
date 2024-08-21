#include "../../include/csapp.h"

int main(int argc, char** argv)
{
  int n, infile = -1;
  rio_t rio;
  char buf[MAXLINE];

  if (argc > 2)
  {
    fprintf(stderr, "Invalid arguments.\n");
    return 0;
  }
  else if (argc == 2)
  {
    if ((infile = open(argv[1], O_RDONLY, 0)) == -1)
    {
      fprintf(stderr, "File '%s' not found.\n", argv[1]);
      return 0;
    }
    dup2(infile, STDIN_FILENO);
  }

  Rio_readinitb(&rio, STDIN_FILENO);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    Rio_writen(STDOUT_FILENO, buf, n);

  if (infile != -1)
    close(infile);

  return 0;
}
