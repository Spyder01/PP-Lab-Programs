#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double *add(double *a, double *b, int n);

int main() {
  int n;

  printf("Enter the number of elements in vectors \n");
  scanf("%d", &n);

  double *a = calloc(n, sizeof(double));
  double *b = calloc(n, sizeof(double));

  printf("Enter elements for vector A \n");
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
  }

  printf("Enter elements for vector B \n");
  for (int i = 0; i < n; i++) {
    scanf("%lf", &b[i]);
  }

  double *c = calloc(n, sizeof(double));
  c = add(a, b, n);

  printf ("The summed up vector is: \n");
  
  for (int i=0; i<n; i++) {
	  printf ("%lf ", c[i]);
  }

  printf ("\n");

  return 0;
}


double* add (double* a, double *b, int n) {
	double *c = calloc(n, sizeof(double));

#pragma omp parallel for 
	for (int i=0; i<n; i++) {
		c[i] = a[i] + b[i];
	}

	return c;
}


  


