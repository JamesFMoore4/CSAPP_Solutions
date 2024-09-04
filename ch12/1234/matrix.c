#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define N 2
#define M 2

typedef struct
{
  const int** mat1;
  const int** mat2;
  int** dest;
  size_t row;
} args;

void* matrix_thread(void* vargp)
{
  args* arg;
  size_t col, i;
  int dot_prod;

  arg = (args*)vargp;

  for (col = 0; col < M; col++)
  {
    dot_prod = 0;

    for (i = 0; i < M; i++)
      dot_prod += arg->mat1[arg->row][i] * arg->mat2[i][col];

    arg->dest[arg->row][col] = dot_prod;
  }
  
}

int matrix_mult_t(const int mat1[N][M], const int mat2[N][M], int dest[N][M])
{
  pthread_t tids[N];
  args arg_vector[N];
  size_t i;
  
  if (N != M)
    return 0;
 
  memset(dest, 0, N*M*sizeof(int));

  for (i = 0; i < N; i++)
  {
    arg_vector[i].mat1 = (const int**)mat1;
    arg_vector[i].mat2 = (const int**)mat2;
    arg_vector[i].dest = (int**)dest;
    arg_vector[i].row = i;
    pthread_create(&tids[i], NULL, matrix_thread, (void*)&arg_vector[i]);
  }

  for (i = 0; i < N; i++)
    pthread_join(tids[i], NULL);

  return 1;
}

void print_matrix(int mat[N][M])
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

  int mat1[][M] =
  {
    {1, -2},
    {5, 12}
  };

  int mat2[][M] =
  {
    {0, 3},
    {5, -1}
  };

  int dest[N][M];
  
  matrix_mult_t(mat1, mat2, dest);
  print_matrix(dest);
  
  return 0;
}
