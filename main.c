#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "Lab3IO.h"
#include "timer.h"


int numOfThreads;

/*Gaussian Elimination
*-------------------------
*A is the input n x (n + 1) matrix
*
*U is the output matrix (n x (n + 1))
*
*/
void gaussianElimination(double** G, int n, double** U){

    //U <- G
    for(int i = 0; i < n; ++i){
        memcpy(U[i], G[i], (n + 1)*sizeof(double));
    }

    for (int k = 0; k < n - 1; ++k){
        
        //Pivot for absoulte max
        int maxRow = k;
        int maxVal = 0;
        int localMaxVal = 0;
        int localMaxRow = k;
        #pragma omp parallel private(localMaxVal, localMaxRow) shared(U, n)
        {

            #pragma omp for 
            for(int p = k; p < n; ++p){
                //Find max
                if(fabs(U[p][k]) > maxVal){
                    localMaxVal = fabs(U[p][k]);
                    localMaxRow = p;
                }  
            }
            if(localMaxVal > maxVal){
                #pragma omp critical
                {
                    if(localMaxVal > maxVal){
                        maxRow = localMaxRow;
                        maxVal = localMaxVal;
                    }
                }

            }
        }
        //Pivot
        double* temp = U[k];
        #pragma omp critical
        {
            U[k] = U[maxRow];
            U[maxRow] = temp;
        }
        
        //#pragma omp barrier
        //printf("Pivot %d, %d\n", k+1, maxRow+1);
        //PrintMat((double**)U, 3, 4);
        //printf("\n");

        //Elimination
        #pragma omp parallel default(none) shared(n, U, k)
        for (int i = k + 1; i < n; ++i){
            double temp = U[i][k]/U[k][k];
            #pragma omp for
            for (int j = k; j < n + 1; ++j){
                U[i][j] = U[i][j] - temp*U[k][j];
            }
            //printf("row Replacement %d %f*R%d\n", i+1, -temp, k+1);
            //PrintMat((double**)U, 3, 4);
            //printf("\n");
        }
        //#pragma omp barrier

        
    }
}

/*Jordan Elimination
*-------------------------
*U is the input matrix (n x (n + 1))
*
*D is the output matrix (n x (n + 1))
*
*/
void jordanElimination(int n, double** U, double** D){
    for(int i=0; i < n; i++){
        memcpy(D[i], U[i], sizeof(double)*(n+1));
    }
    #pragma omp parallel default(none) shared(D,n)
    for(int k=n; k >= 2; k--){
        #pragma omp for
        for(int i=0; i<k-1; i++){
            D[i][n] -= (D[i][k]/D[k][k])*D[k][n];
            D[i][k] = 0;
        }
    }
}


int main(int argc, char* argv[]){

    numOfThreads = atoi(argv[1]);

    //Right format check
    if(argc != 2 || numOfThreads == 0){
        printf("You have entered the wrong arguments, Format: ./main {number of threads}\n");
        return -1;
    }
    omp_set_num_threads(numOfThreads);
    double **G;
    double **U;
    double **D;
    int n=0;
    Lab3LoadInput(&G, &n);
    U = CreateMat(n, n + 1);
    D = CreateMat(n, n + 1);
    double *x = CreateVec(n);
    double startTime, endTime;

    GET_TIME(startTime);
    
    gaussianElimination(G, n, U);
    jordanElimination(n, U, D);

    #pragma omp parallel for shared(n)
    for (int i=0; i < n; ++i){
        x[i]= D[i][n] / D[i][i]; 
    }

    GET_TIME(endTime);
    double Time = endTime - startTime;

    Lab3SaveOutput(x, n, Time);
    //PrintMat(D, n, n + 1); //Testing
    DestroyMat(G, n);
    DestroyMat(U, n);
    DestroyMat(D, n);
    DestroyVec(x);
    return 0;
}