//#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N_THREAD 10



int main()
{
	printf("=== Begin OpenMP Example\n");

	//begin timing 
	clock_t start = clock();

	//comment out this line for serial for loop
	#pragma omp parallel for
	for(int i=0; i<N_THREAD; i++)
	{

		//Something that takes time to compute
		int prod=1;
		for(int j=1; j<10000; j++)
		{
			int prod2=1;
			for(int k=1; k<10000; k++)
			{
				prod2=prod2*j;
			}
			prod=prod*j;
		}

		int tr_id=omp_get_thread_num();
		printf("Compute done: on process %d in thread %d.\n", i, tr_id);
	}

	//stop timing 
	clock_t end = clock();

	//display runtime
	printf("\nruntime: %.5f ms\n\n", (double)(end-start)/CLOCKS_PER_SEC*100);
}
