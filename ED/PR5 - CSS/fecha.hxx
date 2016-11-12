/** @brief fichero de implementacion de la clase fecha

*/

/** @brief Constructor sin parametros de la clase.
	@post Se crea un nuevo objeto fecha con parametros por defecto.
	*/
	fecha::fecha(){
		this->sec=1;
 		this->min=1;
 		this->hour=1;
 		this->mday=1;
 		this->mon=1;
 		this->year=2000;
	}

/** @brief Imprime datos en formato correcto (horas, minutos, etc)
	@param[in] param entero que se comprueba y/o formatea
	*/
	string fecha::DarFormato(int param) const{
		string aux;

		if(param<10)
			aux+=to_string(0);

		aux+=to_string(param);

	return aux;
	}

/** @brief Constructor de copia de la clase.
	@param[in] x fecha del que se copian los datos.
	@post Se crea un nuevo objeto del tipo fehca con los datos del objeteo x.
	*/
	fecha::fecha(const string & x){
		*this=x;
	}

/** @brief Iguala dos fechas.
	@param[in] f fecha a copiar en el que lo llama.
	@return Una copia de la fecha.
    */
 	fecha& fecha::operator=(const fecha & f){
		this->sec=f.sec;
		this->min=f.min;
		this->hour=f.hour;
		this->mday=f.mday;
		this->mon=f.mon;
		this->year=f.year;
	}

/** @brief Iguala dos fechas.
	@param[in] s fecha a copiar en el que lo llama.
	@return Una copia de la fecha.
    */
	fecha & fecha::operator=(const string & s){
		this->mday=stoi(s.substr(0,s.find_first_of("/")));
		this->mon=stoi(s.substr(s.find_first_of("/")+1, s.find_first_of("/")));
		this->year=stoi(s.substr(s.find_last_of("/")+1,4));
		this->hour=stoi(s.substr(s.find_last_of("/")+5, s.find_first_of(":")));
		this->min=stoi(s.substr(s.find_first_of(":")+1, s.find_first_of(":")));
		this->sec=stoi(s.substr(s.find_last_of(":")+1, s.size()));
	}

/** @brief Copiar los datos de una fecha a un string
	@post Se crea un objeto string con los datos de fecha
	*/
	string fecha::toString( )const{
		string aux;
		aux+=DarFormato(this->mday);
		aux+="/";
		aux+=DarFormato(this->mon);
		aux+="/";
		aux+=to_string(this->year);
		aux+=" ";
		aux+=DarFormato(this->hour);
		aux+=":";
		aux+=DarFormato(this->min);
		aux+=":";
		aux+=DarFormato(this->sec);

		return aux;
	}

/** @brief Compara si son iguales dos fechas.
	@param[in] f fecha a comparar.
	@return true si son iguales y false si no lo son.
	*/
	bool fecha::operator==(const fecha & f) const{
		if(this->sec == f.sec &&
			this->min == f.min &&
			this->hour == f.hour &&
			this->mday == f.mday &&
			this->mon == f.mon &&
			this->year == f.year)
			return true;
		else
			return false;
	}

/** @brief Compara si una fecha es menor que otra.
	@param[in] f fecha a comparar.
	@return true si es menor.
	*/
	bool fecha::operator<(const fecha & f)const{

		if(this->year > f.year)
			return false;
		else if(this->mon > f.mon)
			return false;
		else if(this->mday > f.mday)
			return false;
		else if(this->hour > f.hour)
			return false;
		else if(this->min > f.min)
			return false;
		else if(this->sec > f.sec)
			return false;
		else
			return true;
}

/** @brief Compara si una fecha es mayor que otra.
	@param[in] f fecha a comprar.
	@return true si es mayor.
	*/
	bool fecha::operator>(const fecha & f) const{
		if(this->year < f.year)
			return false;
		else if(this->mon < f.mon)
			return false;
		else if(this->mday < f.mday)
			return false;
		else if(this->hour < f.hour)
			return false;
		else if(this->min < f.min)
			return false;
		else if(this->sec < f.sec)
			return false;
		else
			return true;
	}

/** @brief Compara si una fecha es menor o igual que otra.
	@param[in] f fecha a comprar.
	@return true si es menor.
	*/
	bool fecha::operator<=(const fecha & f)const{
		if(this->year >= f.year)
			return false;
		else if(this->mon >= f.mon)
			return false;
		else if(this->mday >= f.mday)
			return false;
		else if(this->hour >= f.hour)
			return false;
		else if(this->min >= f.min)
			return false;
		else if(this->sec >= f.sec)
			return false;
		else
			return true;
	}

/** @brief Compara si una fecha es mayor que otra.
	@param[in] f fecha a comprar.
	@return true si es mayor.
	*/
	bool fecha::operator>=(const fecha & f) const{
		if(this->year <= f.year)
			return false;
		else if(this->mon <= f.mon)
			return false;
		else if(this->mday <= f.mday)
			return false;
		else if(this->hour <= f.hour)
			return false;
		else if(this->min <= f.min)
			return false;
		else if(this->sec <= f.sec)
			return false;
		else
			return true;
	}

/** @brief Compara si una fecha
	@param[in] f fecha a comparar.
	@return true si es mayor.
	*/
    bool fecha::operator!=(const fecha & f) const{
		if(this->sec != f.sec)
			return false;
		else if(this->min != f.min)
			return false;
		else if(this->hour != f.hour)
			return false;
		else if(this->mday != f.mday)
			return false;
		else if(this->mon != f.mon)
			return false;
		else if(this->year != f.year)
			return false;
		else
			return true;
}

/** @brief Muestra por pantalla un objeto del tipo fecha.
	@param[in] os flujo
	@param[in] f fecha a mostrar.
	@return La fecha por salida estandar.
	*/
	ostream& operator<< (ostream& os, const fecha & f){
    	os << f.DarFormato(f.mday) << "/" << f.DarFormato(f.mon) << "/"
 	   	<< f.year << " " << f.DarFormato(f.hour) << ":"
 	   	<< f.DarFormato(f.min) << ":" << f.DarFormato(f.sec);
		return os;
}
