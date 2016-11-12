/**
*       Prácticas realizadas por:
*
*           - Sergio Cervilla Ortega
*           - Daniel Díaz Pareja
*           - Marina Hurtado Rosales
*           - Adrián Morente Gabaldón
*           - Joaquín Rodríguez Claverías
*
*/

#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>


// generador de ejemplos para el problema del elemento en su posici�n. Para rellenar el vector de tama�o n, genera
//todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; despu�s obtiene una permutaci�n aleatoria de ese
//vector, se queda con los n primeros elementos, y los ordena de forma creciente

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

// Algoritmo básico para encontrar un número i tal que v[i] = i
// Simplemente compara cada valor del vector con su indice.
int finder(int begin, int end, int umbral, const vector<int> & myvector){
	bool rompe = false; // Variable que nos permite salir del bucle
			    // si encontramos una solución
	int res = -1;

	for(int i=begin; i<=end && !rompe; i++)
		if(i == myvector[i]){
		        res = i;
		        rompe=true;
		}

     	// Devolvemos el resultado, si es -1, no se ha encontrado ninguno.
     	return res;
}


int main(int argc, char * argv[])
{
  std::chrono::high_resolution_clock::time_point tantes, tdespues;
  int umbral = (atoi(argv[1]))/7;     // nuestro umbral sera el 7% del num de elementos
  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int m=2*n-1;

  int * T = new int[n];
  assert(T);
  int * aux = new int[m];
  assert(aux);

srand(time(0));
//genero todos los enteros entre -(n-1) y n-1
for (int j=0; j<m; j++) aux[j]=j-(n-1);

//algoritmo de random shuffling the Knuth (permutaci�n aleatoria)
for (int j=m-1; j>0; j--) {
   double u=uniforme();
   int k=(int)(j*u);
   int tmp=aux[j];
   aux[j]=aux[k];
   aux[k]=tmp;
}
//me quedo con los n primeros del vector
for (int j=0; j<n; j++) T[j]=aux[j];
//for (int j=0; j<n; j++) cout << T[j] << " ";

//Y ahora ordeno el vector T
vector<int> myvector (T, T+n);
vector<int>::iterator it;

sort(myvector.begin(),myvector.end());
int i=0;
// for (it=myvector.begin(); it!=myvector.end(); ++it){
//     cout << i << " " << *it<<endl;
//     i++;
// }
//   cout << endl;


delete [] aux;


// Cálculo e impresión de resultados
tantes = std::chrono::high_resolution_clock::now();
int encontrado=finder(0, myvector.size()-1, umbral, myvector);
tdespues = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> transcurrido;
transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues-tantes);
// if(encontrado!=-1)
//         cout << "El primer valor que coincide con su posicion es: " << encontrado << endl;
// else
//         cout << "No se han encontrado coincidencias..." << endl;

// cout << "Tiempo transcurrido: " << transcurrido.count() <<" segundos" <<std::endl;
cout << atoi(argv[1]) << "\t\t\t" << transcurrido.count() << endl;

return(0);
}
