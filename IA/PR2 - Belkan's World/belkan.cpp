#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>
#include <string>

using namespace std;

void CapturaFilaColumnaPK (string mensaje, int &fila, int &columna){
	if (mensaje.substr(0,8)=="PK fila:"){
		int pos = mensaje.find('c');
		string valor = mensaje.substr(9,pos-8);
		fila = atoi(valor.c_str());

		int pos2 = mensaje.find('.');
		pos = pos+8;
		valor = mensaje.substr(pos,pos2-1);
		columna = atoi(valor.c_str());
	}
}

void Agent::giraMatriz(){
	const int size_ = 200;
	char aux[size_][size_];
	bool firstPK=false;
	bool secondPK=false;

	//Rotamos el mapa
	for (int i = 0; i < size_; i++){
		int k = size_-1;
		for(int j = 0; j < size_; j++){
			if((i == f_myPK1)&&(j == c_myPK1)&&!firstPK){
				f_myPK1 = k;
				c_myPK1 = i;
				firstPK = true;
			}
			else if((i == f_myPK2)&&(j == c_myPK2)&&!secondPK){
				f_myPK2 = k;
				c_myPK2 = i;
				secondPK = true;
			}
			aux [k][i] = mapa_entorno_ [i][j];
			k--;
		}

		x_=c_myPK2;
		y_=f_myPK2;
	}

	//Cambiamos el mapa entorno por el rotado.
	for(int i = 0; i < size_; i++)
		for(int j = 0; j < size_; j++)
			mapa_entorno_[i][j] = aux[i][j];


	//Ahora guardamos en aux el mapa de objetos rotado.
	for (int i = 0; i < size_; i++){
		int k = size_-1;
		for(int j = 0; j < size_; j++){
			aux [k][i] = mapa_objetos_ [i][j];
			k--;
		}
	}

	//Cambiamos el mapa objetos por el rotado
	for(int i = 0; i < size_; i++)
		for(int j = 0; j < size_; j++)
			mapa_objetos_[i][j] = aux[i][j];



	//Repetimos el proceso con la matriz de frecuencias de paso
	int aux_pasos[size_][size_];

	for (int i = 0; i < size_; i++){
		int k = size_-1;
		for(int j = 0; j < size_; j++){
			aux_pasos [k][i] = frec_pasos [i][j];
			k--;
		}
	}

	//Sustituimos en el mapa de frecuencias
	for(int i = 0; i < size_; i++)
		for(int j = 0; j < size_; j++)
			frec_pasos[i][j] = aux_pasos[i][j];


	//Cambiamos la nueva orientacion:
		switch (orientacion_){
			case 0:	//Norte
				orientacion_ = 3;
				break;
			case 1:	//este
				orientacion_ = 0;
				break;
			case 2:	//sur
				orientacion_ = 1;
				break;
			case 3:	//oeste
				orientacion_ = 2;
				break;
		}
}

// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
		// Lo que tengas que hacer si eres reposicionado en el juego
		haveSHOES=false;
		haveBIKINI=false;
        for(int i=0; i<200; i++){
            for(int j=0; j<200; j++){
                mapa_entorno_[i][j]='?';
                mapa_objetos_[i][j]='?';
            }
        }
        x_=99;
        y_=99;
        orientacion_=3;
	}

	if(foundPKS){
		ajustaMatriz();
	}

	switch(last_accion_){
	  case 0: //avanzar
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // este
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}


	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}


	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);

	env->ActualizarMatrizUsuario(mapa_entorno_);

}

// -----------------------------------------------------------

void Agent::ajustaMatriz(){

		int size = 200;
		int adjusted_size = 100;
		char aux[adjusted_size][adjusted_size];
		char aux_obj[adjusted_size][adjusted_size];

		//Coordenadas clave para la matriz de 100
		esquina_primera_f=f_myPK1 - f_PK1;
		esquina_primera_c=c_myPK1 - c_PK1;
		esquina_segunda_f=esquina_primera_f + 99;
		esquina_segunda_c=esquina_primera_c + 99;


		int fila = 0;

		for(int i = esquina_primera_f; i < (esquina_primera_f + 100); i++, fila++){
			int columna = 0;
			for(int j = esquina_primera_c; j < (esquina_primera_c +100); j++, columna++){
					mapa_solucion_[fila][columna] = mapa_entorno_[i][j];
					if(mapa_solucion_[fila][columna] == '?')	mapa_solucion_[fila][columna] = 'S';
					if((fila == 0)|| (columna == 0) || (columna == 99)|| (fila == 99))   mapa_solucion_[fila][columna] = 'P';
			}
		}
}

bool Agent::obstaculo_estatico(char v){

	//Si tenemos zapatillas los ARBOLES no son obstáculos.
	if(haveSHOES){
		if(v=='M' or v=='P' or v=='D' or v=='A')
			return true;
		else
			return false;
	}

	// Si tenemos el bikini el AGUA no es obstáculo.
	else if(haveBIKINI){
		if(v=='B' or v=='M' or v=='P' or v=='D')
			return true;
		else
			return false;
	}

	// Detecsizeos los obstáculos.
	else{
		if(v=='B' or v=='M' or v=='P' or v=='D' or v=='A')
		return true;
	else
		return false;
	}

}

bool Agent::obstaculo_movil(char s){
	if(s>='e' && s<='z'){
		return true;
	}
	else
		return false;
}

bool Agent::objeto_delante(char s){
	if(s>=0 && s<=9)
		return true;

	return false;
}

int Agent::casillaDelante(){
		if(orientacion_==0){
			if(obstaculo_estatico(VISTA_[1]) || obstaculo_movil(SURFACE_[1]))	frec_pasos[y_-1][x_]=20000;
			if(objeto_delante(SURFACE_[1]))		frec_pasos[y_-1][x_]=-1;
			return frec_pasos[y_-1][x_];
		}
		else if(orientacion_==1){
			if(obstaculo_estatico(VISTA_[1]) || obstaculo_movil(SURFACE_[1]))	frec_pasos[y_][x_+1]=20000;
			return frec_pasos[y_][x_+1];
		}
		else if(orientacion_==2){
			if(obstaculo_estatico(VISTA_[1]) || obstaculo_movil(SURFACE_[1]))   frec_pasos[y_+1][x_]=20000;
			return frec_pasos[y_+1][x_];
		}
		else if(orientacion_==3){
		 	if(obstaculo_estatico(VISTA_[1]) || obstaculo_movil(SURFACE_[1]))	frec_pasos[y_][x_-1]=20000;
			return frec_pasos[y_][x_-1];
		}
}



int Agent::casillaIzquierda(){
	if(orientacion_==0){
		return frec_pasos[y_][x_-1];
	}
	else if(orientacion_==1){
		return frec_pasos[y_-1][x_];
	}
	else if(orientacion_==2){
		return frec_pasos[y_][x_+1];
	}
	else if(orientacion_==3){
		return frec_pasos[y_+1][x_];
	}
}

int Agent::casillaDerecha(){
	if(orientacion_==0){
		return frec_pasos[y_][x_+1];
	}
	else if(orientacion_==1){
		return frec_pasos[y_+1][x_];
	}
	else if(orientacion_==2){
		return frec_pasos[y_-1][x_];
	}
	else if(orientacion_==3){
		return frec_pasos[y_][x_-1];
	}
}

int Agent::casillaDetras(){
	if(orientacion_==0){
		return frec_pasos[y_+1][x_];
	}
	else if(orientacion_==1){
		return frec_pasos[y_][x_-1];
	}
	else if(orientacion_==2){
		return frec_pasos[y_-1][x_];
	}
	else if(orientacion_==3){
		return frec_pasos[y_][x_+1];
	}
}





Agent::ActionType Agent::Think()
{

	Agent::ActionType accion = actFORWARD; // Por defecto avanza


	 if(needFORWARD){
		if(!obstaculo_estatico(VISTA_[1]) && !obstaculo_movil(SURFACE_[1])){
			accion=actFORWARD;
			needFORWARD=false;
		}
		else
			accion=actTURN_R;
	}

	else if(changingPICKUP_first_part){
		changingPICKUP_first_part=false;


		if(firstOBJECT){
			firstOBJECT=false;
			accion=actPICKUP;
			cout << "** Primer objeto."<<endl;
			changingPICKUP_second_part=true;
			cout << "**SEcond objet: "<<secondOBJECT<<endl;
		}
		else if(secondOBJECT){
			secondOBJECT=false;
			accion=actPUSH;
			cout << "** Segundo objeto."<<endl;
			secondOBJECT_pt2=true;
		}
		else if(secondOBJECT_pt2){
			accion=actPICKUP;
			cout << "** Segundo objeto parte 2 " << endl;
			secondOBJECT_pt2=false;
			changingPICKUP_second_part=true;
		}
		else{
			accion=actPUSH;
			changingPICKUP_second_part=true;
			cout <<"Descarte"<<endl;
		}

	}

	else if(changingPICKUP_second_part){
		changingPICKUP_second_part=false;
		accion=actPOP;
	}

	else if(VISTA_[1] == 'A' && MOCHILLA_[0]=='0' && EN_USO_=='6'){
			changingPICKUP_first_part=true;
			accion=actIDLE;
			cout << "Cambio a bikini"<<endl;
	}

	else if(VISTA_[1]=='B' && MOCHILLA_[0]=='6' && EN_USO_=='0'){
			changingPICKUP_first_part=true;
			accion=actIDLE;
			cout << "Cambio a zapatillas"<<endl;
	}

	else if(SURFACE_[0]=='6'){
		changingPICKUP_first_part=true;
		accion=actIDLE;
	}

	else if(SURFACE_[0]=='0'){
		changingPICKUP_first_part=true;
		accion=actIDLE;
	}

	else if(needBACK){
		accion=actTURN_R;
		needFORWARD=true;
		needBACK=false;
	}

     else if(VISTA_[0]=='K' && !found_firstPK && !foundPKS){
		 if(obstaculo_movil(SURFACE_[1]) || obstaculo_estatico(VISTA_[1])){
 			accion=actTURN_R;
 			needFORWARD=true;
 		}
        cout <<" * MIS COORDENADAS PK1: "<< x_  << " "<< y_ << endl;
        found_firstPK=true;
        CapturaFilaColumnaPK(MENSAJE_,f_PK1, c_PK1);

        cout << "COORDENADA - PK1 - X: " << f_PK1 << endl;
        cout << "COORDENADA - PK1 - Y: " << c_PK1 << endl;

        f_myPK1=y_;
        c_myPK1=x_;

		 cout << "MI COORDENADA - PK1 - X: " << f_myPK1 << endl;
		  cout << "MI COORDENADA - PK1 - Y: " << c_myPK1 << endl;
    }

    else if(VISTA_[0]=='K' && found_firstPK && !found_secondPK && !foundPKS ){
        if(obstaculo_movil(SURFACE_[1]) || obstaculo_estatico(VISTA_[1])){
			accion=actTURN_R;
			needFORWARD=true;
		}

        cout << "MENSAJE: " <<MENSAJE_ << endl;

		CapturaFilaColumnaPK(MENSAJE_,f_PK2, c_PK2);
		if(c_PK2!= c_PK1 && f_PK2 != f_PK1){	//No es el PK anterior
			found_secondPK=true;
	        cout << "COORDENADA - PK2 - X: " << f_PK2 << endl;
	        cout << "COORDENADA - PK2 - Y: " << c_PK2 << endl;
			f_myPK2=y_;
	        c_myPK2=x_;
			cout << "MI COORDENADA - PK2 - X: " << f_myPK2 << endl;
	        cout << "MI COORDENADA - PK2 - Y: " << c_myPK2 << endl;
		}

    }

	else if(casillaDelante() <= casillaIzquierda() && casillaDelante() <= casillaDerecha() && (!obstaculo_estatico(VISTA_[1]) && !obstaculo_movil(SURFACE_[1]))){
		accion=actFORWARD;
		cout << "LA MENOR: DELANTE." << endl;
	}
	else if(casillaDerecha() <= casillaDelante() && casillaDerecha() < casillaIzquierda()){
		accion=actTURN_R;
		needFORWARD=true;
		cout << "LA MENOR: DERECHA." << endl;
	}
	else if(casillaIzquierda() <= casillaDerecha() && casillaIzquierda() < casillaDelante() && casillaIzquierda()<casillaDetras()){
		accion=actTURN_L;
		needFORWARD=true;
		cout << "LA MENOR: IZQUIERDA." << endl;
	}
	else if(casillaDetras() <= casillaDerecha() && casillaDetras() <casillaIzquierda() && casillaDetras() < casillaDelante()){
		accion=actTURN_R;
		cout << "NEED BACK" << endl;
	}
	else{
		accion=actTURN_L;
		needFORWARD=true;
		cout << "DESCARTE"<<endl;
	}
	//
	cout << " -------------------"<<endl;
	cout << "Delante:   " << casillaDelante()<<endl;
	cout << "Izquierda: "<<casillaIzquierda()<<endl;
	cout << "Derecha:   "<<casillaDerecha()<<endl;
	cout << "Detras:    "<<casillaDetras()<<endl;

	frec_pasos[y_][x_]++;

	if(EN_USO_=='0'){
		haveBIKINI=true;
		haveSHOES=false;
	}

	if(EN_USO_=='6'){
		haveSHOES=true;
		haveBIKINI=false;
	}

	// Tenemos dos PK. Podemos orientar el mapa.
	 if(found_secondPK && found_secondPK && !foundPKS){

		f1=f_PK1-f_PK2;
		f2=f_myPK1-f_myPK2;
		c1=c_PK1-c_PK2;
		c2=c_myPK1-c_myPK2;

		cout << "F1: " << f1 << endl;
		cout << "F2: " << f2 << endl;
		cout << "C1: " << c1 << endl;
		cout << "C2: " << c2 << endl;

		if(f1 == f2){
			cout << "Estamos orientados." << endl;
		}
		 else if(f1 == -f2){
			cout << "Estamos hacia abajo. Girar 180º." << endl;
			giraMatriz();
			giraMatriz();
		}
		else if(f1 == c2){
			cout << "Estamos girados. Girar 90º derecha." << endl;
			giraMatriz();
			giraMatriz();
			giraMatriz();
		}
		else if(f1==-c2) {
			cout << "Estamos girados. Girar 90º izquierda." << endl;
			giraMatriz();
		}

		foundPKS=true;


	esquina_primera_f = f_myPK1 - f_PK1;
	esquina_primera_c = c_myPK1 - c_PK1;
	esquina_segunda_f = esquina_primera_f + 99;
	esquina_segunda_c = esquina_primera_c + 99;

	}

	cout << "Tengo bikini: "<<haveBIKINI<<endl;
	cout << "Tengo zapatillas: "<<haveSHOES<<endl;
	// recuerdo la ultima accion realizada
	last_accion_ = accion;
	cout << Agent::pasos << endl;
	pasos++;
	return accion;

}
