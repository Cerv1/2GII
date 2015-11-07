#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>

using namespace std ;
// ESCRIBIR ES PRODUCIR.
// LEER ES CONSUMIR.

// ---------------------------------------------------------------------
// constantes 
const unsigned num_items=50, tam_vector=10;   
  int buffer[tam_vector];   
  int primera_libre=0;
  sem_t puede_consumir;
  sem_t puede_producir;
  sem_t mutex;
  
// ---------------------------------------------------------------------

unsigned producir_dato(){
  static int contador = 0 ;
  cout << "producido: " << contador << endl << flush ;
  return contador++ ;
}

// ---------------------------------------------------------------------

void consumir_dato( int dato){
    cout << "dato recibido: " << dato << endl;
    
}
// ---------------------------------------------------------------------

void * productor( void * ){   
  for( unsigned i = 0 ; i < num_items ; i++ ){
  	//cout <<"buff   " << buffer[primera_libre-1]<< endl;
  	//cout << "PL " << primera_libre << "    "<<endl;
    
    int dato=producir_dato();  
    sem_wait(&puede_producir);
    sem_wait(&mutex);
   	buffer[primera_libre]=dato;
   	primera_libre++;
   	sem_post(&mutex);
   	sem_post(&puede_consumir);
 
    
    
  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * ){   
  for( unsigned i = 0 ; i < num_items ; i++ ){
  sem_wait(&puede_consumir);
  sem_wait(&mutex);
   int dato ;
   dato=buffer[primera_libre-1];
   primera_libre--;
   sem_post(&mutex);
   sem_post(&puede_producir);
   consumir_dato(dato) ;
   
   
   
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main(){

  // Inicializamos los semáforos.
  sem_init(&puede_consumir, 0, 0);  
  sem_init(&puede_producir, 0, tam_vector);
  sem_init(&mutex, 0, 1);

  // Creamos las hebras.
  pthread_t hebra_productora, hebra_consumidora;

  // Lanzamos las hebras.
  pthread_create(&hebra_productora, NULL, consumidor, NULL);
  pthread_create(&hebra_consumidora, NULL, productor, NULL);

  // Esperamos la finalizacion de las hebras.
  pthread_join(hebra_consumidora, NULL);
  pthread_join(hebra_productora, NULL);

  cout << "fin" << endl;
  
  return 0 ; 
}