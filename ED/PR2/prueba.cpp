#include "conjunto.h"
#include "crimen.h"
#include "fecha.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
	
/** @brief lee un fichero de delitos, linea a linea
    @param[in] s nombre del fichero
    @param[in,out] C conjunto sobre el que se lee
    @return true si la lectura ha sido correcta, false en caso contrario
    */
    bool load(conjunto & C, const string & S){
    	clock_t start, end;
    	ifstream fe;
    	string cadena;
    	int contador=0;
    	bool resultado=false;
   		double dif=0;

    	cout << "Abrimos " << S << ": " << endl;
    	fe.open(S.c_str(), ifstream::in);

    	if(fe.fail())
    		cerr << "Error al abrir el fichero " << S << "..." << endl;

    	else{
    		getline(fe, cadena, '\n'); // Leemos la cabecera del fichero

    		while(!fe.eof()){
    			
                getline(fe, cadena, '\n');
                if(!fe.eof()){
                    // Convertimos la cadena a crimen
                    crimen aux;
                    aux = cadena;

                    // Insertamos la cadena (el crimen) en el conjunto
                    //Para medir la eficiencia de insertar colocamos aquí el start=clock();
                    C.insert(aux);
                    //Para medir la eficiencia de insertar colocamos aquí end=clock();

                  	//Buscamos un crimen en el conjunto.
                    start=clock();
                    C.find(aux.getID());
                    end=clock();
                    dif=end-start;
                    contador++;
                    cout << contador << "   " << dif/CLOCKS_PER_SEC << endl;
                }
    		}

            C.Ordena();
    		
            //cout << C << endl;

    		resultado=true;
    	}

    	fe.close();
    	return resultado;
    }

/* ------------------------------------------------ */

int main(){

    conjunto ChicagoDB;
    crimen d;
    fecha f;
 
    load(ChicagoDB, "crimenes.csv");

   	return 0;
}
