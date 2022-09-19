#include <stdio.h>
#include <omp.h>
int main () {
    int x = 0; //Shared variable
	#pragma omp parallel
	{
		int tid = omp_get_thread_num(); //Private variable
		#pragma omp critical
		{
			x++;
			printf("Hello World from thread %d, x = %d\n", tid, x);
		}
		#pragma omp barrier
		if(tid==0) {
			printf("Number of threads = %d\n", omp_get_num_threads());
		}
	}
	printf("Done with parallel segment\n");
}
