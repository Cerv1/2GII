#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int  A[5000][5000];
int  B[5000][5000];
int  C[5000][5000];

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "\n[ERROR] - Debe introducir introducir dimension. \n");
        exit(-1);
    }

    int N = atoi(argv[1]);
    int multiB=1;
    int multiA=3;
    
    struct timespec cgt1, cgt2;
    double ncgt;

    if ((N <= 0) || (N > 4999)) {
        fprintf(stderr, "\nEl tamaño tiene que ser un valor menor que 5000 y mayor que 0. \n");
        exit(-1);
    }

    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k+=4){
            A[i][k]   = multiA++;
            A[i][k+1] = multiA++;
            A[i][k+2] = multiA++;
            A[i][k+2] = multiA++;
        }
    }

    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k+=4){
            B[i][k]   = multiB++;
            B[i][k+1] = multiB++;
            B[i][k+2] = multiB++;
            B[i][k+3] = multiB++;
        }
    }


    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k+=4){
            C[i][k]   = 0;
            C[i][k+1] = 0;
            C[i][k+2] = 0;
            C[i][k+3] = 0;
        }
    }
        

    clock_gettime(CLOCK_REALTIME, &cgt1);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k+=4){
                C[i][j] += B[i][k] * A[k][j];
                C[i][j] += B[i][k+1] * A[k+1][j];
                C[i][j] += B[i][k+2] * A[k+2][j];
                C[i][j] += B[i][k+2] * A[k+3][j];
            }
        }
    }

    clock_gettime(CLOCK_REALTIME, &cgt2);
    
    ncgt = (double) (cgt2.tv_sec - cgt1.tv_sec) + (double) ((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));

    printf("\tTiempo:\t%8.6f\n", ncgt);

    return 0;
}
