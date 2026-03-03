#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

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
    for(int i = 0; i < n; ++i)
        memcpy(U[i], G[i], (n + 1)*sizeof(double));

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
                if(abs(U[p][k]) > maxVal){
                    localMaxVal = abs(U[p][k]);
                    localMaxRow = p;
                }  
            }
            if(localMaxVal > maxVal){
                #pragma critical
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

        printf("Pivot %d, %d\n", k+1, maxRow+1);
        PrintMat((double**)U, 3, 4);
        printf("\n");

        //Elimination
        #pragma omp parallel for shared(U, n)
        for (int i = k + 1; i < n; ++i){
            double temp = U[i][k]/U[k][k];

            for (int j = k; j < n + 1; ++j){
                U[i][j] = U[i][j] - temp*U[k][j];
            }

            printf("row Replacement %d %f*R%d\n", i+1, -temp, k+1);
            PrintMat((double**)U, 3, 4);
            printf("\n");
        }
        
    }
}

/*Jordan Elimination
*-------------------------
*U is the input matrix (n x (n + 1))
*
*D is the output matrix (n x (n + 1))
*
*/
void jordanElimination(double** A, double* b, double n, double** U){

}


int main(int argc, char* argv[]){

    numOfThreads = atoi(argv[1]);

    //Right format check
    if(argc != 2 || numOfThreads == 0){
        printf("You have entered the wrong arguments, Format: ./main {number of threads}");
        return -1;
    }

}