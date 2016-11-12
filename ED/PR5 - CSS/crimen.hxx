/*
 * crimen.hxx
 *
 * Copyright  (C) Juan F. Huete
*/

#include "fecha.h"
#include "crimen.h"

//! Clase crimen, asociada a la definición de un crimen
/*! crimen::crimen,  .....
 Descripción contiene toda la información asociada a un crimen.

/** @brief Constructor primitivo de la clase.
 	@post Se crea un nuevo objeto del tipo crimen.
	*/
	crimen::crimen(){
		fecha vacia;

		this->ID = 0;
		this->CaseNumber = "default";
		this->Date = vacia;
		this->IUCR = "default";
		this->Description = "default";
		this->Arrest = false;
		this->Domestic = false;
		this->Latitude = 0.0;
		this->Longitude = 0.0;
	}

/** @brief Constructor de copia de la clase.
	@param[in] x Crimen del que se copian los datos.
	@post Se crea un nuevo objeto del tipo crimen con los datos del objeto x.
	*/
	crimen::crimen(const crimen& x){
		this->ID = x.ID;
		this->CaseNumber = x.CaseNumber;
		this->Date = x.Date;
		this->IUCR = x.IUCR;
		this->Description = x.Description;
		this->Arrest = x.Arrest;
		this->Domestic = x.Domestic;
		this->Latitude = x.Latitude;
		this->Longitude = x.Longitude;
	}

/** @brief Establecer el ID de un crimen.
	@param[in] id ID a establecer.
	*/
	void crimen::setID(long int & id){
		this->ID = id;
	}

/** @brief Establecer el número del caso de un crimen.
	@param[in] s Número del caso.
	*/
	void crimen::setCaseNumber(const string & s){
		this->CaseNumber = s;
	}

/** @brief Establecer la fecha de un caso.
	@param[in] d Fecha a establecer.
	*/
	void crimen::setDate(const fecha & d){
		this->Date = d;
	}

/** @brief Establecer si se produce un arresto o no.
	@param[in] a Se produce arresto -> True / No se produce arresto -> False
	*/
	void crimen::setArrest(bool a){
		this->Arrest = a;
	}

/** @brief Establecer si es un crimen doméstico.
	@param[in] d Es crimen doméstico -> True / No es crimen doméstico -> False
	*/
	void crimen::setDomestic(bool d){
		this->Domestic = d;
	}

/** @brief Obtener la descripción del crimen.
	@return string con la descripción del caso.
	*/
	string crimen::getDescription() const{
		return Description;
	}

/** @brief Obtener si hay arresto.
    @return bool true si hay arresto, false en caso contrario.
    */
    bool crimen::getArrest() const{
		return Arrest;
	}

/** @brief Obtener el IUCR del crimen.
	@return string con el IUCR del caso.
	*/
	string crimen::getIUCR()const{
		return IUCR;
	}

	double crimen::getLatitude()const{
		return Latitude;
	}

	double crimen::getLongitude()const{
		return Longitude;
	}

/** @brief Asignar un IUCR a un crimen.
	@param[in] string con el IUCR a asignar.
	*/
	void crimen::setIUCR(string new_IUCR){
		this->IUCR=new_IUCR;
	}

/** @brief Asignar una descripción a un crimen.
	@param[in] string con la descripción a asignar.
	*/
	void crimen::setDescription(string new_Descr){
		this->Description=new_Descr;
	}

/** @brief Obtener el ID de un crimen.
	@return El ID del crimen.
	*/
	unsigned int crimen::getID( ) const{
		return ID;
	}

/** @brief Obtener el número del caso.
	@return El número del caso.
	*/
  	string crimen::getCaseNumber( ) const{
  		return CaseNumber;
  	}

/** @brief Devuelve la fecha del crimen.
	@return La fecha del crimen.
	*/
  	fecha crimen::getDate( ) const{
  		return Date;
  	}

/** @brief Iguala dos crímenes.
	@param[in] c Crimen a copiar en el que lo llama.
	@return Una copia del crimen.
	*/
   	crimen & crimen::operator=(const crimen & c){
   		this->ID = c.ID;
   		this->CaseNumber = c.CaseNumber;
			this->Date = c.Date;
			this->IUCR = c.IUCR;
			this->Description = c.Description;
			this->Arrest = c.Arrest;
			this->Domestic = c.Domestic;
			this->Latitude = c.Latitude;
			this->Longitude = c.Longitude;
   	}

/** @brief Copia en un crimen los datos de otro pasado como string.
	@param[in] string con los datos a copiar de otro crimen.
	*/
   	crimen & crimen::operator=(const string & datos){
   		string aux=datos;

   		this->ID=stoi(aux.substr(0,aux.find_first_of(",")));

   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);

   		this->CaseNumber=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

		this->Date=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

  		if(aux.substr(0,aux.find_first_of(",")+1)!="")
  			aux.erase(0,aux.find_first_of(",")+1);

		this->IUCR=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

		this->Description=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

		this->Description+= " - ";
		this->Description+=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

		this->Description+= " - ";
		this->Description+=aux.substr(0,aux.find_first_of(","));

		if(aux.substr(0,aux.find_first_of(",")+1)!="")
			aux.erase(0,aux.find_first_of(",")+1);

		if(aux.substr(0,aux.find_first_of(","))=="true")
			this->Arrest=true;
		else
			this->Arrest=false;
		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);

   		if(aux.substr(0,aux.find_first_of(","))=="true")
   			this->Domestic=true;
   		else
   			this->Domestic=false;

   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);
   		if(aux.substr(0,aux.find_first_of(",")+1)!="")
   			aux.erase(0,aux.find_first_of(",")+1);

   		if(aux.substr(0,aux.find_first_of(","))!="")
   			this->Latitude=stod(aux.substr(0,aux.find_first_of(",")));

   		aux.erase(0,aux.find_first_of(",")+1);

   		if(aux.substr(0,aux.find_first_of(","))!="")
   			this->Longitude=stod(aux.substr(0,aux.find_first_of(",")));

   	}

/** @brief Compara si son iguales dos crímenes.
	@param[in] x Crimen a comparar.
	@return true si son iguales y false si no lo son.
	*/
	bool crimen::operator==(const crimen & x) const{

		bool estado=false;
		if(this->ID == x.ID &&
   		this->CaseNumber == x.CaseNumber &&
		this->Date == x.Date &&
		this->IUCR == x.IUCR &&
		this->Description == x.Description &&
		this->Arrest == x.Arrest &&
		this->Domestic == x.Domestic &&
		this->Latitude == x.Latitude &&
		this->Longitude == x.Longitude)
			estado=true;

		return estado;
	}

/** @brief Compara si un conjunto es menor que otro.
	@param[in] x Crimen a comparar.
	@return true si x es mayor que el que lo llama. False en otro caso.
	*/
   	bool crimen::operator<(const crimen & x) const{
   		return (this->ID < x.getID());
   	}

	ostream& operator<< ( ostream& , const crimen& x){
		cout << "\nID: " << x.ID << "\nCaseNumber: " << x.CaseNumber << "\nDate: " << x.Date
			 << "\nIUCR: " << x.IUCR << "\nDescription: " << x.Description << "\nArrest: "
			 << x.Arrest << "\nDomestic: " << x.Domestic << "\nLatitude: " << x.Latitude
			 << "\nLongitude: " << x.Longitude << endl;
	}
