
static char* last_block = heap_listp;

static void* find_fit(size_t asize)
{
  char* bp = last_block;

  while (GET_SIZE(HDRP(bp)))
  {
    if (!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize)
    {
      last_block = NEXT_BLKP(bp);
      return (void*) bp;
    }
    bp = NEXT_BLKP(bp);
  }

  return NULL;
}
