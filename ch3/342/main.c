

struct ACE
{
  short v;
  struct ACE* p;
};

short test(struct ACE* ptr)
{
  int x = 1;
  while (ptr)
  {
    x *= ptr->v;
    ptr = ptr->p;
  }
  return x;
}
