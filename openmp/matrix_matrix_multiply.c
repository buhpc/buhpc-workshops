#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

void MMM(double* A,double* B, double* C,int i_length, int j_length, int k_length){
    /* matrix matrix multiply function that takes in 3 arrays A,B,C, that each represent a matrix:
        A is a i_length by k_length matrix
        B is a k_length by j_length matrix
        C is the output i_length by j_length matrix
        I reccomend trying out a i,j,k triple for loop first

        Due to performance, we are using 1D arrays to represent 2D arrays, the way you index into them is like this
        "A[i][k]" becomes "A[i*k_length + k]"
        "B[k][j]" -> "B[k*j_length + j]"
        "C[i][j]" -> "C[i*j_length + j]"

        the output is C, you don't return anything, just modify C and set the correct values.

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
        for(int j = 0;j<n_cols;j++)
            A[i*n_cols + j]=randfrom(-10,10);
}


int main(){
    clock_t start, end;
    double cpu_time_used;
    //INCREASE MATRIX SIZE TO SEE PERF BOOST
    int i_len = 5,
        j_len=4,
        k_len=3; 
    
    double* A = calloc(i_len*k_len,sizeof(double));
    double* B = calloc(k_len*j_len,sizeof(double));
    double* C = calloc(i_len*j_len,sizeof(double));

    memset(C,0,i_len*j_len*sizeof(double));
    init(A,i_len,k_len);
    init(B,k_len,j_len);
                      
    start = clock();
    MMM(A,B,C,i_len,j_len,k_len);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(i_len<=5 && j_len <=5 && k_len<=5){
        printf("A=");
        for(int i = 0;i<i_len;i++){
            printf("\t");
            for(int k=0;k<k_len;k++){
                printf("%f ",A[i*k_len + k]);
            }
            printf("\n");
        }
        printf("\n");
        printf("B=");
        for(int k = 0;k<k_len;k++){
            printf("\t");
            for(int j=0;j<j_len;j++){
                printf("%f ",B[k*j_len + j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("C=");
        for(int i = 0;i<i_len;i++){
            printf("\t");
            for(int j=0;j<j_len;j++){
                printf("%f ",C[i*j_len + j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    printf("CPU time: %f\n",cpu_time_used);
    free(A);
    free(B);
    free(C);
    return 0;
}