#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <semaphore.h>
#include <pthread.h>

static sem_t mutex;

static void init_mutex(void)
{
  sem_init(&mutex, 0, 1);
}

struct hostent* gethostbyname_ts(const char* name)
{ 
  struct hostent* host;
  static pthread_once_t once;
  char** i, *temp;

  once = PTHREAD_ONCE_INIT;
  pthread_once(&once, init_mutex);

  sem_wait(&mutex);
  
  host = (struct hostent*)malloc(sizeof(struct hostent));
  memcpy(host, gethostbyname(name), sizeof(struct hostent));

  temp = malloc((strlen(host->h_name) + 1) * sizeof(char));
  strcpy(temp, host->h_name);
  host->h_name = temp;

  for (i = host->h_aliases; *i; i++)
  {
    temp = malloc((strlen(*i) + 1) * sizeof(char));
    strcpy(temp, *i);
    *i = temp;
  }

  for (i = host->h_addr_list; *i; i++)
  {
    temp = malloc((strlen(*i) + 1) * sizeof(char));
    strcpy(temp, *i);
    *i = temp;
  }
  
  sem_post(&mutex);
  return host;
}
