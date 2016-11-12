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
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
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
void matriz_distancias(map<int, pair<double,double> > m, vector<vector<int> > &matriz){
    for(int i=0; i<matriz.size(); ++i)
        for(int j=0; j<matriz[i].size(); ++j)
            if(i!=j)
		          matriz[i][j]=distancia_euclidea(m[i+1].first, m[i+1].second, m[j+1].first, m[j+1].second);
}

/*
    @brief Devuelve la distancia entre dos ciudades

    Se debe tener en cuenta que, por ejemplo, la ciudad uno se corresponde con la ciudad 0 realmente, de ah� el ciudad1--

    @param ciudad1 primera matriz para obtener la distancia.
    @param ciudad2 segunda matriz para obtener la distancia.
    @param ciudades donde se almacenan las distancias entre ciudades.
*/
int distancia(int ciudad1, int ciudad2, const vector<vector<int> > &ciudades){
	ciudad1--;
	ciudad2--;
	return ciudades[ciudad1][ciudad2];
}


/*
    @brief Calcula la distancia total de una lista de ciudades.

    @param result, lista de las ciudades resultado.
    @param ciudades, Matriz de distancias, donde estan almacenadas las distancias.
*/

int distancia_total(const vector<int> &result,const vector<vector<int> > &ciudades) {
    vector<int>::const_iterator it1,it2;
    int dist=0;
    it1=result.begin();
    it2=result.begin();
    it1++;

    for(; it1!=result.end(); it1++) {
        dist+=distancia(*it1,*it2,ciudades);
        it2=it1;
    }
    return dist;
}

/*
    Crea un multimap con las ciudades insertadas en orden segun sus aristas
*/
multimap<int , pair<int,int> > calcular_aristas(const vector< vector<int> > & m) {
    multimap<int , pair<int,int> > result;
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) {
            if(j>i) { // comprueba si es una arista que no hayamos introducido ya
                result.insert(pair<int, pair<int,int> >(m[i][j],pair<int,int>(i+1,j+1)));
		/*
		 Inserto en el multimap una arista (estructura pair) que contiene la
		 distancia (m[i][j]) y las dos ciudades que une esa arista (pair<int,int> (i+1, j+1))
		*/
            }
        }
    }
    return result;
}

/*
     Busca una arista de un vértice en concreto (obj)
*/
list<pair<int,int> >::iterator buscarArista(list<pair<int,int> >& aux,int  obj){ // aux contiene las aristas
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++){
        if((*it).first==obj)
            return it;
        else if((*it).second==obj) // se comprueba si la arista es obj-ciudadQueSea o ciudadQueSea-obj
				   // ya que solo nos interesa la arista, no el sentido
            return it;
    }
    return aux.end();
}


/*
    Comprueba si un nodo es factible de ser añadido: cuando un vértice tiene dos aristas
*/
bool nodo_factible(list<pair<int, int> > &aux, const pair<int, int> &s){
	//s es el nodo que estamos comprobando (la arista que queremos comprobar), y aux el conjunto de todas las aristas
    int A=s.first, B=s.second, contA=0, contB=0;
    list<pair<int,int> >::iterator it=aux.begin();
    for(; it!=aux.end(); it++){ // compruebo todas las aristas
        if(A==(*it).first || A==(*it).second)   contA++;
        if(B==(*it).first || B==(*it).second)   contB++;
    }
    return (contA>1 || contB>1); // añado el nodo si ninguno de los dos vertices que une tienen mas de una arista
}

/*
    Si se añade un nodo que tiene dos aristas, se crea un ciclo
*/
bool hayciclos(list<pair<int, int> > aux, const pair<int, int> &s){ // s es el nodo que queremos añadir (arista que une dos vertices)
    int pos, res;
    list<pair<int,int> >::iterator it;
    pos=s.first; // pos es el vertice origen en el nodo que estamos comprobando
    res=s.second; // res es el vertice destino en el nodo que estamos comprobando
    it=buscarArista(aux,pos); // busco una arista que una el vertice origen de nuestro nodo con otro vertice cualquiera
    while(it!=aux.end()){ // mientras no se terminen las aristas
        if(pos==(*it).first)    pos=(*it).second;
	 //si pos es igual al vertice origen en la arista que estamos comprobando, avanzamos por la arista
        else    pos=(*it).first; // cambiamos de vertice origen
        aux.erase(it);
        it=buscarArista(aux,pos);
    }
    return pos==res; // compruebo si hemos llegado al vertice destino del nodo que estamos comprobando
}

/*
   Busco una arista que una el vertice obj con otro vertice, y cambio el valor de obj por el del otro vertice que une la arista
*/
list<pair<int,int> >::iterator buscar_y_avanzar(list<pair<int, int> > &aux, int &obj){
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++){
        if((*it).first==obj){
            obj=(*it).second;
            return it;
        }
        else if((*it).second==obj){
            obj=(*it).first;
            return it;
        }
    }
}

/*
    Devuelvo un vector con el camino de ciudades que recorro
*/
vector<int> camino(list<pair<int,int> >aux){
    vector<int> c; // guardo en c las ciudades que voy recorriendo en orden
    list<pair<int,int> >::iterator it=aux.begin();
    c.push_back((*it).first); // introduzco la primera ciudad
    int obj=(*it).second; // obj tiene guardada la segunda ciudad en el camino
    aux.erase(it);
    while(!aux.empty()){ // mientras no terminen las aristas
        c.push_back(obj); // agrego la ciudad guardada en obj
        it=buscar_y_avanzar(aux,obj);
        aux.erase(it);
    }
    c.push_back(c.front()); // agrego de nuevo la primera ciudad
    return c;
} // NOTA: ciudad = vertice


//cuando ya solo falta un nodo, lo introducimos en el camino y cerramos el ciclo.
void cerrar_ciclo(list <pair<int,int> > &aux, multimap<int, pair<int,int> > &a, int & d){
    int falta1=0, falta2=0, contadorA=0, contadorB=0;
    list<pair<int,int> >::iterator it1,it2;
    for(it1=aux.begin(); it1!=aux.end(); it1++){
        for(it2=aux.begin(); it2!=aux.end(); it2++){
            if((*it1).first==(*it2).first or (*it1).first==(*it2).second) contadorA++;
            if((*it1).second==(*it2).first or (*it1).second==(*it2).second) contadorB++;
            if(contadorA==2 and contadorB==2) break;
        }
        if(contadorA<2 and falta1==0) falta1=(*it1).first;
        else	if(contadorA<2 and falta2==0) falta2=(*it1).first;
        if(contadorB<2 and falta1==0) falta1=(*it1).second;
        else if(contadorB<2 and falta2==0) falta2=(*it1).second;
        contadorA=contadorB=0;
    }
    multimap<int , pair<int,int> >::iterator it;
    for(it=a.begin(); it!=a.end(); it++) {
        if((((*it).second).first==falta1 and ((*it).second).second==falta2)or  (((*it).second).first==falta2 and ((*it).second).second==falta1)) {
            aux.push_back((*it).second);
            d+=(*it).first;
        }
    }
}


/*
   Algoritmo greedy que selecciona los nodos en función del número de aristas
*/
vector<int> calcular_recorrido(multimap<int, pair<int,int> > &a, int &d){ // en a guardamos los nodos que vamos seleccionando, y d es la distancia recorrida
    list<pair<int,int> > aux;
    multimap<int, pair<int,int> >::iterator it=a.begin(); // me situo en el vertice del que partimos
    aux.push_back((*it).second);
    d += (*it).first;
    it++;
    while(it!=a.end()){ // itero sobre todas las aristas
        if(!nodo_factible(aux,(*it).second) && !hayciclos(aux,(*it).second)){ // si el nodo tiene dos aristas y no forma ciclos
            aux.push_back((*it).second); // agrego el nodo que estamos comprobando
            d += (*it).first; // sumo la distancia recorrida
        }
        it++;
    }
    cerrar_ciclo(aux,a,d); // cuando ya solo queda un nodo por recorrer, lo introuce y cierra el ciclo
    vector<int> c = camino(aux); // Saco el camino que hemos recorrido
    return c;
}



//Devuelve las ciudades ordenadas con sus coordenadas para poder crear el camino en una grafica
void mostrar_resultado(const vector<int> &result, const map<int,pair<double,double> > &m) {
    vector<int>::const_iterator it;
    for(it=result.begin(); it!=result.end(); it++) {
        pair<double,double> p;
        p=(m.find(*it))->second;
        cout<<*it<<" "<<p.first<<" "<<p.second<<endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]){
    multimap<int, pair<int,int> > aristas;
    map<int, pair<double,double> > m;       //guardamos en un map las posiciones y las dimensiones
    vector<vector<int> > matriz;                   //matriz con las distancias entre ciudades
    vector<int> ciudades;
    int tamanio, distancia=tamanio=0;
    string aux;
    if(argc<2){
        cout << "Error formato: ./tsp <puntos>" << endl;
        exit(1);
    }

    CLParser cmd_line(argc, argv, false);
    aux = cmd_line.get_arg(1);
    leer_puntos(aux,m);
    tamanio=m.size();
    matriz.resize(tamanio, vector<int>(tamanio,-1));
    matriz_distancias(m, matriz);

    aristas=calcular_aristas(matriz);
    ciudades=calcular_recorrido(aristas,distancia);
    mostrar_resultado(ciudades, m);

    cout << "\n\n" << distancia_total(ciudades, matriz);

    return 0;
}
