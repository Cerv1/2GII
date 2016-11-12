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

    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            B[i][k] = multiA++;
        

    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            B[i][k] = multiB++;



    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            C[i][k] = 0;

    clock_gettime(CLOCK_REALTIME, &cgt1);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += B[i][k] * A[k][j];

    clock_gettime(CLOCK_REALTIME, &cgt2);
    
    ncgt = (double) (cgt2.tv_sec - cgt1.tv_sec) + (double) ((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));

    printf("\tTiempo:\t%8.6f\n", ncgt);

    return 0;
}
