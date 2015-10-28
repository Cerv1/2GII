#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"
using namespace std;
// ----------------------------------------------------------------------------
sem_t sem_estanquero;
sem_t sem_fumadores[3];


// función que simula la acción de fumar  como un retardo aleatorio de la hebra
void fumar(){ 
   //  inicializa la semilla aleatoria  (solo la primera vez)
   static bool primera_vez = true ;
	if(primera_vez){   
		primera_vez = false;
		srand(time(NULL));    
    }
   
   // calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
   const unsigned miliseg = 100U + (rand() % 1900U) ; 

   // retraso bloqueado durante 'miliseg' milisegundos
   usleep( 1000U*miliseg ); 
}
// ----------------------------------------------------------------------------

int ProducirIngrediente(){
	int ingrediente=rand()%3;
	return ingrediente;
}

void* estanquero(void*){
	int ingrediente;
	while(true){
		ingrediente=ProducirIngrediente();

		if(ingrediente == 0)
			cout << "El estanquero saca cerillas. " << endl;
		else if(ingrediente == 1)
			cout << "El estanquero saca tabaco." << endl;
		else 
			cout << "El estanquero saca papel." << endl;

		sem_post(&sem_fumadores[ingrediente]);
		sem_wait(&sem_estanquero);
	}
}



void* fumador_1(void*){
	while(true){
		sem_wait(&sem_fumadores[0]);
		sem_post(&sem_estanquero);
		cout << "El fumador [1] coge las cerillas y fuma." << endl;
		fumar();
	}


}

void* fumador_2(void*){
	while(true){
		sem_wait(&sem_fumadores[1]);
		sem_post(&sem_estanquero);
		cout << "El fumador [2] coge el tabaco y fuma." << endl;
		fumar();
	}


}

void* fumador_3(void*){
	while(true){
		sem_wait(&sem_fumadores[2]);
		sem_post(&sem_estanquero);
		cout << "El fumador [3] coge el papel y fuma." << endl;
		fumar();
	}


}


int main(){
 
	pthread_t hebra_estanquero, hebra_fumadores[3];

	sem_init(&sem_estanquero, 0, 0);
	sem_init(&sem_fumadores[0], 0, 0);
	sem_init(&sem_fumadores[1], 0, 0);
    sem_init(&sem_fumadores[2], 0, 0);

    pthread_create(&hebra_estanquero, NULL, estanquero, NULL);
    pthread_create(&hebra_fumadores[0], NULL, fumador_1, NULL);
    pthread_create(&hebra_fumadores[1], NULL, fumador_2, NULL);
    pthread_create(&hebra_fumadores[2], NULL, fumador_3, NULL);

    pthread_join(hebra_fumadores[0], NULL);
    pthread_join(hebra_fumadores[1], NULL);
    pthread_join(hebra_fumadores[2], NULL);
    pthread_join(hebra_estanquero, NULL);

   	return 0 ;
}
