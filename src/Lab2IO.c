#include <stdio.h>
#include <stdlib.h>
#include "Lab2IO.h"

int Lab2_loadinput(int ***A, int *size){
/*
    Allocate memory and load the input data for Lab 2

    -----
    Input:
    int ***A    pointer to the matrix A
    int *size   pointer to the matrix size

    Note: original files should be the output of the datagen.c with name "data_input" in the same folder

    -----
    Output:
    Generated matrix will be passed back to the array *A, along with the matrix size in *size 

    -----
    Example:
    An integer array pointer and a integer should be defined before calling this function:
    int **A; int size; 
    call this function as
    lab2_loadinput(&A, &size);
*/

    FILE* ip;
    int i,j;

    if ((ip = fopen("data_input","r")) == NULL){
            printf("error opening the input data.\n");
            return 1;
    }
    fscanf(ip, "%d\n", size);
    *A = CreateMat(*size);
    for (i = 0; i < *size; ++i){
        for (j = 0; j< *size; ++j){
            fscanf(ip, "%d\t", &(*A)[i][j]);
        }
    }
    fclose(ip);
    return 0;
}

int Lab2_saveoutput(int **A, int size, double Time){
/*
    Save the data to the file for Lab 2 

    -----
    Input:
    int **A     pointer to the result matrix 
    int size    pointer to the matrix size
    double Time Time measure calulation time
    
    -----
    Output:
    data_output the stored data

    -----
    Example:
    lab2_loadinput(A, size, Time);
*/

    FILE* op;
    int i, j;

    if ((op = fopen("data_output","w")) == NULL){
        printf("Error opening the output file.\n");
        return 1;
    }

    fprintf(op, "%d\n\n", size);
    fprintf(op, "%lf\n\n", Time);
    for (i = 0; i < size; i++) {
        for (j = 0; j< size; j++)
            fprintf(op, "%d\t", A[i][j]);
        fprintf(op, "\n");
    }
    fclose(op);
    return 0;
}
 
int** CreateMat(int size){
    /* Allocate memory for an int square array
    -----
    Input:
        size    size of array
    
    -----
    Output:
        ** A    pointer to the new int array
    */
    int i;
    int ** A;
    A = malloc(size * sizeof(int*));
    for (i = 0; i < size; ++i){
        A[i] = malloc(size * sizeof(int));
    }
    return A;
}
 
int DestroyMat(int** A, int size){
    /* Free memory for an int square array
    -----
    Input:
        A       pointer to the array
        size    size of array
    
    */
    int i;
    for (i = 0; i < size; ++i){
        free(A[i]);
    }
    free(A);
    return 0;
}

int PrintMat(int** A, int size){
    /* Print an array
    -----
    Input:
        A       pointer to the array
        size    size of the array
    */
    int i, j;
    for (i = 0; i < size; ++i){
        for (j = 0; j < size; ++j){
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    return 0;
}
