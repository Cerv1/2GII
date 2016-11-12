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

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido �ptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado seg�n el orden �ptimo, para poder dibujarlo con gnuplot

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


// Calcula la distancia eucl�dea entre dos puntos.
int distancia_euclidea(double xi, double yi, double xj, double yj){
	double X=xj-xi;
		   X*=X;
	double Y=yj-yi;
		   Y*=Y;

	double to_square_root=X+Y;

	int distance=sqrt(to_square_root);

	return distance;
}

void matriz_distancias(vector< vector<int> > & matrix, map<int,pair<double,double> > ciudades){
	for(int i=0; i<matrix.size(); ++i){
		for(int j=0; j<matrix.size(); ++j){
			if(i!=j){		// No calcularla sobre si mismo
				matrix[i][j]=distancia_euclidea(ciudades[i+1].first, ciudades[i+1].second, ciudades[j+1].first, ciudades[j+1].second);
			}
		}
	}
}

//Rellenamos una columna con un valor simb�lico para que no se vuelva a usar.
void discard_column(vector< vector<int> > & m,int colum) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            if(colum==j) {
                m[i][j]=-1;
            }
    }
}


vector<int> recorrido_greedy(vector< vector<int> >  matriz,int & d) {
    vector<int> ciudades;
    int ciudad=0,min=0,pos=0;
    int j;

    //Introducimos la primera ciudad en el vector resultado.
    ciudades.push_back(ciudad+1);

    for(int i=1; i<matriz.size(); ++i) { //contador
        j=1;
        while(matriz[ciudad][j]==-1) {
            j++;
        }
        min=matriz[ciudad][j];
        pos=j;
        while(j<matriz[ciudad].size()){
            if(matriz[ciudad][j]!=-1 && min>matriz[ciudad][j]) {
                min=matriz[ciudad][j];
                pos=j;
            }
        ++j;
        }
        ciudad=pos;
        ciudades.push_back(ciudad+1);
        discard_column(matriz,ciudad);
        d+=min;
    }
    //A�adimos la distancia de la �ltima ciudad al inicio
    d+=matriz[ciudad][0];
    //A�adimos de nuevo la ciudad 1.
    ciudades.push_back(1);

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
  vector< vector<int> > MATRIX;
  vector<int> V;
  int size=0, distance=0;

  string fp,fok;
   if (argc == 1) {
     cout << "Error Formato:  tsp puntos orden_correcto" << endl;
     exit(1);
   }

    CLParser cmd_line(argc,argv,false);

    fp = cmd_line.get_arg(1);
    leer_puntos(fp,M);
    size=M.size();
    MATRIX.resize(size, vector<int>(size,-1));
    matriz_distancias(MATRIX, M);
    V=recorrido_greedy(MATRIX, distance);
    fok = cmd_line.get_arg(2);
    leer_orden(fok,V);


    cout << "Dimension: " << V.size() << endl;
    for (int i=0;i<V.size(); i++)
      cout << V[i] << " " << M[V[i]].first << " " << M[V[i]].second << endl;

     cout << V[0] << " " << M[V[0]].first << " " << M[V[0]].second << endl;
    return 0;
}
