#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define N 2
#define M 2

typedef struct
{
  int** lop;
  int** rop;
  int** result;
  size_t row;
} thread_arg;

void* thread(void* vargp)
{
  thread_arg* args;
  size_t row, col, i;
  int** lop, **rop, **result;
  int dot_prod;

  args = (thread_arg*)vargp;
  lop = args->lop;
  rop = args->rop;
  result = args->result;
  row = args->row;

  for (col = 0; col < M; col++)
  {
    dot_prod = 0;
    for (i = 0; i < M; i++)
      dot_prod += lop[row][i] * rop[i][col];
    result[row][col] = dot_prod;
  }
}

void mmult_t(int** lop, int** rop, int** result)
{
  thread_arg args[N];
  pthread_t tids[N];
  size_t i;

  for (i = 0; i < N; i++)
  {
    args[i].lop = lop;
    args[i].rop = rop;
    args[i].result = result;
    args[i].row = i;
    pthread_create(&tids[i], NULL, thread, (void*)(&args[i]));
  }

  for (i = 0; i < N; i++)
    pthread_join(tids[i], NULL);
}

void print_matrix(int** mat)
{
  size_t i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
  
}

int main(void)
{
  int** mat1, **mat2, **dest;
  size_t i;

  mat1 = malloc(N * sizeof(int*));
  mat2 = malloc(N * sizeof(int*));
  dest = malloc(N * sizeof(int*));

  for (i = 0; i < N; i++)
  {
    mat1[i] = malloc(M * sizeof(int));
    mat2[i] = malloc(M * sizeof(int));
    dest[i] = malloc(M * sizeof(int));
  }

  mat1[0][0] = 1;
  mat1[0][1] = -2;
  mat1[1][0] = 5;
  mat1[1][1] = 12;

  mat2[0][0] = 0;
  mat2[0][1] = 3;
  mat2[1][0] = 5;
  mat2[1][1] = -1;

  mmult_t(mat1, mat2, dest);

  puts("Left matrix:");
  print_matrix(mat1);

  puts("Right matrix:");
  print_matrix(mat2);

  puts("Result:");
  print_matrix(dest);

  for (i = 0; i < N; i++)
  {
    free(mat1[i]);
    free(mat2[i]);
    free(dest[i]);
  }

  free(mat1);
  free(mat2);
  free(dest);

  return 0;
}
