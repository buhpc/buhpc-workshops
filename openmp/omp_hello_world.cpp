#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <chrono>

#define ITERATIONS 4

using namespace std;

int main() {
	printf("=== Begin OpenMP Example ===\n");

	//begin timing
	printf("Timing Starts Now\n"); 
	auto start = std::chrono::system_clock::now();

	long sum = 0;

	//comment out this line for serial for loop
	//#pragma omp parallel for	
	for (int i = 0; i < ITERATIONS; i++) {
		long sum = 0;
		//Something that takes time to compute	
		for (int j = 1; j < 10000; j++) {
			for (int k = 1; k < 100000; k++) {
				sum = sum + j * k;
			}
		}
		
		int thread_id = omp_get_thread_num();
		printf("\nCompute done: on iteration %d in thread %d.\n", i, thread_id);
		cout << "sum: " << sum << endl;
	}

	//stop timing 
	auto end = chrono::system_clock::now();
	printf("\nTiming Stops Now\n");

	auto elapsed_seconds = chrono::duration_cast<chrono::milliseconds>(end-start);

	//display runtime
	cout << "\nRuntime: " << elapsed_seconds.count() << " ms\n\n";
	cout << "=== End ===" << endl;
}

