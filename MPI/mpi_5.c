#include<stdio.h>
#include<mpi.h>

int isPrime (int x) {

	for (int i=2; i*i<x; i++) {
		if (x%i == 0) {
			return 0;
		}
	}

	return 1;
}

int main (int argn, char** argc) {
	int comm_sz, my_rank;

	int n, root=0;

	MPI_Init (&argn, &argc);
	MPI_Comm_size (MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

	if (my_rank == root) {
		printf ("Enter the value of n \n");
		scanf("%d", &n);
	}

	MPI_Bcast (&n, 1, MPI_INT, root, MPI_COMM_WORLD); 
	
	int interval = n/comm_sz;

	int start = my_rank*interval+1;
	int end = (my_rank+1)*interval;

	if (my_rank == root) {
		printf("Printing Prime numbers below %d \n", n);
	}

	for (int i=start; i<end; i++) {
		if (i>1 && isPrime(i)) {
			printf ("%d ", i);
		}
	}

	

	MPI_Finalize ();
	return 0;
}

