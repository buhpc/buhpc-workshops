#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 2000
void MMM(double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]){
    double sum;
    omp_set_num_threads(4);
    #pragma omp parallel for private(sum)
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            
            
            sum=0;
            for(int k=0;k<SIZE;k++){
                sum+=A[i][k]*B[k][j];
            }
            C[i][j]=sum;


        }
    }
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void init(double A[SIZE][SIZE]){
    srand(42);
    for(int i = 0;i<SIZE;i++)
        for(int j = 0;j<SIZE;j++)
            A[i][j]=randfrom(-10,10);
}


int main(){
    clock_t start, end;
    double cpu_time_used;
    
    // double A[SIZE][SIZE] = {{1,2,3},
    //                 {4,5,6},
    //                 {7,8,9}};
    // double B[SIZE][SIZE] = {{1.263,-5.263,8.2632},
    //                   {-1.5555, 7.15, 4.523},
    //                   {9.9999,2.3,-5}};

    static double A[SIZE][SIZE];
    static double B[SIZE][SIZE];
    init(A);
    init(B);
                      
    static double C[SIZE][SIZE]; // result
    start = clock();
    MMM(A,B,C);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    if(SIZE<=5)
        for (int i=0;i<SIZE;i++){
            printf("[");
            for(int j = 0;j<SIZE;j++){
                printf("%f ",A[i][j]);
            }
            printf("] ");
            printf(" [");
            for(int j = 0;j<SIZE;j++){
                printf("%f ",B[i][j]);
            }
            printf("]");
            if(i==SIZE/2)
                printf(" = ");
            else
                printf("   ");
            printf("[");
            for(int j = 0;j<SIZE;j++){
                printf("%f ",C[i][j]);
            }
            printf("] ");
            printf("\n");
        }
    printf("CPU time: %f\n",cpu_time_used);
    return 0;
}