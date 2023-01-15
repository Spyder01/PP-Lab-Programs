#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main () {
	int intervals = 8, intern=1;

#pragma omp parallel for schedule(static, 2)
	for (int i=0; i<intervals; i++) {
		int t = omp_get_thread_num ();

		intern +=1;
		intern %= 2;

		printf ("%d thread in the intern %d value: %d \n", t, intern, i);
	}
	return 0;
}




