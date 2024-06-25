
void merge (long src1[], long src2[], long dest[], long n)
{
  long i1 = 0;
  long i2 = 0;
  long id = 0;
  while (i1 < n && i2 < n)
  {
    long temp1 = src1[i1], temp2 = src2[i2];
    dest[id++] = temp1 < temp2 ? temp1 : temp2;
    i1 += temp1;
    i2 += 1 - temp1;
  }

  while (i1 < n)
    dest[id++] = src[i1++];
  while (i2 < n)
    dest[id++] = src[i1++];
}
