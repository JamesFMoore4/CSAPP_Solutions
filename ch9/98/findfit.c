
static void* find_fit(size_t asize)
{
  char* bp = heap_listp + (2 * WSIZE);

  while (GET_SIZE(HDRP(bp)))
  {
    if (!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize)
      return (void*) bp;
    bp = NEXT_BLKP(bp);
  }

  return NULL;
}
