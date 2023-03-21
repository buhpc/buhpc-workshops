#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int num_procs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello world %d of %d\n", rank, num_procs);

    MPI_Finalize();
    return 0;
}
