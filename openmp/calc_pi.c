// Estimating Pi through Reimann Sums Integration
// by Natalia Frumkin
// problem formulation is here: 
// https://homepage.physics.uiowa.edu/~ghowes/teach/ihpc12/exercises/ihpc12_exercises_openmp.pdf
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

// first 500 or so digits of pi
// taken from https://www.piday.org/million/

#define PI 3.1415926535897932384626433832795028841971693993751058209749\
44592307816406286208998628034825342117067982148086513282306647093844609\
55058223172535940812848111745028410270193852110555964462294895493038196\
44288109756659334461284756482337867831652712019091456485669234603486104\
54326648213393607260249141273724587006606315588174881520920962829254091\
71536436789259036001133053054882046652138414695194151160943305727036575\
95919530921861173819326117931051185480744623799627495673518857527248912\
27938183011949129833673362440656643086021394946395224737190702179860943\
70277053921717629317675238467481846766940513200056812714526356082778577

// Definitions for Timing
#define CPG 2.9 // cycles per GHz
#define GIG 1000000000

// specify how many threads
#define NUM_THREADS 2

// calculate height of this vertical box
double height(double x) {
    return sqrt(1.0-x*x);
}

int main(int argc, char* argv[]) {
    struct timespec diff(struct timespec start, struct timespec end);
    struct timespec time1, time2;
    struct timespec timestamp;

    double pi = 0;
    long int num_boxes = 10000000;
    long double delta;
    delta = 1.0 / num_boxes;

    long double x = 0;
    long double y = 0;

    int i;
    // set number of threads
    omp_set_num_threads(NUM_THREADS);

    // start timer
    clock_gettime(CLOCK_REALTIME, &time1);
    
    // parallelize like this
    // #pragma omp parallel for
    for (i = 0; i < num_boxes; i++) {
        y = height(x);
        // add the area of box to running sum
        pi += y*delta;

        x = i*delta;
    }

    // we are only computing the integral in quadrant I
    // need to multiply by 4 for the full circle
    pi = 4*pi;

    // stop timer
    clock_gettime(CLOCK_REALTIME, &time2);

    printf("=== PI Value:\n %.100lf\n", pi);
    timestamp = diff(time1,time2);
    long double runtime = (long int)((double)(CPG)*(double)(GIG * timestamp.tv_sec + timestamp.tv_nsec));
    long double num_steps_estimated = 1.0/(8.0*fabs(PI-pi));
    
    long double score = runtime / num_steps_estimated;

    printf("=== SCORE: \n %Lf\n\n", score);
}

struct timespec diff(struct timespec start, struct timespec end)
{
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = GIG+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}