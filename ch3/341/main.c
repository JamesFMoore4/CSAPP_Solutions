
struct test
{
  short* p;
  struct
  {
    short x;
    short y;
  } s;
  struct test* next;
}

void st_init(struct test* st)
{
  st->s.y = st->s.x;
  st->p = &(st->s.y);
  st->next = st;
}
