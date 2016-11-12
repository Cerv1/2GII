/* 
 * meteorito.h
 * 
 * Copyright  (C) Juan F. Huete
*/
 
#ifndef __FECHA_H
#define __FECHA_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;


//! Clase fecha, asociada a la 
/*! fecha::fecha,  .....
 * Descripción contiene toda la información asociada a una fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
 @todo Escribe la documentación de la clase
 @todo Implementar esta clase

*/
using namespace std;

class fecha {

public:

	/**@brief Constructor primitivo de la clase.
	*/
 	fecha (); 

	/**@brief Constructor de copia de la clase.
		@param[in] s string a copiar:
	*/
 	fecha (const string & s);

	/** @brief operador de asignación
		@param[in] f fecha a copiar.
		@post Crea una fecha duplicada exacta de f
	*/
 	fecha & operator=(const fecha & f);

	/** @brief operador de asignación
		@param[in] s string a copiar.
	*/
 	fecha & operator=(const string & s); 

	/** @brief Muestra el valor de sus atributos
		@return Devuelve la fecha convertida a un string
	*/
 	string toString( ) const; 

 	string DarFormato(int param) const;

// Operadores relacionales //

	/** @brief Compara si son iguales dos fechas.
		@param[in] f Fecha a comparar.
		@return Devuelve true si son iguales y false si no lo son.
	*/
 	bool operator==(const fecha & f) const;

	/** @brief Compara si una fecha es mayor que otra.
		@param[in] f Fecha a comparar.
		@return Devuelve true si f es mayor que el que lo llama. False en otro caso.
	*/
 	bool operator<(const fecha & f)const;

	/** @brief Compara si una fecha es menor que otra.
		@param[in] f Fecha a comparar.
		@return Devuelve true si f es menor que el que lo llama. False en otro caso.
	*/
 	bool operator>(const fecha & f) const;

	/** @brief Compara si una fecha es mayor o igual que otra.
		@param[in] f Fecha a comparar.
		@return Devuelve true si f es mayor o igual que el que lo llama.False en otro caso.
	*/
 	bool operator<=(const fecha & f)const;

	/** @brief Compara si una fecha es menor o igual que otra.
		@param[in] f Fecha a comparar.
		@return Devuelve true si f es menor o igual que el que lo llama.False en otro caso.
	*/
 	bool operator>=(const fecha & f) const;

	/** @brief Es un comparador de desigualdad
		@param[in] f Fecha a comparar.
		@return Devuelve true cuando f es distinta del que la llama.False en otro caso.
	*/
 	bool operator!=(const fecha & f)const;

private:
	
  	int  sec;   	//sec: segundos de 0 a 61
	
  	int  min;   	//min: minutos de 0 a 59
	
  	int  hour;  	//hour: horas de 0 a 24
	
  	int  mday;  	//mday: dia del menos de 1 a 31
	
  	int  mon;   	//mon: mes del año de 0 a 11
	
  	int  year; 		//year:año desde 2000

	/** @brief Imprime todas las entradas de las fechas.
		@post No se modifica la fecha original
	*/
	friend  ostream& operator<< ( ostream& os, const fecha & f); 
	};

	/** @brief imprime fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
	*/
 	ostream& operator<< ( ostream& os, const fecha & f); 

#include "fecha.hxx" // Incluimos la implementacion.

#endif
