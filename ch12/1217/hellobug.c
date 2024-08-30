#include "../../include/csapp.h"

void* thread(void* vargp)
{
  Sleep(1);
  printf("Hello, world!\n");
  exit(0);
}

int main()
{
  pthread_t tid;

  Pthread_create(&tid, NULL, thread, NULL);

  /* Bug can be fixed with either pthread_exit or pthread_join */
  Pthread_exit(NULL);
}
