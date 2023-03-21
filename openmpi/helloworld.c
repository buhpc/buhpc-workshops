#include <mpi.h> // include library
#include <stdio.h>

int main(int argc, char *argv[]) {
    int num_procs, rank;

    MPI_Init(&argc, &argv); // initilization
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); // commnicator, number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // communicator, process ID

    printf("Hello world %d of %d\n", rank, num_procs); // the process that we want to run

    MPI_Finalize();
    return 0;
}
