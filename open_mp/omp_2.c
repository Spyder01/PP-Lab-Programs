#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define num_steps 100000

double serial_pi();
double parallel_pi();

int main() {
  double start, end, pi;

  start = omp_get_wtime();
  pi = serial_pi();
  end = omp_get_wtime();

  printf("Pi value computed serially=%lf \n", pi);
  printf("Time taken for serial execution: %lf \n", end - start);

  start = omp_get_wtime();
  pi = parallel_pi();
  end = omp_get_wtime();

  printf("Pi value computed parallely=%lf \n", pi);
  printf("Time taken for parallel execution: %lf \n", end - start);

  return 0;
}

double serial_pi() {
  double pi = 0;

  for (int k = 0; k < num_steps; k++) {
    pi += pow(-1, k) / (2 * k + 1);
  }
  pi = pi * 4;

  return pi;
}

double parallel_pi() {
  double pi = 0;

  int N = omp_get_max_threads();
  double *threads = calloc(N, sizeof(double));

#pragma omp parallel for
  for (int k = 0; k < num_steps; k++) {
    int t = omp_get_thread_num();
    threads[t] += pow(-1, k) / (2 * k + 1);
  }

  for (int i = 0; i < N; i++) {
    pi += threads[i];
  }

  pi = pi * 4;

  return pi;
}
