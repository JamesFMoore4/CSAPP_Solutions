
int writecnt;
sem_t mutex, w, wrmutex;

void reader(void)
{
  while (1)
  {
    P(&w);

    /* read */

    V(&w);
  }
}

void writer(void)
{
  while (1)
  {
    P(&mutex);
    writecnt++;
    if (writecnt == 1)
      P(&w);
    V(&mutex);

    P(&wrmutex);

    /* write */

    V(&wrmutex);

    P(&mutex);
    writecnt--;
    if (!writecnt)
      V(&w);
    V(&mutex);
  }
}
