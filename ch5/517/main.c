

void* Memset(void* s, int c, size_t n)
{
  unsigned long pcked;
  unsigned char* byte_ptr = (unsigned char*) &pcked;
  for (int i = 0; i < sizeof(unsigned long); i++)
    *byte_ptr++ = (unsigned char) c;

  unsigned long* mem_location = s;
  size_t cnt = 0;
  if (n - (sizeof(unsigned long) - 1) < n)
      while (cnt < n-(sizeof(unsigned long)-1))
      {
        *mem_location++ = pcked;
         cnt += sizeof(unsigned long);
      }

  unsigned char* mem_location2 = mem_location;
  for (cnt < n)
  {
    *mem_location2++ = (unsigned char) c;
    cnt++;
  }
  
  return s;
}
