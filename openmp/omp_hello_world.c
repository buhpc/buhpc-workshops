#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <chrono>

#define N_THREAD 10



int main()
{
	printf("=== Begin OpenMP Example\n");

	//begin timing 
	auto start = std::chrono::system_clock::now();

	//comment out this line for serial for loop
	//#pragma omp parallel for
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
	auto end = std::chrono::system_clock::now();

	auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

	//display runtime
	std::cout << "\nruntime:" << elapsed_seconds.count() << " ms\n\n";
}
