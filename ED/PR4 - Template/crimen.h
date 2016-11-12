/*
 * crimen.h
 *
 * Copyright  (C) Juan F. Huete
*/
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <vector>
#include <iostream>
#include "fecha.h"
using namespace std;

//! Clase crimen, asociada a la definición de un crimen
/*! crimen::crimen,  .....
 * Descripción contiene toda la información asociada a un crimen.

 @todo Implementa esta clase, junto con su documentación asociada

*/


class crimen{
 public:

 	/** @brief Constructor primitivo de la clase.
	*/
	crimen();

	/** @brief Constructor de copia de la clase.
		@param[in] c crimen a copiar.
	*/
	crimen(const crimen& x);

	/** @brief Establecer el ID de un crimen.
		@param[in] id ID a establecer.
	*/
	void setID(long int & id);

	/** @brief Establecer el número del caso de un crimen.
		@param in s Número del caso.
	*/
	void setCaseNumber(const string &  s);

	/** @brief Establecer la fecha de un caso.
		@param d Fecha a establecer.
	*/
	void setDate(const fecha & d);

	/** @brief Establecer si se produce un arresto o no.
		@param a Se produce arresto -> True / No se produce arresto -> False
	*/
	void setArrest(bool a);

	/** @brief Establecer si es un crimen doméstico.
		@param d Es crimen doméstico -> True / No es crimen doméstico -> False
	*/
	void setDomestic(bool d);

	/** @brief Obtener el ID de un crimen.
		@return Devuelve el ID.
	*/
	long int getID( ) const;

	/** @brief Obtener el número del caso.
		@return Devuelve el número del caso.
	*/
	string getCaseNumber( ) const;

	/** @brief Obtener la descripción del crimen.
		@return string con la descripción del caso.
	*/
	string getDescription() const;

    /** @brief Obtener si hay arresto.
        @return bool true si hay arresto, false en caso contrario.
    */
    bool getArrest() const;

	/** @brief Obtener el IUCR del crimen.
		@return string con el IUCR del caso.
	*/
	string getIUCR()const;

	/** @brief Asignar un IUCR a un crimen.
		@param[in] string con el IUCR a asignar.
	*/
	void setIUCR(string new_IUCR);

	/** @brief Asignar una descripción a un crimen.
		@param[in] string con la descripción a asignar.
	*/
	void setDescription(string new_Descr);

	/** @brief Devuelve la fecha del crimen.
		@return Devuelve la fecha del crimen.
	*/
  	fecha getDate( ) const;

 	/** @brief Copia en un crimen los datos de otro pasado como string.
		@param[in] string con los datos a copiar de otro crimen.
	*/
  	crimen & operator=(const string & datos);

	/** @brief Iguala dos crímenes.
		@param c Crimen a copiar en el que lo llama.
		@return Devuelve una copia del crimen.
	*/
   	crimen & operator=(const crimen & c);

	/** @brief Compara si son iguales dos crímenes.
		@param x Crimen a comparar.
		@return Devuelve true si son iguales y false si no lo son.
	*/
	bool operator==(const crimen & x) const;

	/** @brief Compara si un conjunto es mayor que otro.
		@param x Crimen a comparar.
		@return Devuelve true si x es mayor que el que lo llama. False en otro caso.
	*/
   	bool operator<(const crimen & x) const;

    class ComparacionPorFecha {
      public:
     bool operator()(const crimen &a, const crimen &b) {
       return (a.getDate() < b.getDate()); // devuelve verdadero si el crimen a precede a b en el tiempo
     }
   };

   class ComparacionPorID {
     public:
    bool operator()(const crimen &a, const crimen &b) {
      return (a.getID() < b.getID()); // devuelve verdadero si el crimen a precede a b en el tiempo
    }
  };

  class ComparacionPorIUCR {
    public:
   bool operator()(const crimen &a, const crimen &b) {
     return (a.getIUCR() < b.getIUCR()); // devuelve verdadero si el crimen a precede a b en el tiempo
   }
 };


 private:

	/** @brief Imprime todas las entradas del crimen.
		@post No se modifica el crimen original.
	*/
	friend ostream& operator<< (ostream&, const crimen&);

   // ATRIBUTOS //

	//ID : identificador del delito
	long int ID;
	//CaseNumber : codigo del caso
	string CaseNumber;
	//Date fecha en formato mm/dd/aaaa hh:mm:ss AM/PM
	fecha Date;
	//IUCR : codigo del tipo de delito
	string IUCR;
	//PrimaryType : tipo de delito
	string PrimaryType;
	//Description : descripcion detallada del delito
	string Description;
	//LocationDescription : descripcion del tipo de localizacion
	string LocationDescription;
	//Arrest : booleano que expresa si hay arresto o no
	bool Arrest;
	//Domestic : booleano que expresa si el crimen es domestico o no
	bool Domestic;
	//Latitude : coordenada de latitud
	double Latitude;
	//Longitude : coordenada de longitud
	double Longitude;

};

	ostream& operator<< ( ostream& , const crimen& );


#include "crimen.hxx"
#endif
