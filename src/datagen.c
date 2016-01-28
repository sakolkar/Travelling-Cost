/*
Generate a symmetric square matrix in which every element is uniformly randomly selected integer within some absolute value. The main diagonal are all 0. Some elements are set to large value to represent infinity.

-----
Compiling:
    > gcc datagen.c Lab2IO.c -o datagen

-----
Synopsis:
    datagen [-sbrpo]

-----
Options:
    -s    specify the size of the matrices (default 10) 
    -b    upper bound of the absolute value of the elements (default 5)
    -r    percentage rate of the infinity elements (default 5)
    -p    print the result
    -o    specify the output path (default "./data_input") 

-----
Outputs:
    Output file:
    data_input: storing the two generated matrices

-----
Error returns:
    -1    unexpected options
    -2    fail to open file 

-----
Example:
    >datagen 
    generate 10 by 10 matrix with elements between 0 and 5 or inf (rate 5%), and store the result in "./data_input"
   
    >datagen -s 100 -b 10 -r 10 -p
    generate 100 by 100 matrix with elements between 0 and 10 or inf (rate 10%), print the result and store it in "data_input"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Lab2IO.h"

#define INF 10

int main (int argc, char* argv[])
{
    int size = 10, bound = 5, rate = 5;
    char* OUTPATH = "data_input";
    int b_print = 0;    //switch for the print
    int option;
    int temp,i,j;
    int ** A;
    FILE *op;

    while ((option = getopt(argc, argv, "s:b:r:po:")) != -1)
        switch(option){
            case 's': size = strtol(optarg, NULL, 10); break;
            case 'b': bound = strtol(optarg, NULL, 10);break;
            case 'r': rate = strtol(optarg, NULL, 10);
            case 'p': b_print = 1; break;
            case 'o': OUTPATH = optarg; break;
            case '?': printf("Unexpected Options. \n"); return -1;
        }

    A = CreateMat(size);
    srand(time(NULL));
    for (i = 0; i < size; ++i){	
        for (j = i; j < size; ++j){
            if (rand() % 100 <= rate)
                A[i][j] = INF * bound;
            else
                A[i][j] = rand() % bound + 1;
            A[j][i] = A[i][j];
        }
    }
    for (i = 0; i < size; ++i){
        A[i][i] = 0;
    }

    if ((op = fopen(OUTPATH,"w")) == NULL){
        printf("Cant open a file!/n");
        return -2;
    }
    fprintf(op,"%d\n\n", size);
    for (i = 0; i < size; ++i) {	
        for (j = 0; j < size; ++j){
            fprintf(op,"%d\t", A[i][j]);
        }
        fprintf(op,"\n");
    }
    fclose(op);

    if (b_print){
        printf("The matrix size is %d\n", size);
        printf("=====================================\n");
        printf("Matrix A is \n");			
        PrintMat(A, size);
    }
    
    DestroyMat(A, size);
	return 0;
}
