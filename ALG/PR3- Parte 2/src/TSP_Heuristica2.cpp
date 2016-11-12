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
void matriz_distancias(vector< vector<int> > & matrix, map<int,pair<double,double> > & ciudades){
    for(int i=0; i<matrix.size(); ++i)
        for(int j=0; j<matrix.size(); ++j)
            if(i!=j)      // No calcularla sobre si mismo
		matrix[i][j]=distancia_euclidea(ciudades[i+1].first, ciudades[i+1].second, ciudades[j+1].first, ciudades[j+1].second);

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


/*
    @brief Calcula la distancia total de una lista de ciudades.
.a
    @param result, lista de las ciudades resultado.
    @param ciudades, Matriz de distancias, donde estan almacenadas las distancias.
*/

int distancia_total(const list<int> &result,const vector<vector<int> > &ciudades) {
    list<int>::const_iterator it1,it2;
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

 @brief Calcula el aumento de la distancia total que supone insertar una ciudad

 @param result, lista del ciudades solucion hasta el momento.
 @param m, matriz donde estan almacenadas las distancias.
 @param cuidad, ciudad que se desea insertar y de la cual se obtendr� el aumneto de distancia.

 @return pair<int list<int>::iterator> que contiene el aumento de distancia y un iterador a la ciudad.
 */
pair<int, list<int>::iterator> aumento_de_distancia(list<int> &result, const vector<vector<int> > &matriz, int ciudad){
	list<int>::iterator it1=result.begin(), it2=result.end(), pos=it1;
	it2--;
	int dist = distancia(*it1, ciudad, matriz) + distancia(*it2, ciudad, matriz);
	dist -= distancia(*it1, *it2, matriz); //dist guarda el aumento de la distancia
	it2=it1;
	it1++;
	while(it1 != result.end()){
		int a=*it1;
		int b=*it2;
		int dist2 = distancia(a, ciudad, matriz) + distancia(b, ciudad, matriz);
		dist2 -= distancia(a, b, matriz);
		if(dist2<dist){
			dist=dist2;
			pos=it1;
		}
		it2=it1;
		it1++;
	}
	return make_pair(dist,pos);
}

/*
    @brief Elige la ciudad con menor distancia a�adida.

 @param result,lista del ciudades solucion hasta el momento.
 @param m, matriz donde estan almacenadas las distancias.
 @param restantes, lista de nodos restantes a insertar.

 @return pair<int, list<int>::iterator>, una pareja con la ciudad_selec y un iterador a la misma.

*/
pair<int, list<int>::iterator> elegir_ciudad(list<int> &result, const vector<vector<int> > &matriz, list<int> &restantes){
	list<int>::iterator it, itselec;
	pair<int, list<int>::iterator> selec;
	bool b=false;
	int ciudad_selec;
	for(it=restantes.begin(); it!=restantes.end(); it++){
		pair<int, list<int>::iterator> selec2;
		int cit=*it;
		selec2=aumento_de_distancia(result, matriz, cit);
		if(b==false){
			b=true;
			selec=selec2;
			ciudad_selec=cit;
			itselec=it;
		}
		else if(selec2.first < selec.first){
			selec=selec2;
			ciudad_selec=cit;
			itselec=it;
		}
	}
	restantes.erase(itselec);
	return make_pair(ciudad_selec, selec.second);
}

/*
 @brief Inserta una ciudad en la posicion determinada por el iterador

 @param recorrido, lista de ciudades ya recorridas.
 @param ciudad, cuidad que se va a insertar.
 @param it, iterador que apunta a la posicion donde se va a almacenar la ciudad.

 */
void insertar_ciudad(list<int> &recorrido, int ciudad, list<int>::iterator it){
	recorrido.insert(it, ciudad);
}

/*
  @brief Funci�n greedy que resuelve el problema mediante insercion, mediante el criterio de mas barato antes.

    - Conjunto de candidatos (C): Ciudades no visitadas.
    - Conjunto de Seleccionados (S): Ciudades ya selccionadas.
    - Funcion solucion: Que se hayan visitado todas las ciudades solo una vez.
    - Funcion de factibilidad: Como suponemos que hay una carretera de cada ciudad al resto, no hay funci�n de factibilidad. Siempre podremos elegir una ciudad a la que no hemos ido.
    - Funcion de selccion: La ciudad que menos aumento de distancia suponga en el ciclo inicial.
    - FUncion objetivo: Devuleve el recorrido obtenido y su longitud.

    @param matriz, matriz de distancias.
    @param m, mapa donde se almacenan, las ciudades y sus coordenadas.
    @param d, distancia total del recorrido.

    return result, lista con el recorrido final.
*/
list<int> greedy_insercion(const vector<vector<int> > & matriz, const map<int, pair<double, double> > & m, int & d){
	int norte, sur, oeste;
	norte=sur=oeste=1;
	list<int> result;
	map<int, pair<double, double> >::const_iterator it=m.begin();
	list<int> restantes;
	restantes.push_back(1);
	pair<double, double> pnorte=(*it).second, psur=(*it).second, poeste=(*it).second;	//todas las posiciones a la primera ciudad de la lista
	it++;
	//Inicializacion.
	//bucle para escoger qu� ciudades incluimos en el triangulo (norte, sur, oeste)
    for( ; it!=m.end(); it++){
		restantes.push_back((*it).first);
		pair<double,double> p=(*it).second;
		int actual=(*it).first;
		if(p.first < poeste.first){
			poeste = p;
			oeste = actual;
		}
		else if(p.second > pnorte.second || (norte==oeste && norte==1)){
			pnorte = p;
			norte = actual;
		}
		else if(p.second < psur.second || (sur==oeste && sur==1)){
			psur = p;
			sur = actual;
		}
	}

	//como norte, sur, oeste forman el triangulo mas grande, los incluimos en la lista resultado <result>
	result.push_back(norte);
	result.push_back(sur);
	result.push_back(oeste);
	restantes.remove(norte);
	restantes.remove(sur);
	restantes.remove(oeste);
	//////////////
	while(restantes.size()>0){
		pair<int, list<int>::iterator> pres;
		pres=elegir_ciudad(result, matriz, restantes);
		insertar_ciudad(result, pres.first, pres.second);
	}
	result.push_back(*(result.begin()));
	d=distancia_total(result, matriz);
	return result;
}


//Devuelve las ciudades ordenadas con sus coordenadas para poder crear el camino en una grafica
void mostrar_resultado(const list<int> &result,const map<int,pair<double,double> > &m) {
    list<int>::const_iterator it;
    for(it=result.begin(); it!=result.end(); it++) {
        pair<double,double> p;
        p=(m.find(*it))->second;
        cout<<*it<<" "<<p.first<<" "<<p.second<<endl;
    }
}

int main(int argc, char * argv[])
{

   map<int, pair<double, double> > M;
   vector<vector<int> > matriz;
   list<int> ciudades;
   int tamanio=0, distancia=0;
   string aux;
   if(argc<2){
   	   cout << "Error formato: ./TSP_Heuristica2 <puntos>" << endl;
       exit(1);
   }
   CLParser cmd_line(argc, argv, false);
   aux = cmd_line.get_arg(1);
   leer_puntos(aux, M);
   tamanio=M.size();
   matriz.resize(tamanio, vector<int>(tamanio, -1));
   matriz_distancias(matriz, M);
   ciudades = greedy_insercion(matriz, M, distancia);
   mostrar_resultado(ciudades, M);

   cout << "\n\n" << distancia_total(ciudades, matriz);

   return 0;
}
