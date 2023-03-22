#include <cstdlib>
#include <cmath>
#include <iostream>
#include <mpi.h>

using namespace std;

/* 
 * Using Leibniz series to calculate pi and divde the work in the cluster
 */

#define N 1000
int main(int argc, char *argv[]){
    double pi, truepi;

    double t_start, t_end;

    int rank, size;

    int istart, istop;
    double partialpi, recvpi;

    MPI_Comm comm = MPI_COMM_WORLD; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if(rank == 0)
        cout <<  size << " Processes\n", t_start = MPI_Wtime();

    cout << "Rank: " << rank << "\n";

    partialpi= 0.0;

    istart = N/size * rank + 1;
    istop = istart + N/size -1;

    cout << "rank " << rank << " section start = " << istart << ", section end = " << istop << "\n"; 

    for(int i = istart; i <= istop ;i++){
	    partialpi = partialpi + 1.0/( 1.0 + pow( (((double) i)-0.5)/((double) N), 2.0) );

    }
    cout << "rank " << rank << " >> " << partialpi << "\n";

    if(rank ==0){
        pi = partialpi;
        for(int source = 1 ;  source < size ; source++){
            MPI_Status status;
            MPI_Recv(&recvpi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, comm, &status);
            cout << "rank 0 RECEIVES from rank " << status.MPI_SOURCE << "\n";
            pi = pi + recvpi;
        }
    }else{
        MPI_Ssend(&partialpi, 1, MPI_DOUBLE, 0, 0, comm);
    }


    if(rank ==0){
        pi = pi * 4.0/((double) N);
        truepi = 4.0*atan(1.0);
        cout << "pi: " << pi << ", %error = " << fabs(100.0*(pi-truepi)/truepi) << "\n";
        t_end = MPI_Wtime();
        cout << "time " << (t_end - t_start) << " secs \n";
    }

    MPI_Finalize();

    return 0;
   
}
