
void psum1(float a[], float p[], long n)
{
  long i;
  p[0] = a[0];
  float temp = p[0];
  for (i = 1; i < n; i++)
  {
    temp += a[i];
    p[i] = temp;
  } 
}


