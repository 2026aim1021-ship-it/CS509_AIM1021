#ifndef MATRIX_H
#define MATRIX_H

extern int M,K,N;

extern int A[1000][1000];
extern int B[1000][1000];
extern int C1[1000][1000];
extern int C2[1000][1000];

void readInput(char *filename);
void multiply();
void blockMultiply(int blockSize);
void printResult(int C[1000][1000]);
int checkEqual();

#endif
