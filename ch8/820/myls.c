#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** env)
{
  if (execve("/bin/ls", argv, env) < 0)
    fprintf(stderr, "Command not found");
  exit(1);
}
