#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif
int main(int argc, char **argv) {

    int i, n=7, chunk, a[n], suma=0;

    if(argc<3){
        fprintf(stderr, "\nFaltan argumentos." );
        exit(-1);
    }

    n = atoi(argv[1]); if (n>20) n=20;
    printf("%i\n",n );
    chunk=atoi(argv[2]);
    for (i=0; i<n; i++) a[i] = i;

    #pragma omp parallel for num_threads(2) firstprivate(suma) \
                        lastprivate(suma) schedule(static,chunk)
        for (i=0; i<n+3; i++){
            suma = suma + a[i];
            printf(" thread %d suma a[%d]=%d suma=%d \n",omp_get_thread_num(),i,a[i],suma);
        }

    printf("Fuera de 'parallel for' suma=%d\n",suma);
}
