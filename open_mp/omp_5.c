#include<stdio.h>
#include<omp.h>

int isPrime (int x);
void print_prime_serial (int n);
void print_prime_parallel (int n); 


int main () {
	int n;
	double start, end;

	printf ("Enter the number of consecutive prime numbers to be printed: \n");
	scanf ("%d", &n);

	start = omp_get_wtime ();
	print_prime_serial (n);
	end = omp_get_wtime ();

	printf ("Time taken for serial computation: %lf \n", end-start);

	start = omp_get_wtime ();
	print_prime_parallel (n);
	end = omp_get_wtime ();

	printf ("Time taken for parallel computation: %lf \n", end-start);

	return 0;
}

int isPrime (int x) {

	for (int i=2; i*i<=x; i++) {
		if (x%i == 0){
			return 0;
		}

	}

	return 1;
}

void print_prime_serial (int n) {

	for (int i=2; i<=n; i++) {
		if (isPrime (i)) {
			printf ("%d ", i);
		}
	}

	printf ("\n");
}

void print_prime_parallel (int n) {

	int x = 2;

#pragma omp parallel 
	while (x<n) {
// Use the critical directive to avoid the duplicates
#pragma omp critical
		if (isPrime (x) && x<n) {
			printf("%d ", x);
		}

#pragma omp atomic
		x++;
	}

	printf("\n");
}





