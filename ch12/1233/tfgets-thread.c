#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int finished;

typedef struct
{
  char* arg1;
  int arg2;
  FILE* arg3;
} thread_arg;

static void* tfgets_thread(void* arg)
{
  thread_arg* args = (thread_arg*)arg;
  fgets(args->arg1, args->arg2, args->arg3);
  finished = 1;
}

static void* timer_thread(void* arg)
{
  pthread_t tid = (pthread_t)arg;
  pthread_detach(pthread_self());
  sleep(5);
  pthread_cancel(tid);
}

char* tfgets(char* s, int size, FILE* stream)
{
  pthread_t tid, timer_tid;
  thread_arg args;

  finished = 0;
  args.arg1 = s;
  args.arg2 = size;
  args.arg3 = stream;

  pthread_create(&tid, NULL, tfgets_thread, (void*)&args);
  pthread_create(&timer_tid, NULL, timer_thread, (void*)tid);
  pthread_join(tid, NULL);

  if (finished)
    return s;
  
  return NULL;
}
