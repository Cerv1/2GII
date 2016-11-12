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

/** Este programa resuelve el problema comunmente conocido como
el problema del viajante de comercio que dice asi:

dado un conjunto de ciudades y una matriz con las distancias entre todas ellas,
un viajante debe recorrer todas las ciudades exactamente una vez, regresando al
punto de partida, de forma tal que la distancia recorrida sea minima. Mas
formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo
hamiltoniano de minimo peso de ese grafo.

En este caso emplearemos la heuristica del vecino mas cercano:
Dada una ciudad inicial v0, se agrega como ciudad siguiente
aquella vi (no incluida en el circuito) que se encuentre mas cercana a v0. El
procedimiento se repite hasta que todas las ciudades se hayan visitado.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class CLParser
{
public:

    CLParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CLParser(){}

    string get_arg(int i);
    string get_arg(string s);

private:

    int argc;
    vector<string> argv;

    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char * argv_[],bool switches_on_)
{
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;

    //map the switches to the actual
    //arguments if necessary
    if (switches_on)
    {
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;

        while (true)
        {
            if (it1==argv.end()) break;
            if (it2==argv.end()) break;

            if ((*it1)[0]=='-')
                switch_map[*it1]=*(it2);

            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i)
{
    if (i>=0&&i<argc)
        return argv[i];

    return "";
}

string CLParser::get_arg(string s)
{
    if (!switches_on) return "";

    if (switch_map.find(s)!=switch_map.end())
        return switch_map[s];

    return "";
}



/*
    Funcion que lee el fichero <nombre>.tsp, teniendo en cuenta el numero de ciudades y
    sus coordenadas particulares.
*/
void leer_puntos(string & nombre, map<int, pair<double, double> > & M){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;      //act --> determina la ciudad actual que estoy leyendo

    datos.open(nombre.c_str());
    if (datos.is_open()){
        datos >> s;         //ignoro "DIMENSION: "
        datos >> n;         //leo el numero de ciudades
        int i=0;
        while (i<n){
            datos >> act >> p.first >> p.second;        //leo la siguiente ciudad y sus coordenadas
            M[act] = p;
            i++;
        }
    datos.close();
    }
   else {
      cout << "Error de Lectura en " << nombre << endl;
    }
 }

/*
    Funcion que lee el fichero <nombre_ord>.opt.tour de las ciudades ya ordenadas segun
    recorrido obtenido. Solo tiene en cuenta el orden de las ciudades (el numero que las
    identifica).
*/
void leer_orden(string & nombre, vector<int> & V){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;      //act --> determina la ciudad actual que estoy leyendo

    datos.open(nombre.c_str());
    if (datos.is_open()){
        datos >> s;         //ignoro "DIMENSION: "
        datos >> n;         //leo el numero de ciudades
        V.reserve(n);
        int i=0;
        while (i<n){
            datos >> act;
            V.push_back(act);
            i++;
          }

        datos.close();
    }
   else {
      cout << "Error de Lectura en " << nombre << endl;
    }
 }
//////////////////////////////////////////////////////////////


/* @brief Función que calcula la distancia de una ciudad a otra con la
	  fórmula de euclides.

   @param xi Coordenada x de la primera ciudad
   @param yi Coordenada y de la primera ciudad
   @param xj Coordenada x de la segunda ciudad
   @param yj Coordenada y de la segunda ciudad


*/
int distancia_euclidea(const double &xi, const double &yi, const double &xj, const double &yj){
    double X=xj-xi;
           X*=X;
    double Y=yj-yi;
           Y*=Y;

    double to_square_root=X+Y;

    int distance=sqrt(to_square_root);
    return distance;
}

/* @brief Función que calcula una matriz que contiene la distancia de
	  cada ciudad al resto de ciudades

   @param m Estructura de datos "Map" que contiene las ciudades y sus coordenadas
   @param matriz Matriz donde se almacenaran las distancias entre las ciudades
   de la siguiente manera:

       - La distancia entre una ciudad y otra se calcula mediante la fórmula de euclides.
       - La distancia entre una ciudad y ella misma será -1 (no forma parte del conjunto de
	 candidatos).
       - Una vez se elija una ciudad para el conjunto de seleccionados, se colocarán las distancias
         del resto de ciudades a ella con valor -1 (dejan de ser seleccionables, ya se ha pasado
         por ellas).
       - Para estas dos últimas consideraciones inicializaremos la matriz a -1 en la función main
	 y en esta función solo calcularemos la distancia entre una ciudad y el resto.

*/
void matriz_distancias(vector< vector<int> > & matrix, map<int,pair<double,double> > & ciudades){
    for(int i=0; i<matrix.size(); ++i)
        for(int j=0; j<matrix.size(); ++j)
            if(i!=j)     // No calcularla sobre si mismo
		matrix[i][j]=distancia_euclidea(ciudades[i+1].first, ciudades[i+1].second, ciudades[j+1].first, ciudades[j+1].second);
}

/* @brief Función que pone una columna con valor -1. Esto significa que
         una vez se elija una ciudad para el conjunto de seleccionados (la
         correspondiente a la columna), se colocarán las distancias del resto
         de ciudades a ella con valor -1 (dejan de ser seleccionables, ya se
         ha pasado por ellas).

   @param m Matriz de distancias a modificar una columna.
   @param colum Columna a poner el valor -1.

*/
void discard_column(vector< vector<int> > & m,const int colum) {
    for(int i=0; i<m.size(); i++)
        for(int j=0; j<m[i].size(); j++)
            if(colum==j)
                m[i][j]=-1;
}

/* @brief Función greedy que resuelve el problema planteado.
	Elementos del algoritmo:

	- Conjunto de candidatos (C): Ciudades no visitadas.
	- Conjunto de seleccionados (S) : Ciudades ya visitadas (vector<int> ciudades).
	- Función solución: Que se hayan visitado todas las ciudades solo una vez.
	- Función de Factibilidad: Como suponemos que hay una carretera de cada ciudad
 	al resto, no hay función de factibilidad. Siempre podremos elegir una ciudad a
        la que no hemos ido.
	- Función de Selección: La ciudad más cercana.
	- Función objetivo: Devuelve el recorrido obtenido y su longitud.

   @param matriz Matriz de distancias.
   @param distancia Distancia del recorrido obtenido.
   @param nodo_inicial Nodo (posición de la matriz) desde el que parte el algoritmo.
*/
vector<int> recorrido_greedy(vector< vector<int> >  matriz,int & distancia, const int & nodo_inicial) {
    vector<int> ciudades; // Recorrido solución.
    // "ciudad" se refiere a la posición que ocupa la ciudad en la matriz de distancias.
    // "min" se refiere al siguiente camino con menor longitud desde la posición actual.
    // "pos" se refiere al último nodo que se ha colocado en el conjunto de candidatos.
    int ciudad=nodo_inicial,min=0,pos=0;
    int j;

    //Introducimos la ciudad inicial en el vector resultado.
    ciudades.push_back(ciudad+1);
    discard_column(matriz,ciudad); // La ciudad seleccionada ya no está
			           // en el conjunto de candidatos

    for(int i=1; i<matriz.size(); ++i) {
        j=0;

        while(matriz[ciudad][j]==-1) // Buscamos la primera ciudad que puede elegirse
            j++;

        min=matriz[ciudad][j];
        pos=j;
	// A partir de la primera ciudad elegible, calculamos que distancia es menor desde
	// el nodo actual. Dicho nodo se colocará en la variable "pos" y su distancia en
	// la variable "min".
        while(j<matriz[ciudad].size()){
            if(matriz[ciudad][j]!=-1 && min>matriz[ciudad][j]) {
                min=matriz[ciudad][j];
                pos=j;
            }
            j++;
        }
        ciudad=pos;
        ciudades.push_back(ciudad+1); // Añadimos la ciudad seleccionada.

        distancia+=min; // Actualizamos la distancia total del recorrido.

	if (i==matriz.size()-1) //Añadimos la distancia del nodo inicial a la ciudad final.
		distancia+=matriz[nodo_inicial][ciudad];

        discard_column(matriz,ciudad); // La ciudad seleccionada ya no está
			               //en el conjunto de candidatos
    }

    return ciudades;
}

//Devuelve las ciudades ordenadas con sus coordenadas para poder crear el camino en una grafica
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
}

int main(int argc, char * argv[])
{

   map<int, pair<double, double> >  M;
   vector< vector<int> > MATRIX; // Matriz de distancias
   vector<int> V;  // Orden de recorrido del camino solución.
   int num_ciudades=0; // Numero de ciudades
   int distance=0; // Distancia del camino solución.

   string fp,fok;
   if (argc != 3) {
     cout << "Error. Formato: TSP_Heuristica1 puntos nodo_inicial" << endl;
     exit(1);
   }
    int nodo_inicial = atoi(argv[2]);
    CLParser cmd_line(argc,argv,false);

    fp = cmd_line.get_arg(1);
    leer_puntos(fp,M);
    num_ciudades=M.size();
    MATRIX.resize(num_ciudades, vector<int>(num_ciudades,-1));
    matriz_distancias(MATRIX, M);

    //Impresión de la matriz de distancias
    /*for(int i=0; i<MATRIX.size(); i++) {
        for(int j=0; j<MATRIX[i].size(); j++)
            cout<<MATRIX[i][j]<<" ";
        cout<<endl;
    }*/

    V=recorrido_greedy(MATRIX, distance, nodo_inicial);

    // Descomentar para imprimir para la representación en GNUPLOT
    /*cout << "Dimension: " << V.size() << endl;
    mostrar_resultado(V,M);*/

    // Descomentar para imprimir la solución:
    cout<<"La distancia total es: "<< distance << " y el orden de las ciudades es:"<<endl;
    for(int i=0; i<V.size(); i++)
    	cout<<V[i]<<"  ";
    cout << endl;


    return 0;
}
