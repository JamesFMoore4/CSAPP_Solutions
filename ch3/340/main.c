
#define N 16
typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val)
{
  int *base = A;
  long i = 0, end = N * (N + 1);
  do
  {
    base[i] = val;
    i += N + 1;
  } while (i != end);
}
