#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

void relax(double* A,double* output, int nrows, int ncols){
    /* relax function that takes in an arrays A, that represents a matrix of nrows by ncols. 
        for each non edge/corner cell in the matrix, calculate the average of the cell and it's adjacent neighbors.
        
        Due to performance, we are using 1D arrays to represent 2D arrays, the way you index into them is like this
        "A[i][j]" becomes "A[i*ncols + j]"
        "output[i][j]" becomes "output[i*ncols + j]"
        
        the output is 'output', you don't return anything, just modify output and set the correct values.

        Once you have the code working, try with openMP
    */

}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void init(double *A, int n_rows,int n_cols){
    srand(42);
    for(int i = 0;i<n_rows;i++)
        for(int j = 0;j<n_cols;j++){
            if(i==0)
                A[i*n_cols + j] = randfrom(-10,0);
            else if (i==n_rows-1)
                A[i*n_cols + j] = randfrom(0,10);
            else
                A[i*n_cols + j] = randfrom(-10,10);
        }
}


int main(){
    clock_t start, end;
    double cpu_time_used;
    int nrows = 10,
        ncols=10;
    
    double A[nrows*ncols];
    double output[nrows*ncols];

    memset(output,0,nrows*ncols*sizeof(double));
    init(A,nrows,ncols);
                      
    start = clock();
    relax(A,output,nrows,ncols);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(nrows<=10 && ncols <=10){
        printf("A=");
        for(int i = 0;i<nrows;i++){
            printf("\t");
            for(int j=0;j<ncols;j++){
                printf("%f ",A[i*ncols + j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("output=");
        for(int i = 0;i<nrows;i++){
            printf("\t");
            for(int j=0;j<ncols;j++){
                printf("%f ",output[i*ncols + j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    printf("CPU time: %f\n",cpu_time_used);
    return 0;
}