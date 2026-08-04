#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/matrix.h"

int main(int argc,char *argv[]){
    if (argc<2){
        printf("Usage: %s inputfile blocksize\n",argv[0]);
        return 1;
    }

    int blockSize = 32;
    if (argc>=3){
        blockSize = atoi(argv[2]);
    }

    readInput(argv[1]);
    printf("Simple Multiplication : \n");
    clock_t start1 = clock();
    multiply();
    clock_t end1 = clock();
    double time1 = ((double)(end1-start1))/CLOCKS_PER_SEC * 1000;

    printf("Block Multiplication: \n");
    clock_t start2 = clock();
    blockMultiply(blockSize);
    clock_t end2 = clock();
    double time2 = ((double)(end2-start2))/CLOCKS_PER_SEC*1000;

    printf("Result Matrix:\n");
    printResult(C1);
    printf("Execution time: %f ms\n\n",time1);

    printf("Result Matrix:\n");
    printResult(C2);
    printf("Execution time: %f ms\n\n",time2);

    if (checkEqual())
        printf("Both Results match\n");
    else
        printf("Results do not mathc\n");

    return 0;
}
