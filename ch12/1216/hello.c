#include "../../include/csapp.h"

void* thread(void* vargp)
{
  printf("Hello, world!\n");
  return NULL;
}

int main(int argc, char** argv)
{

  pthread_t tid, *id_vector;
  int i, nthreads;
  
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <nthreads>\n", argv[0]);
    exit(0);
  }

  nthreads = atoi(argv[1]);
  id_vector = (pthread_t*) malloc(nthreads * sizeof(pthread_t));

  for (i = 0; i < nthreads; i++)
  {
    Pthread_create(&tid, NULL, thread, NULL);
    id_vector[i] = tid;
  }

  for (i = 0; i < nthreads; i++)
    Pthread_join(id_vector[i], NULL);

  free(id_vector);
  exit(0);
}
