/** ESTA PRÁCTICA HA SIDO RESUELTA EN SU TOTALIDAD POR SERGIO CERVILLA ORTEGA, DNI: 14275233F- */
#include "fecha.h"
#include "crimen.h"
#include "css.h"

void CSS::load(string nombreDB){
  ifstream fe;
  string cadena;
  cout << "\n\n         Abrimos " << nombreDB << ": \n" << endl;
  fe.open(nombreDB.c_str(), ifstream::in);
  if(fe.fail())
    cerr << "Error al abrir el fichero " << nombreDB << "..." << endl;
  else{
    getline(fe, cadena, '\n'); // Leemos la cabecera del fichero.
    while(!fe.eof()){
      getline(fe, cadena, '\n');
      if(!fe.eof()){
        //Almacenamos el crimen en todos los contenedores a la vez utilizando el insert de CSS.
        crimen aux_crimen;
        aux_crimen = cadena;
        insert(aux_crimen);
      }
    }
  }
}

void CSS::insert(const crimen & x){

  //Almacenamos por ID.
  pair<ID,crimen> crimenID;
  crimenID.first=x.getID();
  crimenID.second=x;
  baseDatos.insert(crimenID);

  //Almacenamos por fecha.
  map<ID,crimen>::iterator it;
  it=baseDatos.find(x.getID());
  pair<fecha, map<ID,crimen>::iterator> crimenDATE;
  crimenDATE.first=x.getDate();
  crimenDATE.second=it;
  DateAccess.insert(crimenDATE);

  //Almacenamos por posición geográfica.
  pair<Longitud,multimap<Latitud, ID>> crimenGEO;
  multimap<Latitud, ID> multiGEO;
  pair<Latitud, ID> pairGEO;
  pairGEO.first=x.getLatitude();
  pairGEO.second=x.getID();
  multiGEO.insert(pairGEO);
  crimenGEO.first=x.getLongitude();
  crimenGEO.second=multiGEO;
  posicionGeo.insert(crimenGEO);
}

bool CSS::erase(unsigned int ID){
  map<unsigned int,crimen>::iterator it;
  it=baseDatos.find(ID);

  //Almacenamos las claves a borrar de los correspondientes contenedores en variables auxiliares.
  fecha date=it->second.getDate();
  Longitud longi=it->second.getLongitude();

  if(baseDatos.erase(ID)){
    DateAccess.erase(date);
    posicionGeo.erase(longi);
    return true;
  }
  else
    return false;
}

void CSS::setArrest(const unsigned int ID, bool value){
  map<unsigned int,crimen>::iterator it;
  it=baseDatos.find(ID);
  if(it!=baseDatos.end())
    it->second.setArrest(value);
}

map<ID,float> CSS::unionPeso( const set<ID> & t1, const set<ID> &t2){
  set<ID>::iterator it1=t1.begin();
  set<ID>::iterator it2=t2.begin();
  map<ID,float> mapreturn;
  pair<ID,float> paux;
  //Ingresamos todos los ID's del primer conjunto.
  while(it1!=t1.end()){
    paux.first=*it1;
    paux.second=1.0;
    mapreturn.insert(paux);
    it1++;
  }
  while(it2 != t2.end()){
    //Comprobamos si existe el elemento actual del conjunto 2 en el primero y si es así
    //lo borramos y lo ingresamos con el valor del float aumentado en una unidad.
    if(mapreturn.find(*it2)!=mapreturn.end()){
      mapreturn.erase(*it2);
      paux.first=*it2;
      paux.second=2.0;
      mapreturn.insert(paux);
    }
    it2++;
  }

  return mapreturn;
}

vector<pair<ID,float>> CSS::Query(list<string> & q, int k){
  //La lista solo tiene un elemento.
  vector<pair<ID,float>> vreturn;
  pair<ID,float> paux;
  if(q.size() == 1){
      unordered_map<Termino, set<ID>>::iterator it=index.find(q.front());
      set<ID>::iterator itset=it->second.begin();
      while(itset != it->second.end()){
        paux.first=*itset;
        paux.second=1.0;
        vreturn.push_back(paux);
        itset++;
      }
      return vreturn;
  }
  //La lista tiene dos elementos.
  else if(q.size() == 2){
    unordered_map<Termino, set<ID>>::iterator it1=index.find(q.front());
    q.pop_front();
    unordered_map<Termino, set<ID>>::iterator it2=index.find(q.front());
    map<ID,float> mapaux=unionPeso(it1->second,it2->second);
    map<ID,float>::iterator itmap=mapaux.begin();
    while(itmap!=mapaux.end()){
      vreturn.push_back(*itmap);
      itmap++;
    }
    return vreturn;
  }
  //La lista tiene mas de dos elementos.
  else{
    list<string>::iterator itlist=q.begin();
    //Repetimos el proceso para 2 pero hasta que se acabe la lista. Haciendo uniones sucesivas.
    while(itlist!=q.end()){
      unordered_map<Termino, set<ID>>::iterator it1=index.find(q.front());
      q.pop_front();
      unordered_map<Termino, set<ID>>::iterator it2=index.find(q.front());
      map<ID,float> mapaux=unionPeso(it1->second,it2->second);
      map<ID,float>::iterator itmap=mapaux.begin();
      while(itmap!=mapaux.end()){
        vreturn.push_back(*itmap);
        itmap++;
      }
      itlist++;
    }
    return vreturn;
  }

}


list<ID> CSS::inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2 ){
  list<ID> listAUX;
  map<Longitud, multimap<Latitud, ID>>::iterator it;
  it=posicionGeo.begin();

  // Añadimos a la lista los crimenes cuya longitud cumple que x1<=x2 && y1<=y2.
  while(it!=posicionGeo.end()){
    multimap<Latitud, ID> multiAUX;
    multiAUX=it->second;
    multimap<Latitud, ID>::iterator it_aux;
    it_aux=multiAUX.begin();
    if(it->first>=y1 && it->first<=y2 && it_aux->first>=x1 && it_aux->first<=x2){
      listAUX.push_back(it_aux->second);
      list<ID>::iterator it_list=listAUX.begin();
      it_list++;
      multiAUX.clear();
    }
  it++;
  }
return listAUX;
}


// -------------------------------- ITERATOR -------------------------------------
pair<const ID, crimen > & CSS::iterator::operator*(){
  return *it;
}
CSS::iterator CSS::iterator::operator++(int){
  CSS::iterator tmp(*this);
  this->it++;
  return tmp;
}
CSS::iterator & CSS::iterator::operator++(){
  this->it++;
  return *this;
}

bool CSS::iterator::operator==(const CSS::iterator & it){
  return (this->it==it.it);
}
bool CSS::iterator::operator!=(const CSS::iterator & it){
  return (this->it!=it.it);
}

// -------------------------------- IUCR_ITERATOR --------------------------------
pair<const ID, crimen > & CSS::IUCR_iterator::operator*(){
  return *ptr->baseDatos.find(*it_s);
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int){
  CSS::IUCR_iterator tmp(*this);
  if(it_s++==it_m->second.end()){
    it_m++;
    it_s=it_m->second.begin();
  }
  return tmp;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++(){
  if(it_s++==it_m->second.end()){
    it_m++;
    it_s=it_m->second.begin();
  }
  return *this;
}

bool CSS::IUCR_iterator::operator==(const CSS::IUCR_iterator &it){
  return (it_m==it.it_m && it_s==it.it_s);
}

bool CSS::IUCR_iterator::operator!=(const CSS::IUCR_iterator &it){
  return (it_m!=it.it_m || it_s!=it.it_s);
}

// -------------------------------- Date_ITERATOR --------------------------------
pair<const ID, crimen > & CSS::Date_iterator::operator*(){
  return *it_mm->second;
}

CSS::Date_iterator CSS::Date_iterator::operator++(int){
  CSS::Date_iterator tmp(*this);
  this->it_mm++;
  return tmp;
}

CSS::Date_iterator & CSS::Date_iterator::operator++(){
  this->it_mm++;
  return *this;
}

bool CSS::Date_iterator::operator==(const CSS::Date_iterator & it){
  return (this->it_mm==it.it_mm);

}
bool CSS::Date_iterator::operator!=(const CSS::Date_iterator & it){
  return (this->it_mm!=it.it_mm);
}
// -------------------------------------------------------------------------------


CSS::iterator CSS::find_ID(const unsigned int ID){
  CSS:iterator it_aux;
  it_aux.it=baseDatos.find(ID);
  if(it_aux.it!=baseDatos.end())
    return it_aux;
  else{
    it_aux.it=baseDatos.begin();
    return it_aux;
  }
}

CSS::iterator CSS::begin(){
  CSS::iterator it_aux;
  it_aux.it=baseDatos.begin();
  return it_aux;
}

CSS::iterator CSS::end(){
  CSS::iterator it_aux;
  it_aux.it=baseDatos.end();
  return it_aux;
}

CSS::Date_iterator CSS::dbegin(){
  CSS::Date_iterator it_aux;
  it_aux.it_mm=DateAccess.begin();
  return it_aux;
}
CSS::Date_iterator CSS::dend(){
  CSS::Date_iterator it_aux;
  it_aux.it_mm=DateAccess.end();
  return it_aux;
}

CSS::IUCR_iterator CSS::ibegin(){
  CSS::IUCR_iterator it_aux;
  it_aux.ptr=this;
  it_aux.it_m=IUCRAccess.begin();
  it_aux.it_s=it_aux.it_m->second.begin();

  return it_aux;
}

CSS::IUCR_iterator CSS::iend(){
  CSS::IUCR_iterator it_aux;
  it_aux.ptr=this;
  it_aux.it_m=IUCRAccess.end();
  it_aux.it_m--; // IUCRAccess.end() devuelve la posicion siguiente al anterior.
  it_aux.it_s=it_aux.it_m->second.end();
  it_aux.it_s--;

  return it_aux;
}

CSS::Date_iterator CSS::lower_bound(fecha f){
  CSS::Date_iterator it;
  it.it_mm=DateAccess.lower_bound(f);
  return it;
}

CSS::Date_iterator CSS::upper_bound(fecha f){
  CSS::Date_iterator it;
  it.it_mm=DateAccess.upper_bound(f);
  return it;
}

CSS::IUCR_iterator CSS::lower_bound(IUCR iucr){
  CSS::IUCR_iterator it;
  it.ptr=this;
  it.it_m=IUCRAccess.lower_bound(iucr);
  it.it_s=it.it_m->second.begin();
  return it;
}

CSS::IUCR_iterator CSS::upper_bound(IUCR iucr){
  CSS::IUCR_iterator it;
  it.ptr=this;
  it.it_m=IUCRAccess.upper_bound(iucr);
  it.it_s=it.it_m->second.begin();
  return it;
}
