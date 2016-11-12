/*! Implementacion  de la clase conjunto

*/

/*! Implementacion  de la clase conjunto

*/

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
			this->vc=d.vc;
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
	conjunto::iterator conjunto::find( const long int & id){
		conjunto::iterator tmp=begin();
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
	conjunto::const_iterator conjunto::find(const long int & id) const{
		conjunto::const_iterator tmp=cbegin();
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
	conjunto conjunto::findIUCR(const string & iucr) const{
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
	conjunto conjunto::findDESCR(const string & descr) const{
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
	bool conjunto::insert(const conjunto::entrada & e){
		if(empty())
			vc.insert(vc.begin(), e);
		else{
			long int pos=ExisteElemento(e.getID());
			bool insert=false;
			if(pos != -1){
				cout << pos << "   ";
				vc.insert(vc.begin()+pos,e);
				cout << e.getID() << endl;
				insert=true;
			}
			return insert;
		}
	}

/** @brief Borra el delito dado un identificacador.
	Busca la entrada con id en el conjunto  y si la encuentra la borra
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
	@param[in] entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
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
			return -1;
		else
			return centro;
	}


// ================================= CLASS ITERATOR   =================================================/


	conjunto::iterator conjunto::begin(){
		conjunto::iterator sal;
		sal.itv=vc.begin();
		sal.ptr=this;
		return sal;
	}

	conjunto::iterator conjunto::end(){
		conjunto::iterator sal;
		sal.itv = vc.end();
		sal.ptr=this;
		return sal;
	}

	conjunto::iterator::iterator(){

	}

	conjunto::iterator::iterator(const conjunto::iterator & it){
		this->itv=it.itv;
		this->ptr=it.ptr;
	}

 	const conjunto::entrada & conjunto::iterator::operator*() const{
		return *itv;
	}

	conjunto::iterator conjunto::iterator::operator++(int){
		conjunto::iterator tmp(*this);
		itv++;
		return tmp;
	}

	conjunto::iterator & conjunto::iterator::operator++(){
		this->itv++;
		return *this;
	}

	conjunto::iterator conjunto::iterator::operator--(int){
		conjunto::iterator tmp(*this);
		itv--;
		return tmp;
	}

	conjunto::iterator & conjunto::iterator::operator--(){
		this->itv--;
		return *this;
	}

	bool conjunto::iterator::operator==(const conjunto::iterator & it){
		return (itv==it.itv);
	}

	bool conjunto::iterator::operator!=(const conjunto::iterator & it){
		return (itv!=it.itv);
	}


// ================================= CLASS CONSTANT ITERATOR    ========================================/

	conjunto::const_iterator conjunto::cbegin() const{
		conjunto::const_iterator sal;
		sal.c_itv=vc.begin();
		sal.ptr=this;
		return sal;
	}

	conjunto::const_iterator conjunto::cend() const{
		conjunto::const_iterator sal;
		sal.c_itv = vc.end();
		sal.ptr=this;
		return sal;
	}

	conjunto::const_iterator::const_iterator(){

	}

	conjunto::const_iterator::const_iterator(const conjunto::const_iterator & it){
		this->c_itv=it.c_itv;
		this->ptr=it.ptr;
	}

	conjunto::const_iterator::const_iterator(const conjunto::iterator & it){
		this->c_itv=it.itv;
		this->ptr=it.ptr;
	}

	const conjunto::entrada & conjunto::const_iterator::operator*() const{
		return *(c_itv);
	}

	conjunto::const_iterator conjunto::const_iterator::operator++(int){
		conjunto::const_iterator tmp(*this);
		c_itv++;
		return tmp;
	}

	conjunto::const_iterator & conjunto::const_iterator::operator++(){
		this->c_itv++;
		return *this;
	}

 	conjunto::const_iterator conjunto::const_iterator::operator--(int){
		conjunto::const_iterator tmp(*this);
		c_itv--;
		return tmp;
	}

    conjunto::const_iterator & conjunto::const_iterator::operator--(){
		this->c_itv--;
		return *this;
	}

	bool conjunto::const_iterator::operator==(const conjunto::const_iterator & it){
		return (this->c_itv==it.c_itv);
	}

	bool conjunto::const_iterator::operator!=(const conjunto::const_iterator & it){
		return (this->c_itv!=it.c_itv);
	}


// ================================= CLASS ARREST ITERATOR   ========================================/

	conjunto::arrest_iterator conjunto::abegin(){
		conjunto::arrest_iterator tmp;
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

	conjunto::arrest_iterator conjunto::aend(){
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

	conjunto::arrest_iterator::arrest_iterator(){

	}

	conjunto::arrest_iterator::arrest_iterator(const conjunto::arrest_iterator & it){
		this->a_itv = it.a_itv;
		this->ptr = it.ptr;
	}

	const conjunto::entrada & conjunto::arrest_iterator::operator*() const{
		return *a_itv;
	}

	conjunto::arrest_iterator conjunto::arrest_iterator::operator++(int){
		conjunto::arrest_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), a_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			tmp.a_itv+=i;
		}
		return tmp;
	}

	conjunto::arrest_iterator & conjunto::arrest_iterator::operator++(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), a_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			a_itv+=i;
		}
		return *this;
	}

	conjunto::arrest_iterator conjunto::arrest_iterator::operator--(int){
		conjunto::arrest_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), a_itv);
		for(int i=inicio; !existe && i>0; i--){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			tmp.a_itv-=i;
		}
		return tmp;
	}

	conjunto::arrest_iterator & conjunto::arrest_iterator::operator--(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), a_itv);
		for(int i=inicio; !existe && i>0; i--){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			a_itv-=i;
		}
		return *this;
	}

	bool conjunto::arrest_iterator::operator==(const conjunto::arrest_iterator & it){
		return (this->a_itv == it.a_itv);
	}

	bool conjunto::arrest_iterator::operator!=(const conjunto::arrest_iterator & it){
		return (this->a_itv != it.a_itv);
	}


// ================================= CLASS CONST ARREST ITERATOR   ========================================/

	conjunto::const_arrest_iterator conjunto::cabegin(){
		conjunto::const_arrest_iterator tmp;
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

	conjunto::const_arrest_iterator conjunto::caend(){
		conjunto::const_arrest_iterator tmp;
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

	conjunto::const_arrest_iterator::const_arrest_iterator(){

	}

	conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::const_arrest_iterator & it){
		this->ca_itv = it.ca_itv;
		this->ptr=it.ptr;
	}

	const conjunto::entrada & conjunto::const_arrest_iterator::operator*() const{
		return *(ca_itv);
	}

	conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator++(int){
		conjunto::const_arrest_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), ca_itv);
		for(int i=inicio; !existe && i<(*ptr).vc.size(); i--){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			tmp.ca_itv-=i;
		}
		return tmp;
	}

	conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator++(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), ca_itv);
		for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			ca_itv+=i;
		}
		return *this;
	}

 	conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator--(int){
		conjunto::const_arrest_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), ca_itv);
		for(int i=inicio; !existe && i>0; i--){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			tmp.ca_itv-=i;
		}
		return tmp;
	}

	conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator--(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), ca_itv);
		for(int i=inicio; !existe && i>0; i--){
			if((*ptr).vc[i].getArrest()==true)
				existe=true;
			ca_itv-=i;
		}
		return *this;
	}

	bool conjunto::const_arrest_iterator::operator==(const conjunto::const_arrest_iterator & it){
		return (ca_itv==it.ca_itv);
	}

	bool conjunto::const_arrest_iterator::operator!=(const conjunto::const_arrest_iterator & it){
		return (ca_itv!=it.ca_itv);
	}

// ================================= CLASS DESCRIPTION ITERATOR  ========================================/

	conjunto::description_iterator conjunto::dbegin(const string & descr){

		conjunto::description_iterator return_iterator;
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

	conjunto::description_iterator conjunto::dend( ){
		conjunto::description_iterator return_iterator;
		return_iterator.d_itv=vc.end();
		bool existe=false;
		for(int i=vc.size()-1; i>0; i--){
			if(vc[i].getDescription() == return_iterator.descr)
				existe=true;
			return_iterator.d_itv-=i;
		}
		return return_iterator;
	}

	conjunto::description_iterator::description_iterator(){

	}

	conjunto::description_iterator::description_iterator(const conjunto::description_iterator & it){
		this->d_itv=it.d_itv;
		this->ptr=it.ptr;
		this->descr=it.descr;
	}

	const conjunto::entrada & conjunto::description_iterator::operator*() const{
		return *(d_itv);
	}

	conjunto::description_iterator conjunto::description_iterator::operator++(int){
		conjunto::description_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), d_itv);
		for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			d_itv+=i;
		}
		return tmp;
	}

	conjunto::description_iterator & conjunto::description_iterator::operator++(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), d_itv);
		for(int i=inicio; !existe && i<(*ptr).vc.size(); i++){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			d_itv+=i;
		}
		return *this;
	}

	conjunto::description_iterator conjunto::description_iterator::operator--(int){

		conjunto::description_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), d_itv);
		for(int i=inicio; !existe && i<(*ptr).vc.size(); i--){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			d_itv-=i;
		}
		return tmp;
	}

	conjunto::description_iterator & conjunto::description_iterator::operator--(){

		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), d_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			d_itv-=i;
		}
		return *this;
	}

	bool conjunto::description_iterator::operator==(const conjunto::description_iterator & it){
		return (this->d_itv == it.d_itv);
	}

	bool conjunto::description_iterator::operator!=(const conjunto::description_iterator & it){
		return (this->d_itv != it.d_itv);
	}


	// ================================= CLASS CONST DESCRIPTION ITERATOR   ========================================/

	conjunto::const_description_iterator conjunto::cdbegin(const string & descr){

		conjunto::const_description_iterator return_iterator;
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

	conjunto::const_description_iterator conjunto::cdend( ){

		conjunto::const_description_iterator return_iterator;
		return_iterator.cd_itv=vc.end();
		bool existe=false;
		for(int i=vc.size()-1; i>=0; i--){
			if(vc[i].getDescription() == return_iterator.descr)
				existe=true;
			return_iterator.cd_itv-=i;
		}
		return return_iterator;
	}

	conjunto::const_description_iterator::const_description_iterator(){

	}

	conjunto::const_description_iterator::const_description_iterator(const conjunto::const_description_iterator & it){
		this->cd_itv=it.cd_itv;
		this->ptr=it.ptr;
		this->descr=it.descr;
	}

	const conjunto::entrada & conjunto::const_description_iterator::operator*() const{
		return *(cd_itv);
	}

	conjunto::const_description_iterator conjunto::const_description_iterator::operator++(int){
		conjunto::const_description_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), cd_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			cd_itv+=i;
		}
		return tmp;
	}

	conjunto::const_description_iterator & conjunto::const_description_iterator::operator++(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), cd_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i++){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;
			cd_itv+=i;
		}
		return *this;
	}

	conjunto::const_description_iterator conjunto::const_description_iterator::operator--(int){
		conjunto::const_description_iterator tmp(*this);
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), cd_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;

			cd_itv-=i;
		}
		return tmp;
	}

	conjunto::const_description_iterator & conjunto::const_description_iterator::operator--(){
		bool existe=false;
		int inicio=distance((*ptr).vc.begin(), cd_itv);
		for(int i=inicio; i<(*ptr).vc.size() && !existe; i--){
			if((*ptr).vc[i].getDescription() == (*ptr).vc[inicio].getDescription())
				existe=true;

			cd_itv-=i;
		}
		return *this;
	}

	bool conjunto::const_description_iterator::operator==(const conjunto::const_description_iterator & it){
		return (this->cd_itv == it.cd_itv);
	}

	bool conjunto::const_description_iterator::operator!=(const conjunto::const_description_iterator & it){
		return (this->cd_itv != it.cd_itv);
	}
