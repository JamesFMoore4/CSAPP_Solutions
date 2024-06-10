
void cond(short a, short* p)
{
  if (!a)
    goto done;
  if (a <= *p)
    goto done;
  *p = a;
 done:
  return;
}
