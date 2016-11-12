#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include "conexion.h"
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		srand(time(NULL));
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		size_=200;
		FIN_JUEGO_=false;
		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
			  frec_pasos[i][j]=0;
		    }

		for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++)
		      mapa_solucion_[i][j]='?';


	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};

	int casillaDelante();
	int casillaIzquierda();
	int casillaDerecha();
	int casillaDetras();
	// ________________________________________________________
	// MIS FUNCIONES
	// ________________________________________________________

	bool obstaculo_estatico(char v);
	bool obstaculo_movil(char s);
	bool objeto_delante(char s);
	void giraMatriz();
	void ajustaMatriz();
private:
	//Variables de interaccion con el entorno grafico
	int size_;
	int pasos=0;
	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;

	//Variables necesarias
	int f_PK1, c_PK1, f_PK2, c_PK2, fila_, columna_,orientacion_final;
	int c_myPK1, f_myPK1, c_myPK2, f_myPK2;
	int f1,f2,c1,c2;
	bool  found_firstPK=false;
	bool  found_secondPK=false;
	bool foundPKS=false;
	int frec_pasos[200][200];
	int mapa_auxiliar[200][200];
	bool needFORWARD=false;
	bool needFORWARD_pt2=false;
	bool needBACK=false;
	bool haveSHOES=false;
	bool haveBIKINI=false;
	bool changingPICKUP_first_part=false;
	bool changingPICKUP_second_part=false;
	bool changingPICKUP_third_part=false;
	bool firstOBJECT=true;
	bool secondOBJECT=true;
	bool secondOBJECT_pt2=false;
	int esquina_primera_f,esquina_primera_c;
	int esquina_segunda_f,esquina_segunda_c;
	int num_objetos=0;
	bool haveMANSANITA=false;
	bool haveORO=false;
	bool haveOSCAR=false;
};

string ActionStr(Agent::ActionType);

#endif
