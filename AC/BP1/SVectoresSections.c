/* SumaVectoresC.c
 Suma de dos vectores: v3 = v1 + v2
*/

 #include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
 #include <stdio.h> // biblioteca donde se encuentra la función printf()
 #include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>

int main(int argc, char** argv){

    int i;
    double start;

    //Leer argumento de entrada (nº de componentes del vector)
    if(argc<2){
        printf("Faltan nº componentes del vector\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]); //Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4B)

    double *v1, *v2, *v3;
    v1 = (double*) malloc(N*sizeof(double)); // malloc necesita el tamaño en bytes
    v2 = (double*) malloc(N*sizeof(double)); // si no hay espacio suficiente malloc devuelve NULL
    v3 = (double*) malloc(N*sizeof(double));

    if((v1==NULL) || (v2==NULL) || (v3==NULL)){
        printf("Error en la reserva de espacio para los vectores\n");
        exit(-2);
    }

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            for(i=0; i<N*1/4; i++){
                v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
            }
            #pragma omp section
            for(i=N/4; i<N*2/4; i++){
                v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
            }
            #pragma omp section
            for(i=N/2; i<N*3/4; i++){
                v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
            }
            #pragma omp section
            for(i=3/4*N; i<N; i++){
                v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; //los valores dependen de N
            }
        }

        #pragma omp master
        start= omp_get_wtime();

        #pragma omp sections
        {
            #pragma omp section
            for(i=0; i<N*1/4; i++){
                v3[i] = v1[i] + v2[i];
            }
            #pragma omp section
            for(i=N/4; i<N*2/4; i++){
                v3[i] = v1[i] + v2[i];
            }
            #pragma omp section
            for(i=N/2; i<N*3/4; i++){
                v3[i] = v1[i] + v2[i];
            }
            #pragma omp section
            for(i=3/4*N; i<N; i++){
                v3[i] = v1[i] + v2[i];
            }
        }

        #pragma omp master
        printf("First v1=%f   First v2=%f    First v3=%f   Last v1=%f   Last v2=%f   Last v3=%f   Time elapsed: %f \n",v1[0],v2[0],v3[0],v1[N-1],v2[N-1],v3[N-1],omp_get_wtime()-start );

    }

    free(v1); //libera el espacio reservado para v1
    free(v2); //libera el espacio reservado para v2
    free(v3); //libera el espacio reservado para v3

    return 0;
}
