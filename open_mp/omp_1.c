#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void merge_sort(int a[], int low, int high);
void merge(int a[], int low, int mid, int high);
void display(int a[], int n);

int main() {
  int *a, n;

  printf("Enter number of elements in the array \n");
  scanf("%d", &n);

  a = (int *)malloc(sizeof(int) * n);

  printf("Enter Array elements \n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  merge_sort(a, 0, n - 1);

  display(a, n);

  return 0;
}

void merge_sort(int a[], int low, int high) {
  int mid;

  if (low < high) {
    mid = (low + high) / 2;

#pragma omp parallel sections num_threads(2)
    {
#pragma omp section
      { merge_sort(a, low, mid); }
#pragma omp section
      { merge_sort(a, mid + 1, high); }
    }
    merge(a, low, mid, high);
  }
}

void merge(int array[], int low, int mid, int high) {
  int temp[50];

  int p, q, i;
  p = low;
  q = mid + 1;

  for (i = 0; p <= mid && q <= high; i++) {
    if (array[p] <= array[q]) {
      temp[i] = array[p++];
    } else {
      temp[i] = array[q++];
    }
  }
  if (p > mid) {
    for (int j = q; j <= high; j++) {
      temp[i++] = array[j];
    }
  } else {
    for (int j = p; j <= mid; j++) {
      temp[i++] = array[j];
    }
  }

  for (int i = 0; i <= high; i++) {
    array[i] = temp[i];
  }
}

void display(int a[], int n) {
  printf("Printing Array inside display \n");
  for (int i = 0; i < n; i++) {
    printf("%d \n", a[i]);
  }
}
