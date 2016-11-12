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

#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int controller=0;
vector<bool> found; //vector que dice si se ha ejecutado o no los programas.

struct program{
    string name;
    double exe_time;
    double frecuencia;

    program(string n, double e, double f){
        name=n;
        exe_time=e;
        frecuencia=f;
    }
};

void Execution(const program & x){
    cout << "Ejecutando: " << x.name << endl;
    sleep(x.exe_time);
}

void Rewind(const vector<program> cinta){
    controller=0;
}

void Load(vector<program> & cinta, const program & x){
    cout << "Cargando el programa " << x.name << " al final de la cinta" << endl;
    cinta.push_back(x);
    found.push_back(false);
    sleep(1);
}

//Greedy ejecuta los programas segun tama�o de ejecucion
void Greedy_Size(vector<program> & cinta){

    program aux= cinta[0];

    double menor=cinta[0].exe_time;
    //Buscamos
	for(controller; controller<cinta.size(); controller++){

            if(menor > cinta[controller].exe_time && !found[controller]){
                    menor=cinta[controller].exe_time;
                    aux= cinta[controller];

            }


        Execution(cinta[controller]);
        found[controller]=true;
        Rewind(cinta);
    }

}
//Greedy ordena los programas segun frecuencia de ejecucion
void Greedy_Frequency(vector<program> & cinta){

    for(int i=0; i<cinta.size(); i++){
        Execution(cinta[i]);
    }
}


//Greedy ordena los programas segun frecuencia/tama�o de ejecucion
void Greedy_Hybrid(vector<program> & cinta){

    for(int i=0; i<cinta.size(); i++){
        Execution(cinta[i]);
    }
}


int main(){

    vector<program> cinta;

	//Primer apartado de la pr�ctica. Orden no decreciente de tama�o de programa.
    program E("VLC",0.5, 0.1);
	program D("Unity",1, 0.15);
	program C("Doom",2, 0.25);
	program B("Netbeans",5, 0.3);
	program A("Autocad", 6, 0.2);

    //Inicializamos el vector y rebobinamos
    Load(cinta,B);
    Rewind(cinta);
    Load(cinta,D);
    Rewind(cinta);
    Load(cinta,A);
    Rewind(cinta);
    Load(cinta,E);
    Rewind(cinta);
    Load(cinta,C);
    Rewind(cinta);

    Greedy_Size(cinta);


    return 0;
}
