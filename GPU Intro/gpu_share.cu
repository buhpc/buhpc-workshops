#include <chrono>
#include <cstdlib>
#include <iostream>


#define BLOCK_SIZE 1024

#ifndef RADIUS
	#define RADIUS 3
#endif

#ifndef ITERS
	#define ITERS 100
#endif

#ifndef USE_L2
	#define USE_L2 false 
#endif


__global__ void stencil_no_shared(int *in, int *out)
{
	int temp[BLOCK_SIZE + 2 * RADIUS];
	int gindex = threadIdx.x + blockIdx.x * blockDim.x;
	int lindex = threadIdx.x + RADIUS;
	// Read input elements into shared memory
	temp[lindex] = in[gindex+RADIUS];
	if (threadIdx.x < RADIUS) {
		temp[lindex - RADIUS] = in[gindex];
		temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE + RADIUS];
	}
	 __syncthreads();
	// Apply the stencil
	int result = 0;
	for (int offset = -RADIUS ; offset <= RADIUS ; offset++)
	result += temp[lindex + offset];
	// Store the result
	out[gindex] = result;

}

__global__ void stencil_shared(int *in, int *out)
{
	__shared__ int temp[BLOCK_SIZE + 2 * RADIUS];
	int gindex = threadIdx.x + blockIdx.x * blockDim.x;
	int lindex = threadIdx.x + RADIUS;
	// Read input elements into shared memory
	temp[lindex] = in[gindex+RADIUS];
	if (threadIdx.x < RADIUS) {
		temp[lindex - RADIUS] = in[gindex];
		temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE + RADIUS];
	}
	 __syncthreads();
	// Apply the stencil
	int result = 0;
	for (int offset = -RADIUS ; offset <= RADIUS ; offset++)
	result += temp[lindex + offset];
	// Store the result
	out[gindex] = result;

}


int main(int argc, const char *argv[])
{
	using namespace std::chrono;

	int iters;
	if (argc < 2) {
		iters = ITERS;
	} else {
		iters = std::atoi(argv[1]);
	}

	int *in  = static_cast<int *>(aligned_alloc(64, (BLOCK_SIZE+2*RADIUS) * sizeof(int)));
	int *out  = static_cast<int *>(aligned_alloc(64, (BLOCK_SIZE) * sizeof(int)));

	for(int i=0; i<BLOCK_SIZE+2*RADIUS; i++)
	{
		in[i]=i;
	}

	//copying mem to device
	int *d_in_ns;
	int *d_in_s;
	int *d_out_ns;
	int *d_out_s;
	cudaMalloc(&d_in_ns,	(BLOCK_SIZE+2*RADIUS) * sizeof(int));
	cudaMalloc(&d_in_s, 	(BLOCK_SIZE+2*RADIUS) * sizeof(int));
	cudaMalloc(&d_out_ns, 	BLOCK_SIZE * sizeof(int));
	cudaMalloc(&d_out_s, 	BLOCK_SIZE * sizeof(int));

	cudaMemcpy(d_in_ns,	in,	(BLOCK_SIZE+2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_in_s,	in,	(BLOCK_SIZE+2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice);
	//cudaMemcpy(d_out_ns,out,BLOCK_SIZE * sizeof(int), cudaMemcpyHostToDevice);
	//cudaMemcpy(d_out_s,	out,BLOCK_SIZE * sizeof(int), cudaMemcpyHostToDevice);


	//run without using shared cache
 	auto start = high_resolution_clock::now();
 	for(auto i=0; i<iters; i++)
 	{
 		#if (USE_L2==true)
 			stencil_no_shared<<<BLOCK_SIZE, 1>>>(d_in_s, d_out_s);
 		#else
 			stencil_no_shared<<<1, BLOCK_SIZE>>>(d_in_s, d_out_s);
 		#endif
 		cudaDeviceSynchronize();
 	}
 	auto end = high_resolution_clock::now();
	auto diff = duration_cast<microseconds>(end - start);

	#if (USE_L2==true)
		std::cout << "CUDA stencil with L2 cache:\n"
	#else
		std::cout << "CUDA stencil with L1 cache:\n"
	#endif
			<< "\tNumber of Elements: " << BLOCK_SIZE << "\n"
			<< "\tRadius: " << RADIUS << "\n"
			<< "\tIterations = " << iters << "\n"
			<< "\tAverage time = " << diff.count() / iters
			<< " micros. Total time= " << diff.count() << " micros.\n";

	//run with share cache
	start = high_resolution_clock::now();
 	for(auto i=0; i<iters; i++)
 	{
 		stencil_shared<<<1, BLOCK_SIZE>>>(d_in_s, d_out_s);
 		cudaDeviceSynchronize();
 	}
 	end = high_resolution_clock::now();
	diff = duration_cast<microseconds>(end - start);

	std::cout << "CUDA stencil with shared cache:\n"
			<< "\tNumber of Elements: " << BLOCK_SIZE << "\n"
			<< "\tRadius: " << RADIUS << "\n"
			<< "\tIterations = " << iters << "\n"
			<< "\tAverage time = " << diff.count() / iters
			<< " micros. Total time= " << diff.count() << " micros.\n\n";

	return 0;


}