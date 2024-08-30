int readcnt, should_read;
sem_t mutex, mutex2, w;

void reader(void)
{
  while (1)
  {
    P(&mutex);
    readcnt++;
    if (readcnt == 1)
      P(&w);
    V(&mutex);

    /* Reading */

    P(&mutex);
    readcnt--;
    if (!readcnt)
    {
      P(&mutex2);
      should_read = 0;
      V(&mutex2);
      V(&w);
    }
    V(&mutex);
  }
}

void writer(void)
{
  int tmp;
  
  while (1)
  {
    P(&mutex2);
    tmp = should_read;
    V(&mutex2);
    
    if (!tmp)
    {
      P(&w);

      /* Writing */
    
      P(&mutex2);
      should_read = 1;
      V(&mutex2);

      V(&w);
    }
    
  }
}
