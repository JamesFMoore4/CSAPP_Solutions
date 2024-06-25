
void innter(vec_ptr u, vec_ptr v, data_t* dest)
{
  long i;
  long length = vec_length(u);
  data_t* udata = get_vec_start(u);
  data_t* vdata = get_vec_start(v);
  data_t sum1, sum2, sum3, sum4, sum5, sum6;
  sum1 = sum2 = sum3 = sum4 = sum5 = sum6 =(data_t) 0;
  
  
  for (i = 0; i < length - 5; i += 6)
  {
    sum1 += udata[i] * vdata[i];
    sum2 += udata[i+1] * vdata[i+1];
    sum3 += udata[i+2] * vdata[i+2];
    sum4 += udata[i+3] * vdata[i+3];
    sum5 += udata[i+4] * vdata[i+4];
    sum6 += udata[i+5] * vdata[i+5];
  }

  for (; i < length; i++)
    sum1 += udata[i] * vdata[i];
  
  *dest = sum1 + sum2 + sum3 + sum4 + sum5 + sum6;
}
