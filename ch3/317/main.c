
long lt_cnt = 0;
long ge_cnt = 0;

// Original
/* long absdiff_se(long x, long y)
   {
     long result;
     if (x < y) {
       lt_cnt++;
       result = y - x;
     }
     else {
       ge_cnt++;
       result = x - y;
     }
     return result;
   }
*/

long absdiff_se(long x, long y)
{
  long result;
  int t = x < y;
  if (t)
    goto true;
  ge_cnt++;
  result = x - y;
  goto done;
 true:
  lt_cnt++;
  result = y - x;
 done:
  return result;
}


