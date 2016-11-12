/*! Implementacion  de la clase conjunto

*/

/** @brief constructor primitivo.
	*/
	template <class CMP>
	conjunto<CMP>::conjunto(){
 		vc.resize(0);
	}

/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	template <class CMP>
	conjunto<CMP>::conjunto(const conjunto<CMP> & d){
		if(this!=&d)
			this->vc=d.vc;
	}

/** @brief constructor de conjunto que contiene los elementos contenidos en el rango [ini,fin)
	@param[in] ini iterator que indica el inicio del rango
	@param[in] fin iterator que indica el fin del rango a copiar
	*/
	template <class CMP>
	conjunto<CMP>::conjunto(conjunto<CMP>::iterator ini, conjunto<CMP>::iterator fin){
		int i=0;
		while(ini!=fin){
			this.insert(this.begin()+i, *ini);
			i++;
		}
	}

/** @brief busca un determinado crimen en el conjunto
	@param[in] c crimen a buscar
	@return iterator que ubica al crimen en el conjunto
	*/
	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::find(const crimen & c){
		typename conjunto<CMP>::iterator tmp=begin();
		bool found=false;
		for(int i=0; i<vc.size() && !found; i++){
			if(tmp.ptr->vc[i] == c){
				found=true;
			}
			tmp.itv+=i;
		}
		return tmp;
	}

/** @brief busca un determinado crimen en el conjunto
	@param[in] c crimen a buscar
	@return const iterator que ubica al crimen en el conjunto
	*/
	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const crimen & c)const{
		typename conjunto<CMP>::const_iterator tmp=cbegin();
		bool found=false;
		for(int i=0; i<vc.size() && !found; i++){
			if(tmp.ptr->vc[i] == c){
				found=true;
			}
			tmp.c_itv+=i;
		}
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::lower_bound (const conjunto::entrada & x){
		typename conjunto<CMP>::iterator tmp(vc.begin());
		for(int i=0; i<vc.size(); i++){
			tmp.itv=lower_bound(vc.begin(), vc.end(), comp(vc[i],x));
		}
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::lower_bound (const conjunto::entrada & x)const{
		typename conjunto<CMP>::const_iterator tmp(vc.begin());
		for(int i=0; i<vc.size(); i++){
			tmp.c_itv=lower_bound(vc.begin(), vc.end(), comp(vc[i],x));
		}
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::upper_bound (const conjunto::entrada & x){
		typename conjunto<CMP>::iterator tmp(vc.begin());
		for(int i=0; i<vc.size(); i++){
			tmp.itv=upper_bound(vc.begin(), vc.end(), comp(vc[i],x));
		}
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::upper_bound (const conjunto::entrada & x)const{
		typename conjunto<CMP>::const_iterator tmp(vc.begin());
		for(int i=0; i<vc.size(); i++){
			tmp.c_itv=upper_bound(vc.begin(), vc.end(), comp(vc[i],x));
		}
		return tmp;
	}


/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo


	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::find(const long int & id){
		typename conjunto<CMP>::iterator tmp=begin();
		bool found=false;
		for(int i=0; i<vc.size() && !found; i++){
			if(tmp.ptr->vc[i].getID() == id){
				found=true;
			}
			tmp.itv+=i;
		}
		return tmp;
	}

/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo


	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const long int & id) const{
		typename conjunto<CMP>::const_iterator tmp=cbegin();
		bool found=false;
		for(int i=0; i<vc.size() && !found; i++){
			if(tmp.ptr->vc[i].getID() == id){
				found=true;
			}
			tmp.c_itv+=i;
		}
		return tmp;
	}


/** @brief busca los crimenes con el mismo codigo IUCR
	@param iucr identificador del crimen  buscar
	@return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findIUCR("0460");
	\endverbatim
	*/
	template <class CMP>
	 conjunto<CMP> conjunto<CMP>::findIUCR(const string & iucr) const{
		conjunto return_conjunto;
		for(int i=0; i<vc.size(); i++){
			if(iucr == vc[i].getIUCR())
				return_conjunto.vc.push_back(vc[i]);
		}
		return return_conjunto;
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
	template <class CMP>
	conjunto<CMP> conjunto<CMP>::findDESCR(const string & descr) const{
		conjunto return_conjunto;
		for(int i=0; i<vc.size(); i++){
			if(descr == vc[i].getDescription())
				return_conjunto.vc.push_back(vc[i]);
		}
		return return_conjunto;
	}


/** @brief Inserta una entrada en el conjunto
	@param e entrada a insertar
	@return true si la entrada se ha podido insertar con éxito. False en caso contrario
	@post Si e no esta en el conjunto, el size() sera incrementado en 1.
	*/
	template <class CMP>
	bool conjunto<CMP>::insert(const conjunto::entrada & e){
		bool insertado = false;
        for (int i =0; !insertado && i < vc.size(); )
            if(vc[i].getID()==e.getID())
				i++;
            else{
            	vc.insert(vc.begin()+i,e);
            	insertado = true;
            }
        if (!insertado)
			vc.push_back(e);
		return insertado;
	}

/** @brief Borra el delito dado un identificacador.
	Busca la entrada con id en el conjunto  y si la encuentra la borra
	@param[in] id a borrar
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	template <class CMP>
	bool conjunto<CMP>::erase(const long int & id){
		bool result=false;
		if(ExisteElemento(id) != -1){
			vc.erase(vc.begin()+ExisteElemento(id));
			result=true;
		}
		return result;
	}

/** @brief Borra una crimen con identificador dado por e.getID() en el conjunto.
	Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra
	@param[in] entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	template <class CMP>
	bool conjunto<CMP>::erase(const conjunto::entrada & e){
		return erase(e.getID());
	}

/** @brief operador de asignación
	@param[in] org conjunto  a copiar.
	Crea un conjunto duplicado exacto de org.
	*/
	template <class CMP>
	conjunto<CMP> & conjunto<CMP>::operator=(const conjunto & org){
		vc=org.vc;
	}

/** @brief numero de entradas en el conjunto
	@post  No se modifica el conjunto.
	*/
	template <class CMP>
	typename conjunto<CMP>::size_type conjunto<CMP>::size() const{
		return vc.size();
	}


/** @brief Chequea si el conjunto esta vacio
	@return true si size()==0, false en caso contrario.
	*/
	template <class CMP>
	bool conjunto<CMP>::empty() const{
		if(vc.size()==0)
			return true;
		else
			return false;
	}

/** @brief	Busca en nuestro conjunto el elemento con el ID pasado por parámetro.
	@return Posición del elemento buscado. -1 si no lo encuentra
	*/
	template <class CMP>
	long int conjunto<CMP>::ExisteElemento(const long int &ID)const{
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

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::busquedaBinaria (const crimen &d ){
		typename conjunto<CMP>::iterator tmp(vc.begin());
		int sup=vc.size()-1;
		int inf = 0;
		bool found=false;
		int medio=0;
		while (sup > inf && !found) {
			medio = (inf+sup)/2;
			if (!comp(vc[medio],d) && !comp(d,vc[medio]) )
				found=true;  // comparamos igualdad entre crimen
			else if (comp(vc[medio],d))
				inf = medio+1; // comparamos menor entre crimen
			else sup = medio-1;
		}
		if(found)
			tmp.itv+=medio;

	return tmp;
	}


// ================================= CLASS ITERATOR   =================================================/

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::begin(){
		typename conjunto<CMP>::iterator sal;
		sal.itv=vc.begin();
		sal.ptr=this;
		return sal;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::end(){
		typename conjunto::iterator sal;
		sal.itv = vc.end();
		sal.ptr=this;
		return sal;
	}

	template <class CMP>
	conjunto<CMP>::iterator::iterator(){

	}

	template <class CMP>
	conjunto<CMP>::iterator::iterator(const conjunto<CMP>::iterator & it){
		this->itv=it.itv;
		this->ptr=it.ptr;
	}

	template <class CMP>
 	const typename conjunto<CMP>::entrada & conjunto<CMP>::iterator::operator*() const{
		return *itv;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator++(int){
		typename conjunto<CMP>::iterator tmp(*this);
		itv++;
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator & conjunto<CMP>::iterator::operator++(){
		this->itv++;
		return *this;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator--(int){
		typename conjunto<CMP>::iterator tmp(*this);
		itv--;
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::iterator & conjunto<CMP>::iterator::operator--(){
		this->itv--;
		return *this;
	}

	template <class CMP>
	bool conjunto<CMP>::iterator::operator==(const conjunto<CMP>::iterator & it){
		return (itv==it.itv);
	}

	template <class CMP>
	bool conjunto<CMP>::iterator::operator!=(const conjunto<CMP>::iterator & it){
		return (itv!=it.itv);
	}


// ================================= CLASS CONSTANT ITERATOR    ========================================/
	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::cbegin() const{
		typename conjunto::const_iterator sal;
		sal.c_itv=vc.begin();
		sal.ptr=this;
		return sal;
	}

	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::cend() const{
		typename conjunto::const_iterator sal;
		sal.c_itv = vc.end();
		sal.ptr=this;
		return sal;
	}

	template <class CMP>
	conjunto<CMP>::const_iterator::const_iterator(){

	}

	template <class CMP>
	conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::const_iterator & it){
		this->c_itv=it.c_itv;
		this->ptr=it.ptr;
	}

	template <class CMP>
	conjunto<CMP>::const_iterator::const_iterator(const conjunto<CMP>::iterator & it){
		this->c_itv=it.itv;
		this->ptr=it.ptr;
	}

	template <class CMP>
	const typename conjunto<CMP>::entrada & conjunto<CMP>::const_iterator::operator*() const{
		return *(c_itv);
	}

	template <class CMP>
	typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator++(int){
		typename conjunto<CMP>::const_iterator tmp(*this);
		c_itv++;
		return tmp;
	}

	template <class CMP>
	typename conjunto<CMP>::const_iterator & conjunto<CMP>::const_iterator::operator++(){
		this->c_itv++;
		return *this;
	}

	template <class CMP>
 	typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator--(int){
		typename conjunto::const_iterator tmp(*this);
		c_itv--;
		return tmp;
	}

	template <class CMP>
  typename conjunto<CMP>::const_iterator & conjunto<CMP>::const_iterator::operator--(){
		this->c_itv--;
		return *this;
	}

	template <class CMP>
	bool conjunto<CMP>::const_iterator::operator==(const conjunto<CMP>::const_iterator & it){
		return (this->c_itv==it.c_itv);
	}

	template <class CMP>
	bool conjunto<CMP>::const_iterator::operator!=(const conjunto<CMP>::const_iterator & it){
		return (this->c_itv!=it.c_itv);
	}

// ================================= CLASS ARREST ITERATOR   ========================================/
	template <class CMP>
	typename conjunto<CMP>::arrest_iterator conjunto<CMP>::abegin(){
		typename conjunto<CMP>::arrest_iterator tmp;
		tmp.a_itv=vc.begin();
		tmp.ptr=this;
		bool found=false;
		for(int i=0; i<vc.size(); i++){
			if(vc[i].getArrest()==true)
				found=true;
			tmp.a_itv+=i;
		}
		return tmp;
	}
template <class CMP>
	 typename conjunto<CMP>::arrest_iterator conjunto<CMP>::aend(){
		conjunto::arrest_iterator tmp;
		tmp.a_itv=vc.end();
		tmp.ptr=this;
		bool found=false;
		for(int i=vc.size()-1; i>0; i--){
			if(vc[i].getArrest()==true)
				found=true;
			tmp.a_itv-=i;
		}
		return tmp;
	}
	template <class CMP>
		conjunto<CMP>::arrest_iterator::arrest_iterator(){

		}
	template <class CMP>
		conjunto<CMP>::arrest_iterator::arrest_iterator(const conjunto<CMP>::arrest_iterator & it){
			this->a_itv = it.a_itv;
			this->ptr = it.ptr;
		}
	template <class CMP>
		const typename conjunto<CMP>::entrada & conjunto<CMP>::arrest_iterator::operator*() const{
			return *a_itv;
		}

	template <class CMP>
		typename conjunto<CMP>::arrest_iterator conjunto<CMP>::arrest_iterator::operator++(int){
			typename conjunto<CMP>::arrest_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), a_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				tmp.a_itv+=i;
			}
			return tmp;
		}
	template <class CMP>
		typename conjunto<CMP>::arrest_iterator & conjunto<CMP>::arrest_iterator::operator++(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), a_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				a_itv+=i;
			}
			return *this;
		}
	template <class CMP>
		typename conjunto<CMP>::arrest_iterator conjunto<CMP>::arrest_iterator::operator--(int){
			typename conjunto<CMP>::arrest_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), a_itv);
			for(int i=inicio; !existe && i>0; i--){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				tmp.a_itv-=i;
			}
			return tmp;
		}
	template <class CMP>
		typename conjunto<CMP>::arrest_iterator & conjunto<CMP>::arrest_iterator::operator--(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), a_itv);
			for(int i=inicio; !existe && i>0; i--){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				a_itv-=i;
			}
			return *this;
		}
	template <class CMP>
		bool conjunto<CMP>::arrest_iterator::operator==(const conjunto<CMP>::arrest_iterator & it){
			return (this->a_itv == it.a_itv);
		}
	template <class CMP>
		bool conjunto<CMP>::arrest_iterator::operator!=(const conjunto<CMP>::arrest_iterator & it){
			return (this->a_itv != it.a_itv);
		}


	// ================================= CLASS CONST ARREST ITERATOR   ========================================/
	template <class CMP>
		typename conjunto<CMP>::const_arrest_iterator conjunto<CMP>::cabegin(){
			typename conjunto<CMP>::const_arrest_iterator tmp;
			tmp.ca_itv=vc.begin();
			tmp.ptr=this;
			bool found=false;
			for(int i=0; i<vc.size(); i++){
				if(vc[i].getArrest()==true)
					found=true;
				tmp.ca_itv+=i;
			}
			return tmp;
		}
	template <class CMP>
		typename conjunto<CMP>::const_arrest_iterator conjunto<CMP>::caend(){
			typename conjunto<CMP>::const_arrest_iterator tmp;
			tmp.ca_itv=vc.end();
			tmp.ptr=this;
			bool found=false;
			for(int i=vc.size()-1; i>0; i++){
				if(vc[i].getArrest()==true)
					found=true;
				tmp.ca_itv-=i;
			}
			return tmp;
		}
	template <class CMP>
		conjunto<CMP>::const_arrest_iterator::const_arrest_iterator(){

		}
	template <class CMP>
		conjunto<CMP>::const_arrest_iterator::const_arrest_iterator(const conjunto<CMP>::const_arrest_iterator & it){
			this->ca_itv = it.ca_itv;
			this->ptr=it.ptr;
		}

	template <class CMP>
		const typename conjunto<CMP>::entrada & conjunto<CMP>::const_arrest_iterator::operator*() const{
			return *(ca_itv);
		}

	template <class CMP>
		typename conjunto<CMP>::const_arrest_iterator conjunto<CMP>::const_arrest_iterator::operator++(int){
			typename conjunto<CMP>::const_arrest_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), ca_itv);
			for(int i=inicio; !existe && i<(*ptr).vc.size(); i--){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				tmp.ca_itv-=i;
			}
			return tmp;
		}
	template <class CMP>
		typename conjunto<CMP>::const_arrest_iterator & conjunto<CMP>::const_arrest_iterator::operator++(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), ca_itv);
			for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				ca_itv+=i;
			}
			return *this;
		}
	template <class CMP>
	 	typename conjunto<CMP>::const_arrest_iterator conjunto<CMP>::const_arrest_iterator::operator--(int){
			typename conjunto<CMP>::const_arrest_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), ca_itv);
			for(int i=inicio; !existe && i>0; i--){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				tmp.ca_itv-=i;
			}
			return tmp;
		}
	template <class CMP>
		typename conjunto<CMP>::const_arrest_iterator & conjunto<CMP>::const_arrest_iterator::operator--(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), ca_itv);
			for(int i=inicio; !existe && i>0; i--){
				if((*ptr).vc[i].getArrest()==true)
					existe=true;
				ca_itv-=i;
			}
			return *this;
		}
	template <class CMP>
		bool conjunto<CMP>::const_arrest_iterator::operator==(const conjunto<CMP>::const_arrest_iterator & it){
			return (ca_itv==it.ca_itv);
		}
	template <class CMP>
		bool conjunto<CMP>::const_arrest_iterator::operator!=(const conjunto<CMP>::const_arrest_iterator & it){
			return (ca_itv!=it.ca_itv);
		}


	// ================================= CLASS DESCRIPTION ITERATOR  ========================================/

		template <class CMP>
		typename conjunto<CMP>::description_iterator conjunto<CMP>::dbegin(const string & descr){
			typename conjunto<CMP>::description_iterator return_iterator;
			return_iterator.ptr=this;
			return_iterator.d_itv=vc.begin();
			bool existe=false;
			for(int i=0; !existe && i<vc.size(); i++){
				std::size_t found=vc[i].getDescription().find(descr);
				if(found!=std::string::npos){
					existe=true;
					return_iterator.d_itv+=i;
				}
			}
			return return_iterator;
		}

		template <class CMP>
		typename conjunto<CMP>::description_iterator conjunto<CMP>::dend( ){
			typename conjunto<CMP>::description_iterator return_iterator;
			return_iterator.d_itv=vc.end();
			bool existe=false;
			for(int i=vc.size()-1; i>0; i--){
				if(vc[i].getDescription() == return_iterator.descr)
					existe=true;
				return_iterator.d_itv-=i;
			}
			return return_iterator;
		}

		template <class CMP>
		conjunto<CMP>::description_iterator::description_iterator(){

		}

		template <class CMP>
		conjunto<CMP>::description_iterator::description_iterator(const conjunto<CMP>::description_iterator & it){
			this->d_itv=it.d_itv;
			this->ptr=it.ptr;
			this->descr=it.descr;
		}

		template <class CMP>
		const typename conjunto<CMP>::entrada & conjunto<CMP>::description_iterator::operator*() const{
			return *(d_itv);
		}

		template <class CMP>
		typename conjunto<CMP>::description_iterator conjunto<CMP>::description_iterator::operator++(int){
			typename conjunto<CMP>::description_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), d_itv);
			for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				d_itv+=i;
			}
			return tmp;
		}

		template <class CMP>
		typename conjunto<CMP>::description_iterator & conjunto<CMP>::description_iterator::operator++(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), d_itv);
			for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				d_itv+=i;
			}
			return *this;
		}

		template <class CMP>
		typename conjunto<CMP>::description_iterator conjunto<CMP>::description_iterator::operator--(int){
			typename conjunto<CMP>::description_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), d_itv);
			for(int i=inicio; !existe && i<(*ptr).vc.size(); i--){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				d_itv-=i;
			}
			return tmp;
		}

		template <class CMP>
		typename conjunto<CMP>::description_iterator & conjunto<CMP>::description_iterator::operator--(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), d_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				d_itv-=i;
			}
			return *this;
		}

		template <class CMP>
		bool conjunto<CMP>::description_iterator::operator==(const conjunto<CMP>::description_iterator & it){
			return (this->d_itv == it.d_itv);
		}

		template <class CMP>
		bool conjunto<CMP>::description_iterator::operator!=(const conjunto<CMP>::description_iterator & it){
			return (this->d_itv != it.d_itv);
		}


		// ================================= CLASS CONST DESCRIPTION ITERATOR   ========================================/

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator conjunto<CMP>::cdbegin(const string & descr){
			typename conjunto<CMP>::const_description_iterator return_iterator;
			return_iterator.ptr=this;
			return_iterator.cd_itv=vc.begin();
			bool existe=false;
			for(int i=0; i<vc.size() && !existe; i++){
				std::size_t found=vc[i].getDescription().find(descr);
				if(found!=std::string::npos){
					existe=true;
					return_iterator.cd_itv+=i;
				}
			}
			return return_iterator;
		}

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator conjunto<CMP>::cdend( ){
			typename conjunto<CMP>::const_description_iterator return_iterator;
			return_iterator.cd_itv=vc.end();
			bool existe=false;
			for(int i=vc.size()-1; i>=0; i--){
				if(vc[i].getDescription() == return_iterator.descr)
					existe=true;
				return_iterator.cd_itv-=i;
			}
			return return_iterator;
		}

		template <class CMP>
		conjunto<CMP>::const_description_iterator::const_description_iterator(){

		}

		template <class CMP>
		conjunto<CMP>::const_description_iterator::const_description_iterator(const conjunto<CMP>::const_description_iterator & it){
			this->cd_itv=it.cd_itv;
			this->ptr=it.ptr;
			this->descr=it.descr;
		}

		template <class CMP>
		const typename conjunto<CMP>::entrada & conjunto<CMP>::const_description_iterator::operator*() const{
			return *(cd_itv);
		}

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator conjunto<CMP>::const_description_iterator::operator++(int){
			typename conjunto<CMP>::const_description_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), cd_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				cd_itv+=i;
			}
			return tmp;
		}

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator & conjunto<CMP>::const_description_iterator::operator++(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), cd_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;
				cd_itv+=i;
			}
			return *this;
		}

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator conjunto<CMP>::const_description_iterator::operator--(int){
			typename conjunto<CMP>::const_description_iterator tmp(*this);
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), cd_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;

				cd_itv-=i;
			}
			return tmp;
		}

		template <class CMP>
		typename conjunto<CMP>::const_description_iterator & conjunto<CMP>::const_description_iterator::operator--(){
			bool existe=false;
			int inicio=distance((*ptr).vc.begin(), cd_itv);
			for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
				if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
					existe=true;

				cd_itv-=i;
			}
			return *this;
		}

		template <class CMP>
		bool conjunto<CMP>::const_description_iterator::operator==(const conjunto<CMP>::const_description_iterator & it){
			return (this->cd_itv == it.cd_itv);
		}

		template <class CMP>
		bool conjunto<CMP>::const_description_iterator::operator!=(const conjunto<CMP>::const_description_iterator & it){
			return (this->cd_itv != it.cd_itv);
		}
