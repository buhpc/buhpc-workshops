#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int num_procs, rank, msg;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Send a message from each process to the host process
  if (rank != 0) {
    printf("Sending message from process %d\n", rank);
    msg = rank;
    MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    // Host process receives messages from all other processes
    int i, recv_msg;
    for (i = 1; i < num_procs; i++) {
      MPI_Recv(&recv_msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Received message from process %d: %d\n", i, recv_msg);
    }
  }

  MPI_Finalize();
  return 0;
}
