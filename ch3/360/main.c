

long loop(long x, long n)
{
  long result = 0;
  long mask;
  for (mask = 1; mask; mask = mask << n)
  {
    result |= x & mask;
  }
  return result;
}
