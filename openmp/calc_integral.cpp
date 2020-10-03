#include <iostream>
#include <math.h>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {

  // Don't change
  int a = 0;
  int b = 500;

  // ----------------------------------
  // Anything below here can be changed
  // ----------------------------------
 
  // Areas is an array that stores each individual Riemann sum
  float areas[500];
  // x_interval is the width of the Riemann sum rectangle
  float x_interval = 0.000001;

  cout << "The function that we are approximating is y = 0.5x + 5 from a = " << a << " to b = " << b << endl;
  cout << "And we will be using Right Riemann sum" << endl;

  auto start = std::chrono::system_clock::now();

  // This looks promising
  int NUM_THREADS = 2;
  omp_set_num_threads(NUM_THREADS); 
  for (int i = a; i < b; i++) {
	float area = 0;
        for (double j = i; j <= i + 1; j += x_interval) {
		area = area + (0.5 * j + 5) * x_interval;
	}
	areas[i] = area;
  }

  // Could this also be made parallel???
  float sum = 0;
  for (int i = 0; i < b; i++) {
	sum += areas[i];
  }

  cout << fixed;
  cout << "The estimated integral is: " << sum << endl;

  auto end = std::chrono::system_clock::now();
  
  auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
 
  cout << "\nRuntime:" << elapsed_seconds.count() << " ms\n\n";

  return 0;
}
