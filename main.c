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