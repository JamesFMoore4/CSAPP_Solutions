#define N 4

sem_t mutex, cntr;

void reader(void)
{
  while (1)
  {
    if (cntr < N)
    {
      V(&cntr);
      if (cntr == 1)
	P(&mutex);

      /* read */

      P(&cntr);
      if (!cntr)
	V(&mutex);
    }
  }
}

void writer(void)
{ 
  while (1)
  {
    P(&mutex);

    /* write */

    V(&mutex);
  }
}
