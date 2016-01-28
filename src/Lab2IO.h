/*
Header for the Lab 2 IO functions
*/
#ifndef LAB2_H_INCLUDE
#define LAB2_H_INCLUDE

int Lab2_loadinput(int*** A, int* size);
int Lab2_saveoutput(int** A, int size, double Time);
int** CreateMat(int size);
int DestroyMat(int** A, int size);
int PrintMat(int** A, int size);

#endif
