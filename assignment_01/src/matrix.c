#include <stdio.h>
#include "matrix.h"

int M,K,N;

int A[1000][1000];
int B[1000][1000];
int C1[1000][1000];
int C2[1000][1000];

void readInput(char *filename){
    FILE *fp = fopen(filename,"r");

    if (fp==NULL){
        printf("Could not open file %s \n",filename);
    }

    fscanf(fp,"%d %d %d",&M,&K,&N);

    for (int i=0;i<M;i++){
        for (int j=0;j<K;j++)
            fscanf(fp,"%d",&A[i][j]);
    }

    for (int i=0;i<K;i++){
        for (int j=0;j<N;j++)
            fscanf(fp,"%d",&B[i][j]);
    }

    fclose(fp);
}

void multiply(){
    for (int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            int sum = 0;
            for(int k=0;k<K;k++){
                sum += A[i][k]*B[k][j];
            }
            C1[i][j] = sum;
        }
    }
}

void blockMultiply(int blockSize){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            C2[i][j] = 0;
        }
    }

    for(int ii=0;ii<M;ii=ii+blockSize){
        for(int jj=0;jj<N;jj=jj+blockSize){
            for(int kk=0;kk<K;kk=kk+blockSize){
                for(int i=ii;i<ii+blockSize && i<M;i++){
                    for(int j=jj;j<jj+blockSize && j<N;j++){
                        int sum = C2[i][j];
                        for(int k=kk;k<kk+blockSize && k<K;k++)
                            sum += A[i][k]*B[k][j];

                        C2[i][j] = sum;
                    }
                }
            }
        }
    }
}

void printResult(int C[1000][1000]){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }
}

int checkEqual(){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if (C1[i][j] != C2[i][j])
                return 0;
    
        }
    }
    return 1;
}
