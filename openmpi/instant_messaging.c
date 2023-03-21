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
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, node_name_len;
    char node_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(node_name, &node_name_len);
    printf("Hello from process %d on node %s\n", rank, node_name);
    if (rank == 0) {
        char message[100];
        MPI_Status status;
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("Received message '%s' from process %d on node %s\n", message, status.MPI_SOURCE, node_name);
        }
    } else {
        char message[100] = "Hello from process ";
        sprintf(message + 19, "%d", rank);
        MPI_Send(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
