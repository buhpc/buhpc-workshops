#include <chrono>
#include <cstdlib>
#include <iostream>


#ifndef RADIUS
	#define RADIUS 5
#endif

#ifndef BLOCK_SIZE
	#define BLOCK_SIZE 10
#endif


__global__ void stencil_no_sync(int *in, int *out)
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
	////////////////////////////// missing sync thread ////////////////////////
	
	// Apply the stencil
	int result = 0;
	for (int offset = -RADIUS ; offset <= RADIUS ; offset++)
		result += temp[lindex + offset];
	// Store the result
	out[gindex] = result;

}

__global__ void stencil_sync(int *in, int *out)
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
	////////////////////////////////// sync thread ////////////////////////////
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

	int *in  = static_cast<int *>(aligned_alloc(64, (BLOCK_SIZE+2*RADIUS) * sizeof(int)));
	int *out_ns  = static_cast<int *>(aligned_alloc(64, (BLOCK_SIZE) * sizeof(int)));
	int *out_s  = static_cast<int *>(aligned_alloc(64, (BLOCK_SIZE) * sizeof(int)));


	std::cout << "value of in array\n";

	for(int i=0; i<BLOCK_SIZE+2*RADIUS; i++)
	{
		in[i]=i+1;
		std::cout << in[i] << "\t";

	}
	std::cout << "\nCorrect answer\n";
	for(int i=RADIUS; i<BLOCK_SIZE+RADIUS; i++)
	{
		int sum=0;
		for(int j=i-RADIUS; j<=i+RADIUS; j++)
			sum+=in[j];
		std::cout << sum << "\t";
	}
	std::cout << "\n\n";
	

	//copying mem to device
	int *d_in;
	int *d_out_ns;
	int *d_out_s;
	cudaMalloc(&d_in,	(BLOCK_SIZE+2*RADIUS) * sizeof(int));
	cudaMalloc(&d_out_ns, 	BLOCK_SIZE * sizeof(int));
	cudaMalloc(&d_out_s, 	BLOCK_SIZE * sizeof(int));
	cudaMemcpy(d_in,	in,	(BLOCK_SIZE+2*RADIUS) * sizeof(int), cudaMemcpyHostToDevice);

	//run without sync
	stencil_no_sync<<<1, BLOCK_SIZE>>>(d_in, d_out_ns);
	cudaDeviceSynchronize();

	//get data
	cudaMemcpy(out_ns,	d_out_ns,	(BLOCK_SIZE) * sizeof(int), cudaMemcpyDeviceToHost);

	cudaError_t __err = cudaGetLastError();
	std::cout << "Result for stencil without __syncthreads: "<<cudaGetErrorString(__err)<<"\n";
	for (auto i=0; i<BLOCK_SIZE; i++)
	{
		std::cout << out_ns[i] << "\t";
	}
	std::cout << "\n";


	//run with sync
	stencil_sync<<<1, BLOCK_SIZE>>>(d_in, d_out_s);
	cudaDeviceSynchronize();

	//get data
	cudaMemcpy(out_s,	d_out_s,	(BLOCK_SIZE) * sizeof(int), cudaMemcpyDeviceToHost);

	__err = cudaGetLastError();
	std::cout << "\nResult for stencil with __syncthreads: "<<cudaGetErrorString(__err)<<"\n";
	for (auto i=0; i<BLOCK_SIZE; i++)
	{
		std::cout << out_s[i] << "\t";
	}
	std::cout << "\n\n";


	return 0;


}