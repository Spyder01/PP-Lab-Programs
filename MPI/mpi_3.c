#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void display(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(int argn, char **argc) {
  int comm_sz, my_rank;

  int a[100], b[100], c[100];

  int size = 16;
  int root = 0;

  MPI_Init(&argn, &argc);

  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0) {
    for (int i = 0; i < size; i++) {
      a[i] = rand() % 10;
      b[i] = rand() % 10;
    }
  }

    int subsize = size / comm_sz;

    int *a_small = malloc(subsize * sizeof(int));
    int *b_small = malloc(subsize * sizeof(int));

    MPI_Scatter(a, subsize, MPI_INT, a_small, subsize, MPI_INT, root,
                MPI_COMM_WORLD);
    MPI_Scatter(b, subsize, MPI_INT, b_small, subsize, MPI_INT, root,
                MPI_COMM_WORLD);

    int *c_small = malloc(subsize * sizeof(int));

    for (int i = 0; i < subsize; i++) {
      c_small[i] = a_small[i] + b_small[i];
    }

    MPI_Gather(c_small, subsize, MPI_INT, c, subsize, MPI_INT, root,
               MPI_COMM_WORLD);

    if (my_rank == root) {
      printf("Vector A: \n");
      display(a, size);

      printf("Vector B: \n");
      display(b, size);

      printf("The sum of the vectors A and B is: \n");
      display(c, size);
    }

    MPI_Finalize();
    return 0;
  }
