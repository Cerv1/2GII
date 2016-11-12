#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv[]){
    if(argc<2){
        fprintf(stderr, "\nFalta numero de elementos \n");
        exit(-1);
    }
    int n = atoi(argv[1]), i, k, j;

    int a[n][n], b[n][n], c[n][n];

    printf("\nInicializando matriz resultado!");
    for(i=0; i<n; i++)
        for(k=0; k<n; k++)
            a[i][k] = 0;

    printf("\nValores matriz B: ");
    for(i=0; i<n; i++){
        printf("\n");
        for(k=0; k<n; k++){
            b[i][k] = i+k+2;
            printf("[%d]", b[i][k]);
        }
    }
    printf("\nValores matriz C: ");
    for(i=0; i<n; i++){
        printf("\n");
        for(k=0; k<n; k++){
            c[i][k] = i+k+2;
            printf("[%d]", c[i][k]);
        }
    }

    printf("\n\nCalculando multiplicacion de matrices!");
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            for(k=0; k<n; k++)
                a[i][j] += b[i][k] * c[k][j];

    printf("\n\nValor componente [0][0] del resultado: %d", a[0][0]);
    printf("\nValor componente [%d][%d] del resultado: %d", n-1, n-1, a[n-1][n-1]);
    printf("\n\n");
    return(0);
}
