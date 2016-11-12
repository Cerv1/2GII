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
#include <chrono>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace std::chrono;

/* Problema:
Se va a celebrar una cena de gala a la que asistiran n invitados. Todos se van a sentar
alrededor de una unica gran mesa rectangular, de forma que cada invitado tendria sentados
junto a el a otros dos comensales (uno a su izquierda y otro a su derecha). En funcion de
las caracteristicas de cada invitado (por ejemplo categoria o puesto, lugar de procedencia,...)
existen unas normas de protocolo que indican el nivel de conveniencia de que dos invitados se
sienten en lugares contiguos (supondremos que dicho nivel es un numero entero entre 0 y 100).
El nivel de conveniencia total de una asignacion de invitados a su puesto en la mesa es la suma
de todos los niveles de conveniencia de cada invitado con cada uno de los dos invitados sentados
a su lado. Se desea sentar a los invitados de forma que el nivel de conveniencia global sea lo
mayor posible. Diseñar e implementar un algoritmo vuelta atras para resolver este problema.
Realizar un estudio empirico de su eficiencia.

Compilar: g++ -O2 -std=c++11 -o final final.cpp std=c++11
Ejecutar: ./final <numero_comensales>
*/

/* Genera una matriz simetrica aleatoria de conveniencias en que cada par i,j
es la conveniencia de sentar al comensal i junto al comensal j. */
vector<vector<int>> generaMatrizConveniencias(int N){
    vector<vector<int>> matriz(N, vector<int>(N));
    srand ( time(NULL) ); // Para que se generen distintos números aleatorios con cada ejecución.
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i==j){
                matriz[i][j]=-1;
            }
            else{
                int random = rand()%(101); // Genera aleatorios entre 0 y 100.
                matriz[i][j] = random;
                matriz[j][i] = random;
            }
        }
    }
    return matriz;
}

// Imprime una matriz pasada como parametro
void imprimeMatriz(vector< vector<int> > & matriz)
{
	for(int i=0; i<matriz.size(); i++) {
        	for(int j=0; j<matriz[i].size(); j++)
            		cout << setw(3) << matriz[i][j] << setw(3);
        	cout<<endl;
	}
}

// Calcula la conveniencia de una mesa.
int calcularConvenienciaDeMesa(const vector<vector<int>> & matrizConveniencias, vector<int> & mesa) {
    // Casos particulares
    if (mesa.size() == 0) // Ningún comensal
        return 0;
    else if (mesa.size() == 1) // Un comensal
        return 0;
    else if (mesa.size() == 2) // 2 comensales
        return 2*matrizConveniencias[mesa[0]][mesa[1]] + 2*matrizConveniencias[mesa[1]][mesa[0]];

    // Calculamos los valores de 0 y N-1, ya que no están contiguos en el vector:
    int conv1 = matrizConveniencias[mesa[0]][mesa[mesa.size()-1]] +
		matrizConveniencias[mesa[0]][mesa[1]];
    int conv2 = matrizConveniencias[mesa[mesa.size()-1]][mesa[mesa.size()-2]]+
		matrizConveniencias[mesa[mesa.size()-1]][mesa[0]];
    int convTotal = conv1 + conv2;
    // Calculamos la conveniencia para el resto de comensales
    for (int i = 1; i < mesa.size() - 1; ++i)
        convTotal += matrizConveniencias[mesa[i]][mesa[i-1]] + matrizConveniencias[mesa[i]][mesa[i+1]];

    return convTotal;
}

// Calcula la solución al problema mediante fuerza bruta
// En el parametro vector<int> mejorMesa se guardara la mejor mesa calculada,
// y la función devuelve el valor a maximizar.
int FuerzaBruta(const vector<vector<int>> & matrizConveniencias, vector<int> & mejorMesa) {

    // Creamos una mesa ordenada, desde 0 hasta n.
    vector<int> mesa;
    for (int i = 0; i < matrizConveniencias.size(); ++i)
        mesa.push_back(i);

    // Calculamos la valoración de la mesa inicial
    int conv = calcularConvenienciaDeMesa(matrizConveniencias, mesa);
    mejorMesa = mesa;

    // Hacemos sucesivas permutaciones de la mesa con la funcion next_permutation
    // y comprobamos si el valor de esta nueva mesa es mejor que el de la anterior
    while (next_permutation(mesa.begin(),mesa.end())) {
        int nuevaConv = calcularConvenienciaDeMesa(matrizConveniencias, mesa);
        if (nuevaConv > conv) {
            mejorMesa = mesa;
            conv = nuevaConv;
        }
    }

    return conv;
}

//******************************** CLASE Solucion **************************//
class Solucion {
    vector<int> mesaPosible; // Va almacenando posibles soluciones
    vector<int> mesaSol; // Almacena la solución final
    int mejorValorConveniencia; // Almacena el mejor valor encontrado para la conveniencia (la mejor mesa)
    int numComensales; // Numero de comensales totales
    const vector< vector<int> > * matrizConv; // Apunta a la matriz de conveniencias creada
    static const int UMBRAL = 200; // Cota local para podar ramas con futuras peores soluciones

public:
    // Constructor por defecto.
    Solucion(const vector<vector<int>> * matrizConveniencias) {
        numComensales = matrizConveniencias->size();
        this->matrizConv = matrizConveniencias;
        mejorValorConveniencia = -1;
    }

    // Devuelve el numero de comensales totales de la solución
    int Size() {
        return numComensales;
    }

    // Inicia el vector solución a un valor nulo (-1)
    void Iniciar() {
        mesaPosible.push_back(-1);
    }

    //Genera el siguiente valor válido del dominio. Se usa la función count(inicio,fin,k), que
    //devuelve el número de coincidencias del valor k buscadas entre el inicio y el fin del vector
    //desde donde se llama.
    void SigValComp(int k) {
        ++mesaPosible[k];
        while(count(mesaPosible.begin(),mesaPosible.end(), mesaPosible[k]) > 1)
            	++mesaPosible[k];

    }

    // Testea si quedan valores de la solución por generar.
    bool TodosGenerados(int k) const{
        return (mesaPosible[k] == numComensales);
    }

    // Comprueba si la solución es factible (función de poda). Como restricciones
    // ponemos que la conveniencia actual no puede superar el valor de un cierto umbral.
    bool Factible(){

        int convenienciaActual = calcularConvenienciaDeMesa(*matrizConv, mesaPosible);
        int comensalesRestantes = numComensales - mesaPosible.size();

        int convMax = convenienciaActual + UMBRAL * comensalesRestantes;

        return (convMax > mejorValorConveniencia);
    }

    // Representa el proceso que se alcanza cuando se alcanza una solución.
    // Como estamos en un problema de optimización, comparamos con la mejor solución
    // alcanzada hasta el momento y actualizamos.
    void ProcesaSolucion() {
        int convenienciaActual = calcularConvenienciaDeMesa(*matrizConv, mesaPosible);
        if (convenienciaActual > mejorValorConveniencia) {
            mejorValorConveniencia = convenienciaActual;
            mesaSol = mesaPosible;
        }
    }

    // Nos permite eliminar el último valor de la mesa posible solución.
    // La utilizaremos porque el último valor que tendrá esta mesa es -1, y cuando tengamos
    // una solución final
    // queremos quitar ese valor nulo al que inicializabamos la mesa.
    void quitarUltimoComensal() {
        mesaPosible.erase(mesaPosible.end()-1);
    }

    // Metodo get para la mesa solución
    vector<int> getMesa() {
        return mesaSol;
    }


}; // FIN DE LA CLASE


//************************************ BACKTRACKING ******************************************/
// Método que implementa el backtracking recursivo
void backtrackingRecursivo(Solucion & Sol, int k) {

    Sol.Iniciar();
    Sol.SigValComp(k);
    while (!Sol.TodosGenerados(k)) {
        if (Sol.Factible())
            backtrackingRecursivo(Sol, k+1);
        if (k == Sol.Size()-1)
            Sol.ProcesaSolucion();
        Sol.SigValComp(k);
    }
    Sol.quitarUltimoComensal();
}

// Método que llama al backtracking recursivo y coloca el resultado en el parametro
// vector <int> & mesaSol. Devuelve el valor a maximizar del problema.
int backtracking(const vector<vector<int>> & matrizConveniencias, vector<int> & mesaSol) {
    Solucion sol(&matrizConveniencias);
    backtrackingRecursivo(sol,0);
    mesaSol = sol.getMesa();
    int conv = calcularConvenienciaDeMesa(matrizConveniencias, mesaSol);

    return conv;
}


/******************************** PROGRAMA PRINCIPAL *********************/
int main(int argc, char *argv[])
{

    //************************ ENTRADA DE DATOS **************************//
    if (argc != 2) {
	    cout << "Error. Formato: ./CenaDeGala tamanio_matriz" << endl;
	    exit(1);
    }
    int N = atoi(argv[1]);


    //********************* DECLARACIÓN DE VARIABLES ********************//
    int valorFuerzaBruta, valorBacktracking;
    vector<int> mesaFuerzaBruta, mesaBacktracking;
    // para calcular el tiempo de ejecución:
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> totalFuerzaBruta, totalBacktracking;


    //************************** CALCULOS *******************************//
    vector<vector<int>> matrizConveniencias = generaMatrizConveniencias(N);
    // Para fuerza bruta
    tantes = high_resolution_clock::now();
    valorFuerzaBruta = FuerzaBruta(matrizConveniencias, mesaFuerzaBruta);
    tdespues = high_resolution_clock::now();
    totalFuerzaBruta = duration_cast<duration<double>>(tdespues - tantes);

    // Para B&T
    tantes = high_resolution_clock::now();
    valorBacktracking = backtracking(matrizConveniencias, mesaBacktracking);
    tdespues = high_resolution_clock::now();
    totalBacktracking = duration_cast<duration<double>>(tdespues - tantes);


    //************************* MUESTRA DE RESULTADOS ************************//

    cout << endl << "Matriz de conveniencias: " << endl;
    imprimeMatriz(matrizConveniencias);

    cout << endl << "Solución mediante fuerza bruta: " << endl;
    for (int i=0; i < mesaFuerzaBruta.size(); i++)
       cout << mesaFuerzaBruta[i] << " ";

    cout << endl << "El valor de conveniencia de la mesa de fuerza bruta es de: " << valorFuerzaBruta << ". Tiempo: " << totalFuerzaBruta.count() << endl << endl;
    cout << endl << "Solución mediante backtracking:" << endl;

    for (int i=0; i < mesaBacktracking.size(); i++)
       cout << mesaBacktracking[i] << " ";

    cout << endl << "El valor de conveniencia de la mesa de backtracking es de: " << valorBacktracking << ". Tiempo: " << totalBacktracking.count() << endl << endl;

}
