#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(rank); // Seed the random number generator with the process rank

    long long n = 1000000; // Number of random points to generate
    double x, y, pi = 0, local_pi;

    for (long long i = rank; i < n; i += size) {
        x = (double) rand() / RAND_MAX; // Generate a random x-coordinate
        y = (double) rand() / RAND_MAX; // Generate a random y-coordinate
        if (x * x + y * y <= 1) { // If the point is inside the unit circle
            pi += 4.0 / n;
        }
    }

    MPI_Reduce(&pi, &local_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Estimate of pi: %f\n", local_pi);
    }

    MPI_Finalize();
    return 0;

}
