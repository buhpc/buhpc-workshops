// Estimating Pi through Reimann Sums Integration
// by Natalia Frumkin
// problem formulation is here: 
// https://homepage.physics.uiowa.edu/~ghowes/teach/ihpc12/exercises/ihpc12_exercises_openmp.pdf
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <iostream>
#include <chrono>

// first 100 or so digits of pi
// taken from https://www.piday.org/million/
#define PI 3.1415926535897932384626433832795028841971693993751058209749

// Definitions for Timing
#define CPG 2.9 // cycles per GHz
#define GIG 1000000000

// specify how many threads
#define NUM_THREADS 8

// calculate height of this vertical box
double height(double x) {
    return 1.0/(1.0+x*x);
}

int main(int argc, char* argv[]) {

    double pi = 0, integral;
    long int num_boxes = 1000000000;
    long double delta;
    delta = 1.0 / num_boxes;

    long double x = 0;

    int i;


    // set number of threads
    omp_set_num_threads(NUM_THREADS);

    // start timer
    auto start = std::chrono::system_clock::now();
    
    // parallelize like this

    #pragma omp parallel for private(x, i) reduction(+:integral)
    for (i = 0; i < num_boxes; i++) {

        x = i*delta;        
        // add the area of box to running sum
        integral += height(x)*delta;

    }

    // we are only computing the integral in quadrant I
    // need to multiply by 4 for the full circle
    pi = 4*integral;

    // stop timer
    auto end = std::chrono::system_clock::now();

    printf("=== Pi Value:\n %.100lf\n", pi);
    if (fabs(PI-pi) < 1e-8) {
        printf("=== The calculated value is correct to at least 8 digits!\n");
    }

    // calculate runtime
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    //display runtime
    std::cout << "\nruntime:" << elapsed_seconds.count() << " ms\n\n";
}

