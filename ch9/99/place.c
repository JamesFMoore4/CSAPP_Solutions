
static void place(void* bp, size_t asize)
{
  int prev_block_size = GET_SIZE(HDRP(bp));
  
  if (prev_block_size - asize < ((2 * WSIZE) + DSIZE)) /* Remainder less than minimum block size */
  {
    PUT(HDRP(bp), PACK(prev_block_size, 1));
    PUT(FTRP(bp), PACK(prev_block_size, 1));
  }
  else
  {
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(prev_block_size - asize, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(prev_block_size - asize, 0));
  }
}
