//
// conjunto.hxx
// Implementación de los métodos de la clase Conjunto
//

#include "conjunto.h"
#include "crimen.h"
#include "fecha.h"


/** @brief constructor primitivo.	
	*/
	conjunto::conjunto(){
 		vc.resize(0);
	}
	
/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	conjunto::conjunto(const conjunto & d){
		if(this!=&d)
			vc=d.vc;
			
	}

		
/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un par con una copia de la entrada en el conjunto y con el segundo valor a true. 
	        Si no se encuentra devuelve la entrada con la definicion por defecto y false 
	@post no modifica el conjunto.
	\verbatim Uso
	if (C.find(12345).second ==true) cout << "Esta" ;
	else cout << "No esta";
	\endverbatim
	*/
	pair<conjunto::entrada,bool> conjunto::find(const long int & id) const{
		pair<conjunto::entrada,bool> aux;

		if(ExisteElemento(id)!=-1){
			aux.first=vc[ExisteElemento(id)];
			aux.second=true;
		}
		else{
			aux.first=vc[0];
			aux.second=false;
		}
		return aux;					
	}


/** @brief busca los crimenes con el mismo codigo IUCR
	@param icur identificador del crimen  buscar
	@return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findIUCR("0460");
	\endverbatim
	*/
	conjunto conjunto::findIUCR(const string & iucr) const{
		conjunto SimilIUCR;
		for(int i=0; i<size(); i++){
			if(iucr == vc[i].getIUCR())
				SimilIUCR.insert(vc[i]);
		}
		return SimilIUCR;
	}


/** @brief busca los crimenes que contienen una determinada descripcion 
	@param descr string que representa la descripcion del delito buscar
	@return Devuelve un  conjunto con todos los crimenes  que contengan descr en su descripcionR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findDESCR("BATTERY");
	\endverbatim
	*/
	conjunto  conjunto::findDESCR(const string & descr) const{
		conjunto SimilDescr;
		for(int i=0; i<size(); i++){
			if(descr == vc[i].getDescription())
				SimilDescr.insert(vc[i]);
		}
		return SimilDescr;
		
	}


/** @brief Inserta una entrada en el conjunto
	@param e entrada a insertar
	@return true si la entrada se ha podido insertar con éxito. False en caso contrario
	@post 	 Si e no esta en el conjunto, el size() sera incrementado en 1.
	*/
	bool conjunto::insert(const conjunto::entrada & e){
		bool no_esta=true;
		for(int i=0; i<this->size() && no_esta; i++){
			if(vc[i].getID()==e.getID())
				no_esta=false;	
		}		
		if(no_esta){
			vc.push_back(e);
	
		}		
		return no_esta;
	}

	
/** @brief Borra el delito dado un identificador. Busca la entrada con id en el conjunto  y si la encuentra la borra
	@param[in] id a borrar
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	bool conjunto::erase(const long int & id){
		bool result=false;
		if(ExisteElemento(id) != -1){
			vc.erase(vc.begin()+ExisteElemento(id));
			result=true;
		}		
		return result;
	}


/** @brief Borra una crimen con identificador dado por e.getID() en el conjunto. 
	Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra
	@param[in] entrada con e.getID() que queremos borrar, el resto de los valores no son tenidos en cuenta
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	bool conjunto::erase(const conjunto::entrada & e){
		return erase(e.getID());		
	}
         

/** @brief operador de asignación
	@param[in] org conjunto  a copiar.
	Crea un conjunto duplicado exacto de org.
	*/
	conjunto & conjunto::operator=(const conjunto & org){
		vc=org.vc;
	}


/** @brief numero de entradas en el conjunto 
	@post  No se modifica el conjunto.
	*/
	conjunto::size_type conjunto::size() const{
		return vc.size();
	}


/** @brief Chequea si el conjunto esta vacio
	@return true si size()==0, false en caso contrario.
	*/
	bool conjunto::empty() const{
		if(vc.size()==0)
			return true;
		else
			return false;
	}

	
/** @brief Chequea el Invariante de la representacion 
    @return true si el invariante es correcto, falso en caso contrario
	*/
  	bool conjunto::cheq_rep( ) const{
  		bool state=true;

  		for(int i=0; i<vc.size() && state==true; i++){
  			if(vc[i].getID() <= 0)
  				state=false;
  		}

  		for(int i=0; i<size()-1 && state==true; i++){
  			if(vc[i].getID() >= vc[i+1].getID())
  				state=false;
  		}
  		return state;
  	}


/** @brief	Busca en nuestro conjunto el elemento con el ID pasado por parámetro.
	@return Posición del elemento buscado. -1 si no lo encuentra
	*/
	long int conjunto::ExisteElemento(const long int &ID)const{
		bool encontrado=false;
   	    long int inicio = 0, centro, fin = size() - 1;
		while (inicio <= fin && !encontrado) {
			centro = (inicio + fin) / 2;
        	if (ID == vc[centro].getID())     	
            	encontrado=true;
        	else if(vc[centro].getID() > ID)
                fin = centro - 1;
             else
                inicio = centro + 1;
		} 

  		if(encontrado)
    		return centro;
   		else
    		return -1;    	
	}

/** @brief	Ordena el conjunto.
	*/
	void conjunto::Ordena(){
		sort(vc.begin(),vc.end());
	}