#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100

int main () {
	int sum = 0;

#pragma omp parallel for 
	for (int i=1; i<=N; i++) {
#pragma omp critical
		sum += i;
	}

	printf ("Sum of first 100 numbers are %d \n", sum);

	return 0;
}
