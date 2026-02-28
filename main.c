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
        for(int p = k; p < n; ++p){
            //Find max
            if(abs(U[p][k]) > maxVal){
                maxVal = abs(U[p][k]);
                maxRow = p;
            }  

        }
        //Pivot
        double* temp = U[k];
        U[k] = U[maxRow];
        U[maxRow] = temp;

        printf("Pivot %d, %d\n", k+1, maxRow+1);
        PrintMat((double**)U, 3, 4);
        printf("\n");

        //Elimination
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
void jordanElimination(int n, double** U, double** D){
    memcpy(D,U,sizeof(U));
    for(int k=n; k >= 2; k--){
        for(int i=1; i<k-1; i++){
            D[i][n+1] -= (D[i][k]/D[k][k]) * D[k][n+1];
            D[i][k] = 0;
        }
    }
}


int main(int argc, char* argv[]){

    numOfThreads = atoi(argv[1]);

    //Right format check
    if(argc != 2 || numOfThreads == 0){
        printf("You have entered the wrong arguments, Format: ./main {number of threads}");
        return -1;
    }

}