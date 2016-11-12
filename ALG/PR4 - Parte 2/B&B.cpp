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

/*
Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.
Para emplear un algoritmo de ramificación y poda es necesario utilizar una cota inferior: un valor menor o
igual que el verdadero coste de la mejor solución (la de menor coste) que se puede obtener a partir de la
solución parcial en la que nos encontremos.
Para realizar la poda, guardamos en todo momento en una variable C el costo de la mejor solución obtenida
hasta ahora (que se utiliza como cota superior global: la solución óptima debe tener un coste menor a esta
cota). Esa variable puede inicializarse con el costo de la solución obtenida utilizando un algoritmo voraz
(como los utilizados en la practica 2). Si para una solución parcial, su cota inferior es mayor o igual que la
cota global (superior) entonces se puede realizar la poda.
Como criterio para seleccionar el siguiente nodo que hay que expandir del árbol de búsqueda (la solución
parcial que tratamos de expandir), se emplear el criterio LC o “más prometedor”.
En este caso consideraremos como nodo más prometedor aquel que presente el menor valor de cota
inferior.
Para ello se debe de utilizar una cola con prioridad que almacene los nodos ya generados (nodos vivos).
*/

//compilar: g++ TSPbandb.cpp -o TSPbandb
//ejecutar: ./TSPbandb berlin52.tsp

#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <string>
#include <algorithm>
#include <iomanip>      // std::setw
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <queue>          // std::priority_queue
#include <list>          // std::list
using namespace std;
using namespace std::chrono;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido óptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado según el orden óptimo, para poder dibujarlo con gnuplot
//--------------------------------------------------class CLParser------------------------------------------------
class CLParser
{
public:
    CLParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CLParser() {}
    string get_arg(int i);
    string get_arg(string s);

private:
    int argc;
    vector<string> argv;
    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char * argv_[],bool switches_on_){
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;

    if (switches_on){
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;

        while (true){
            if (it1==argv.end()) break;
            if (it2==argv.end()) break;
            if ((*it1)[0]=='-') switch_map[*it1]=*(it2);

            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i){
    if (i>=0&&i<argc)
        return argv[i];

    return "";
}

string CLParser::get_arg(string s){
    if (!switches_on) return "";

    if (switch_map.find(s)!=switch_map.end())
        return switch_map[s];

    return "";
}


void leer_puntos(string & nombre, map<int, pair<double, double> > & M) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;


    datos.open(nombre.c_str());
    if (datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        int i=0;
        while (i<n) {
            datos >> act >> p.first >> p.second;
            M[act] = p;
            i++;
        }

        datos.close();
    }
    else {
        cout << "Error de Lectura en " << nombre << endl;
    }
}

void leer_orden(string & nombre, vector<int> & V) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;

    datos.open(nombre.c_str());
    if (datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        V.reserve(n);
        int i=0;
        while (i<n) {
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
//--------------------------------------------------class CLParser------------------------------------------------

//Mostrar matriz
void mostrar_matriz(const vector< vector<int> > & m) {
    cout<<"La matriz es:"<<endl;
    cout<<setw(3);

    for(int i=0; i<m.size(); i++) {
        cout<<"Ciudad "<<i+1<<": "<<endl;
        for(int j=0; j<m[i].size(); j++){
            cout<<m[i][j]<<" ";
        }
        cout<<"\n\n";
    }
}

//Mostrar vector
void mostrar_vector(const vector<int> & m) {
    cout<<"El vector  es: "<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<m[i]<<"  ";
    }
    cout<<endl;
}

//Calcular distancia euclidea entre dos ciudades.
int distancia_euclidea(double xi,double yi,double xj,double yj) {
    double c1=(xj-xi)*(xj-xi);
    double c2=(yj-yi)*(yj-yi);
    c2+=c1;
    int distancia=sqrt(c2);
    return distancia;
}

//Creamos la matriz de distancias y asignamos la distancia entre si misma como -1.
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<int> > & matriz) {
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[i].size(); j++){
            if(i!=j)
                matriz[i][j]=distancia_euclidea(m[i+1].first,m[i+1].second,m[j+1].first,m[j+1].second);
        }
    }
}

//Rellenamos la columna de -1 para que esta no se vuelva a utilizar.
void descartar_columna(vector< vector<int> > & m,int colum) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++){
            if(colum==j)
                m[i][j]=-1;
        }
    }
}

//Introducimos como nodo inicial la ciudad 1 y devolvemos el vector de ciudades y la distancia.
vector<int> recorridoGreedy(vector< vector<int> >  matriz, int & d){

    // Almacena las ciudades segun una heurística greedy.
    vector<int>ciudades;

    // Variables auxiliares necesarias
    int nodo=0,min=0,pos=0,i=1,j=0;

    //introducimos el primer nodo en la solucion
    ciudades.push_back(nodo+1);

    for(; i<matriz.size(); i++) {
        j=1;
        while(matriz[nodo][j]==-1) {
            j++;
        }
        min=matriz[nodo][j];
        pos=j;
        for(; j<matriz[nodo].size(); j++) {
            if(matriz[nodo][j]!=-1 and min>matriz[nodo][j]) {
                min=matriz[nodo][j];
                pos=j;
            }
        }
        nodo=pos;

        //Una vez encontrada la mejor ciudad la almacenamos en nuestro vector
        ciudades.push_back(nodo+1);
        descartar_columna(matriz,nodo);
        d+=min;
    }
    // Añadimos la primera distancia
    d+=matriz[nodo][0];
    return ciudades;
}

//Muestra las coordenadas de las ciudades
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
    pair<double,double> p;
    p=(m.find(1))->second;
    cout<<1<<" "<<p.first<<" "<<p.second<<endl;
}

//Calcula el camino más corto de entre todos sus hijos
vector<int> calcularMenorArista(const vector< vector<int> > & m){
    //Creamos vector de salida del tamaño=numero de ciudades
    vector<int> salida(m.size());

    int min=0,j;

    for(int i=0; i<m.size(); i++) {
        min=m[i][0];                            // Suponemos la ciudad actual como la mejor, la de menor distancia
        j=1;
        //Sirve para recorrer la matriz de manera triangular, ahorrando computo ya que se repiten los datos
        if(min==-1) {                           // Si es ella misma
            min=m[i][1];                       // Avanzamos de columna
            j++;
        }
        for(; j<m[i].size(); j++) {
            if(m[i][j]<min && m[i][j]!=-1)	// Si la ciudad actual es menor que la mejor ciudad anterior, actualiza
                min=m[i][j];
        }
        salida[i]=min;                                  // Almacena la nueva mejor ciudad y avanza al siguiente nivel
    }
    return salida;
}

int distanciaCiudades(int c1,int c2,const vector< vector<int> > & m) {
    return m[c1-1][c2-1];       //-1 porque la ciudad 1 esta en la posicion 0

}
//--------------------------------------------------class Solucion------------------------------------------------
class Solucion {
public:

    Solucion(int tama){
        pos_e=distancia=estimador=0;
        //Empezamos en la ciudad 1
        solucion.push_back(1);
        ciudadesRestantes.assign(tama-1,0);//-1 ya que la ciudad 1 ya esta dentro
        crearCiudades();
    }

    //Creamos la lista de ciudades
    void crearCiudades() {
        //Empezamos en la ciudad 2 ya que la 1 está almacenada
        int i=2;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            *it=i;
            i++;
        }
    }

    void primeraCotaGreedy(const vector< vector<int> >  & matriz) {
        solucion=recorridoGreedy(matriz,distancia);
        ciudadesRestantes.clear();
    }

    int getDistancia() {
        return distancia;
    }

    //Calcula la cota local a partir del vector de aristas menores
    //En arista_menor en la posicion 0, tenemos la ciudad 1.
    void calcularCotaLocal(const vector<int> & arista_menor){
        estimador=distancia;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            estimador+=arista_menor[(*it)-1];
        }
        //Añadimos siempre la arista de la primera ciudad, consiguiendo un estimador mas preciso
        estimador+=arista_menor[0];
    }

    int CotaLocal() const {
        return estimador;
    }

    bool EsSolucion(int tama) {
        return solucion.size()==tama;
    }

    //Devuelve en un vector el resto de ciudades por añadir
    vector<int> resto_ciudades() {
        vector<int> resto_ciudades;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            resto_ciudades.push_back(*it);
        }
        return resto_ciudades;
    }

    //Añade una ciudad al vector junto a sus distancias
    void anadirciudad(int a,const vector< vector<int> >  &m) {
        //Le volvemos a restar uno ya que la ciduad n, en la matriz es la n-1
        distancia+=distanciaCiudades(solucion.back(),a,m);
        solucion.push_back(a);
    }

    //Quita una ciudad del vector
    void quitarCiudad(const vector< vector<int> > & m) {
        //Le volvemos a restar uno ya que la ciudad n, en la matriz es la n-1
        distancia-=distanciaCiudades(solucion[solucion.size()-2],solucion.back(),m);
        solucion.pop_back();
    }

    void eliminarCiudadIndice(int a) {
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            if(*it==a) {
                ciudadesRestantes.erase(it);
                break;
            }
        }
    }

    void anadircidudadRestante(int a) {
        ciudadesRestantes.push_back(a);
    }

    //Calcula la distancia que llevamo
    int Evalua(const vector< vector<int> > & m) {
        distancia+=distanciaCiudades(solucion.back(),1,m);
        return distancia;
    }

     //Ordenados de menor a mayor
    bool operator<( const Solucion & s) const {
        return estimador > s.estimador;
    }

    void mostrar() {
        cout<<" Las ciudades son: "<<endl;
        for(int i=0; i<solucion.size(); i++) cout<<solucion[i]<<"   ";
        cout<<solucion[0]<<endl;
        cout<<"La distancia es: "<<distancia<<endl;
    }

    vector<int> devolverSolucion() {
        return solucion;
    }

private:
    vector<int> solucion; // Almacenamos la solucion
    int pos_e; // Posicion de la ultima decision en solucion
    int distancia;
    int estimador; // Valor del estimador para el nodo solucion
    list<int> ciudadesRestantes;
};


//--------------------------------------------------class Solucion------------------------------------------------
//////////////////////////////////////////////////////////////
Solucion Branch_and_Bound(const vector< vector<int> > & matriz,const vector<int> & arista_menor,int tama){
    //Vector que almacenara el resto de ciudades
    vector<int> ciudades_restantes;

    priority_queue<Solucion> Q; // Vector con los nodos vivos.

    // e_nodo -> Nodo a expandir
    // mejor_solucion=obvio
    Solucion e_nodo(tama), mejor_solucion(tama) ;

    // Inicializamos la mejor solucion a la cota greedy
    mejor_solucion.primeraCotaGreedy(matriz);

    //Nuestra cota global es la distancia actual de nuestra mejor solucion
    int CG=mejor_solucion.getDistancia();

    int distancia_actual=0;
    long long podas=0;
    long long nodosExpandidos=0;
    long long  maxNodosVivos=0;

    // Lista de nodos vivos
    Q.push(e_nodo);

    //Mientras que queden nodos vivos y la CotaLocal sea menor que la global
    while ( !Q.empty() && (Q.top().CotaLocal() < CG) ){

        if(maxNodosVivos<Q.size())
            maxNodosVivos=Q.size();

        e_nodo = Q.top();           // Actualizamos el nodo a expandir con el primer nodo de la cola
        Q.pop();                             // Lo eliminamos de la cola de nodos vivos
        ciudades_restantes=e_nodo.resto_ciudades(); // Actualizamos las ciudades restantes

        //Para todas las ciudades restantes
        for(int i=0; i<ciudades_restantes.size(); i++) {
            e_nodo.anadirciudad(ciudades_restantes[i],matriz);      // Añadimos una posible ciudad
            e_nodo.eliminarCiudadIndice(ciudades_restantes[i]);    // La quitamos de ciudades restantes
            if ( e_nodo.EsSolucion(tama) ) {
                distancia_actual = e_nodo.Evalua(matriz);
                if (distancia_actual < CG) {                                                    // Si es mejor, actualiza
                    CG = distancia_actual;
                    mejor_solucion = e_nodo;
                }
                else{
                    podas++;
                }
            }
            else {
                e_nodo.calcularCotaLocal(arista_menor);
                if (e_nodo.CotaLocal()<CG ){                            //Si existe un nuevo camino mas corto, añade la ciudad
                    // Si la cota local es < que la cota global, expandimos, si no la ignoramos
                    Q.push( e_nodo );
                    nodosExpandidos++;
                }
            }
            e_nodo.quitarCiudad(matriz);    // La ultima que se ha añadido
            e_nodo.anadircidudadRestante(ciudades_restantes[i]);   //Añadimos la ultima que se quito
        }
    }
    cout << "EL numero de podas es : " << podas<<endl;
    cout << "El numero de nodos expandidos es: "<<nodosExpandidos<<endl;
    cout << "El maximo de nodos vivos es: " << maxNodosVivos << endl;
    return mejor_solucion;
}


////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[]){

    // Un map con las posicion y las dimensiones.
    map<int, pair<double, double> >  m;

    // Creamos una matriz con la distancia entre dos ciudades
    vector< vector<int> >  matriz;

    // Vector con la secuencia de ciudades optima
    vector<int> ciu;

    vector<int> menor_arista;
    int tama=0,distancia=0;

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> totalbb;
    //----------------------------------------------------------------------------------------

    // Calcular matriz, menor_arista y m.
    string fp;
    if (argc<2) {
        cout << "Error Formato:  tsp puntos" << endl;
        exit(1);
    }
    CLParser cmd_line(argc,argv,false);
    fp=cmd_line.get_arg(1);
    leer_puntos(fp,m);
    tama=m.size();
    matriz.resize(tama, vector<int>(tama,-1));
    calcular_matriz(m,matriz);
    menor_arista=calcularMenorArista(matriz);

    tantes= high_resolution_clock::now();
    Solucion s=Branch_and_Bound(matriz,menor_arista,tama);
    tdespues= high_resolution_clock::now();

    totalbb= duration_cast<duration<double>>(tdespues-tantes);

    ciu=s.devolverSolucion();
    distancia=s.getDistancia();

    // Añadimos la ciudad 1
    mostrar_resultado(ciu,m);
    cout<<"Distancia: "<<distancia<<endl;
    cout << "Tiempo: " << totalbb.count() << endl;
    cout<<endl;
}
