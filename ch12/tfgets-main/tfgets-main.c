#include "../../include/csapp.h"

char* tfgets(char* s, int size, FILE* stream);

int main()
{
  char buf[MAXLINE];

  if (!tfgets(buf, MAXLINE, stdin))
    printf("BOOM!\n");
  else
    printf("%s", buf);

  exit(0);
}