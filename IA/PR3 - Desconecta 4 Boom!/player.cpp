
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

const int VALOR_MAXIMO=1500000;
const int VALOR_MEDIO=175;
const int VALOR_MINIMO=5;

// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

/*
            Comprueba si existe una secuencia de tamaño secuencia_meta en la vertical ascendete de la ficha
            en la posicion (fila,columna) del tablero
*/
int checkVerticalSuperior(const Environment &estado, int fila, int columna, int jugador, int secuencia_meta) {

	int secuencia_actual=0;

	for(int i=fila; i<7; i++) {
		if(estado.See_Casilla(i,columna) == jugador)
			secuencia_actual++;
		else
			break;
	}

	int ret = (secuencia_actual >= secuencia_meta) ? 1 : 0;
    return ret;
}

/*
            Comprueba si existe una secuencia de tamaño secuencia_meta en la vertical descendente de la ficha
            en la posicion (fila,columna) del tablero
*/
int checkVerticalInferior(const Environment &estado, int fila, int columna, int jugador, int secuencia_meta) {

	int secuencia_actual=0;

	for(int i=fila; i>=0; i--) {
		if(estado.See_Casilla(i,columna) == jugador)
			secuencia_actual++;
		else
			break;
	}

    int ret = (secuencia_actual >= secuencia_meta) ? 1 : 0;
    return ret;
}

/*
            Comprueba si existe una secuencia de tamaño secuencia_meta en la horizontal derecha de la ficha
            en la posicion (fila,columna) del tablero
*/
int checkHorizontalDerecha(const Environment &estado, int fila, int columna, int jugador, int secuencia_meta) {

	int secuencia_actual=0;

	for(int j=columna; j<7; j++) {
		if(estado.See_Casilla(fila,j) == jugador)
			secuencia_actual++;
		else
			break;
	}

    int ret = (secuencia_actual >= secuencia_meta) ? 1 : 0;
    return ret;
}

/*
            Comprueba si existe una secuencia de tamaño secuencia_meta en la horizontal izquierda de la ficha
            en la posicion (fila,columna) del tablero
*/
int checkHorizontalIzquierda(const Environment &estado, int fila, int columna, int jugador, int secuencia_meta) {

	int secuencia_actual=0;

	for(int j=columna; j>=0; j--) {
		if(estado.See_Casilla(fila,j) == jugador)
			secuencia_actual++;
		else
			break;
	}

    int ret = (secuencia_actual >= secuencia_meta) ? 1 : 0;
    return ret;
}

/*
            Comprueba si existe una secuencia de tamaño secuencia_meta en la diagonal ascendente y
            descendente de la ficha en la posicion (fila,columna) del tablero
*/
int checkDiagonal(const Environment &estado, int fila, int columna, int jugador, int secuencia_meta) {

	int total_secuencias=0;

	// Comprobamos los diagonales ascendentes
	double secuencia_actual = 0;

	int col=columna;

    // Comprobamos las diagonales ascendentes en primer lugar
	for(int i=fila; i<7; ++i){
		if(col>6)
			break;
		else if (estado.See_Casilla(i,col)==jugador)
			secuencia_actual++;
		else
			break;
		col++;

	}

    // Si se ha dado una secuencia mayor o igual que secuencia_meta aumentamos el numero total de secuencias
	if(secuencia_actual >= secuencia_meta)
		total_secuencias++;

    // Reestablecemos el valor de las variables para poder contar de nuevo la secuencia_actual
	secuencia_actual=0;
	col=columna;

    // Comprobamos los diagonales descendentes en segundo lugar
	for(int i=fila; i>=0; i--) {
		if(col>6)
			break;
		else if (estado.See_Casilla(i,col) == jugador)
			secuencia_actual++;
		else
			break;
		col++;

	}
    // Si se ha dado una secuencia mayor o igual que secuencia_meta aumentamos el numero total de secuencias
	if (secuencia_actual >= secuencia_meta)
		total_secuencias++;

	return total_secuencias;
}


int checkAll(const Environment &estado, int jugador, int longitud_secuencia) {

/*
    Para todo el tablero:
        Comprobamos que la casilla sea de nuestro jugador y en caso de serla buscamos las secuencias
        verticales, horizontales y diagonales de longitud longitud_secuencia.
*/

	int secuencias = 0;
	for (int i=0; i<7;i++) {
		for (int j=0; j<7;j++) {
			if (estado.See_Casilla(i,j) == jugador) {
				secuencias += checkVerticalSuperior(estado, i, j, jugador, longitud_secuencia);
                secuencias += checkVerticalInferior(estado, i, j, jugador, longitud_secuencia);
				secuencias += checkHorizontalDerecha(estado, i, j, jugador, longitud_secuencia);
                secuencias += checkHorizontalIzquierda(estado, i, j, jugador, longitud_secuencia);
				secuencias += checkDiagonal(estado, i, j, jugador, longitud_secuencia);
			}
		}
	}
	return secuencias;
}


// Funcion heuristica
double Valoracion(const Environment &estado, int jugador){

    double valor_heuristico=0;
    int enemigo = (jugador==1) ? 2:1;

    // Almacenamos el conjunto de secuencias según el número de fichas por el que esté compuesto para nosotros
    int secuencia_peor = checkAll(estado, jugador, 4);
    int secuencia_media =  checkAll(estado, jugador, 3);
    int secuencia_favorable =   checkAll(estado, jugador, 2);

    // Almacenamos el conjunto de secuencias según el número de fichas por el que esté compuesto para el contrincante
    int secuencia_favorable_enemigo = checkAll(estado, enemigo, 4);
    int secuencia_media_enemigo =  checkAll(estado, enemigo, 3);
    int secuencia_peor_enemigo =   checkAll(estado, enemigo, 2);


    // Penalizamos las secuencias largas de nuestro jugador
    valor_heuristico-=secuencia_peor*VALOR_MINIMO;
    valor_heuristico-=secuencia_media*VALOR_MEDIO;
    valor_heuristico-=secuencia_favorable*VALOR_MAXIMO;

    // Bonificamos las secuencias largas del contrincante
    valor_heuristico+=secuencia_favorable_enemigo*VALOR_MAXIMO;
    valor_heuristico+=secuencia_media_enemigo*VALOR_MEDIO;
    valor_heuristico+=secuencia_peor_enemigo*VALOR_MINIMO;

    return valor_heuristico;
}

// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;

    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
   valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, menosinf-1, masinf+1);


    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    return accion;
}


double Player::Poda_AlfaBeta(const Environment &tablero, int jugador, int prof, const int MAX_PROF,
    Environment::ActionType &accion, double alfa, double beta){
    if(prof==MAX_PROF || tablero.JuegoTerminado())
        return Valoracion(tablero, jugador);
    else{
        int last_accion=-1;
        double  temporal;
        Environment::ActionType accion_previa;
        Environment hijo=tablero.GenerateNextMove(last_accion);

        //NODO ALFA
        if((prof%2)==0){
            while(!(hijo==tablero)){
                temporal=Poda_AlfaBeta(hijo, jugador, prof+1,MAX_PROF, accion_previa, alfa, beta);
                // Si existe una jugada mejor, actualizamos el alfa.
                if(temporal > alfa){
                    alfa=temporal;
                    accion=static_cast<Environment::ActionType>(last_accion);
                }
                if(beta<=alfa){
                    break;
                }
                hijo=tablero.GenerateNextMove(last_accion);
            }
            return alfa;
        }

        //NODO BETA
        else{
            while(!(hijo==tablero)){
                temporal=Poda_AlfaBeta(hijo, jugador, prof+1,MAX_PROF, accion_previa, alfa, beta);
                // Si existe una jugada peor, actualizamos el beta.
                if(temporal < beta){
                    beta=temporal;
                    accion=static_cast<Environment::ActionType>(last_accion);
                }
                if(beta<=alfa){
                    break;
                }
                hijo=tablero.GenerateNextMove(last_accion);
            }
            return beta;
        }
    }
}
