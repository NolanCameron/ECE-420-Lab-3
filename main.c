#include <stdlib.h>

#include "Lab3IO.h"
#include "timer.h"

int numOfThreads;

/*Gaussian Elimination
*-------------------------
*A is the input n x n matrix
*B is the input n dimensional vector
*
*U is the output matrix (n x (n + 1))
*
*/
void gaussianElimination(double** A, double* b, double n, double** U){

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