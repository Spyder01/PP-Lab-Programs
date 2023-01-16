#include <mpi.h>
#include <stdio.h>

int main(int argn, char **argv) {
  int comm_sz, my_rank, root = 0;

  long factorial = 1;

  int n;

  MPI_Init(&argn, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == root) {
    printf("Enter the value of n \n");
    scanf("%d", &n);
  }
  
  MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
  
  int interval = n/comm_sz;

  int local_start = interval*my_rank+1;
  int local_end = interval*(my_rank+1);
  int local_factorial = 1;

  for (int i=local_start; i<=local_end; i++) {
	  local_factorial *= i;
  }

  MPI_Reduce (&local_factorial, &factorial, 1, MPI_INT, MPI_PROD, root, MPI_COMM_WORLD);

  if (my_rank == 0){
	  printf ("The factorial of %d is %ld \n", n, factorial);
  }


  MPI_Finalize ();
  return 0;
}
