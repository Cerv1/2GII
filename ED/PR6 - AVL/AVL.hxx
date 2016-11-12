
typedef int altura;

//                         // MÉTODOS PRIVADOS //
//____________________________________________________________________________

template <typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(typename bintree<pair<T,AVL<T,comparar>::altura> >::node n){
  typename AVL<T,comparar>::iterator it(n);
  return (*it).second;
}

template <typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(typename bintree<pair<T,AVL<T,comparar>::altura> >::const_node n){
  typename AVL<T,comparar>::iterator it(n);
  return (*it).second;
}

template <typename T, class comparar>
bool AVL<T,comparar>::Balanceo(typename bintree<pair<T,altura> >::node &n){
  /*if(h(n.right())-h(n.left())>1){
    if(h(n.right().left())>h(n.right().right()))
      RSD(n);
    else
      RDII(n);

    if(h(n.left()))
  }
  else if(h(n.left())-h(n.right())<-1){

  }*/
}

template <typename T, class comparar>
void AVL<T,comparar>::AlturaTotal(typename bintree<pair<T,altura> >::node n){
  while(!n.null())
    AlturaNode(n);
}

template <typename T, class comparar>
void AVL<T,comparar>::AlturaNode(typename bintree<pair<T,altura> >::node n){
      cout << "HOLA";
  if(n.right().null() && n.left().null())
    (*n).second=0;

  else{
    cout << "HAY";
    if(h(n.right())<h(n.left()))
      (*n).second=h(n.left())+1;
    else if(h(n.right()) >= h(n.left()))
      (*n).second=h(n.right())+1;

  }
}

template <typename T, class comparar>
void AVL<T,comparar>::RSD(typename bintree<pair<T,altura> >::node & n){

   typename bintree<pair<T,altura> >::node Padre=n.parent();
   typename bintree<pair<T,altura> >::node P = n;
   typename bintree<pair<T,altura> >::node Q = P.left();
   typename bintree<pair<T,altura> >::node B = P.right();

   if(!Padre.null()){
     if(Padre.right() == P)
        Padre.right() = Q;
     else
        Padre.left() = Q;
   }
   else
      *this=Q;

    P.left()=B;
    Q.right()=P;
    P.parent()=Q;
    if(!B.null())
      B.parent()=P;

    Q.parent()=Padre;
}


template <typename T, class comparar>
void AVL<T,comparar>::RSI(typename bintree<pair<T,altura> >::node & n){
  typename bintree<pair<T,altura> >::node Padre=n.parent();
  typename bintree<pair<T,altura> >::node P = n;
  typename bintree<pair<T,altura> >::node Q = P.left();
  typename bintree<pair<T,altura> >::node B = P.right();

  if(!Padre.null()){
    if(Padre.right() == P)
       Padre.right() = Q;
    else
       Padre.left() = Q;
  }
  else
     *this=Q;

   P.left()=B;
   Q.right()=P;
   P.parent()=Q;
   if(!B.null())
     B.parent()=P;

   Q.parent()=Padre;
}

template <typename T, class comparar>
void AVL<T,comparar>::RDDI(typename bintree<pair<T,altura> >::node & n){
  RSD(n);
  RSI(n);
}

template <typename T, class comparar>
void AVL<T,comparar>::RDID(typename bintree<pair<T,altura> >::node & n){
  RSI(n);
  RSD(n);
}
//____________________________________________________________________________



                          // CONSTRUCTORES //
//____________________________________________________________________________

template <typename T, class comparar>
AVL<T,comparar>::AVL(){
  tama=0;
}

template <typename T, class comparar>
AVL<T,comparar>::AVL(AVL<T,comparar> &avl){
  this->el_avl=avl.el_avl;
  this->tama=avl.tama;
}
//____________________________________________________________________________



//                    // OPERADOR DE ASIGNACIÓN //
//____________________________________________________________________________

template <typename T, class comparar>
AVL<T,comparar> & AVL<T,comparar>::operator=(AVL<T,comparar> &avl){
  this->el_avl=avl.el_avl;
  this->tama=avl.tama;
  return *this;
}
//____________________________________________________________________________



//                         // ITERADORES //
//____________________________________________________________________________

template <typename T, class comparar>
AVL<T,comparar>::iterator::iterator(){
  //AVL<T,comparar>::iterator::elnodo = typename bintree<T>::node();
}

template <typename T, class comparar>
AVL<T,comparar>::iterator::iterator(const AVL<T,comparar>::iterator &it){
  this->in_it=it.in_it;
}

template <typename T, class comparar>
AVL<T,comparar>::iterator::iterator(typename bintree<pair<T,altura>>::node n){
  typename bintree<pair<T,altura>>::inorder_iterator aux(n);
  (*this).in_it=aux;
}
template <typename T, class comparar>
bool AVL<T,comparar>::iterator::operator!=(const AVL<T,comparar>::iterator &it){
  return (this->in_it!=it.in_it);
}

template <typename T, class comparar>
bool AVL<T,comparar>::iterator::operator==(const AVL<T,comparar>::iterator &it){
  return (this->in_it==it.in_it);
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator=(const AVL<T,comparar>::iterator &it){
  this->in_it = it.in_it;
  return *this;
}

template <typename T, class comparar>
pair<T,altura> AVL<T,comparar>::iterator::operator*(){
  return (*in_it);
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator++(){
  ++in_it;
  return *this;

}
//___________________________________________________________________________________

template <typename T, class comparar>
AVL<T,comparar>::const_iterator::const_iterator(){

}

template <typename T, class comparar>
AVL<T,comparar>::const_iterator::const_iterator(const AVL<T,comparar>::const_iterator &it){
  this->cin_it=it.cin_it;
}

template <typename T, class comparar>
AVL<T,comparar>::const_iterator::const_iterator(typename bintree<pair<T,altura>>::node n){
  typename bintree<pair<T,altura>>::inorder_iterator aux(n);
  (*this).cin_it=aux;
}

template <typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator!=(const AVL<T,comparar>::const_iterator &it){
  return (this->cin_it!=it.cin_it);
}

template <typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator==(const AVL<T,comparar>::const_iterator &it){
  return (this->cin_it==it.cin_it);
}

template <typename T, class comparar>
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator=(const AVL<T,comparar>::const_iterator &it){
  this->cin_it=it.cin_it;
  return *this;
}

template <typename T, class comparar>
pair<T,altura> & AVL<T,comparar>::const_iterator::operator*(){
  return (*cin_it);
}

template <typename T, class comparar>
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator++(){
  ++cin_it;
  return *this;
}

//__________________________________________________________________________________________________


template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::begin(){
  AVL<T,comparar>::iterator out;
  out.in_it=el_avl.begin_inorder();
  return out;
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::end(){
  AVL<T,comparar>::iterator out;
  out.in_it=el_avl.end_inorder();
  return out;
}

template <typename T, class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cbegin(){
  typename AVL<T,comparar>::const_iterator it;
  it.cin_it=el_avl.begin_inorder();
  return it;
}

template <typename T, class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cend(){
  typename AVL<T,comparar>::const_iterator it;
  it.cin_it=el_avl.end_inorder();
  return it;
}

//____________________________________________________________________________


//                         // CAPACIDAD //
//____________________________________________________________________________

template <typename T, class comparar>
bool AVL<T,comparar>::empty(){
  return el_avl.empty();
}

template <typename T, class comparar>
typename bintree<T>::size_type AVL<T,comparar>::size(){
  return el_avl.size();
}
//____________________________________________________________________________


//                         // MODIFICADORES //
//____________________________________________________________________________
template <typename T, class comparar>
pair<typename AVL<T,comparar>::iterator, bool> AVL<T,comparar>::insert(const T &dato){
  typename bintree<pair<T,altura>>::node nodo,nodo_padre;
  pair<T,AVL<T,comparar>::altura> in;
  int altura=0;
  in.first=dato;
  in.second=0;
  pair<AVL<T,comparar>::iterator, bool> out;

  bool found=finder(dato, nodo, nodo_padre);
  if(!found){
    if(el_avl.empty()){  // Si está vacío
      el_avl = bintree<pair<T,AVL<T,comparar>::altura>>(in);
      out.second=true;
      out.first=this->begin();
      return out;
    }
    else{
      altura=1;
      nodo=el_avl.root();
      if(dato < (*el_avl.root()).first){
        while(!nodo.left().null()){
          nodo=nodo.left();
          altura++;
        }
        in.second=altura;
        el_avl.insert_left(nodo, in);
        //AlturaTotal(nodo);
        out.second=true;
        out.first=find(dato);

      }
      else{
        while(!nodo.right().null()){
          nodo=nodo.right();
          altura++;
        }
        in.second=altura;
        el_avl.insert_right(nodo, in);
        //AlturaTotal(nodo);
        out.second=true;
        out.first=find(dato);
      }
    }
  }
  else{
    (*nodo).second=dato;
    out.second=false;
    out.first=end();
  }

  return out;
}


template <typename T, class comparar>
void AVL<T,comparar>::erase(typename bintree<T>::inorder_iterator &pos){
  typename bintree<pair<T,altura>>::node nodo,nodo_padre;
  bintree<pair<T,altura>> Taux;
  bool found=finder((*pos).first,nodo,nodo_padre);
  if(found){
    typename bintree<pair<T,altura>>::iterator aux_it=find((*pos).first);

    //CASO NODO HOJA
    if((*aux_it).left().null() && (*aux_it).right().null()){
      if((*aux_it).parent().null())
        el_avl.clear();
      else
        if(nodo_padre.left()==nodo)
          el_avl.prune_left(nodo_padre,Taux);
        else
          el_avl.prune_right(nodo_padre,Taux);
          Taux.clear();

    }
    //CASO NODO CON 1 HIJO
    else if(nodo.left().null() || nodo.right().null()){
      if(!nodo.left().null())             //Hijo a la izquierda
        el_avl.prune_left(nodo,Taux);
      else
        el_avl.prune_right(nodo,Taux);    //Hijo a la derecha

      if(nodo_padre.null())               //Nodo es raiz
        el_avl=Taux;
      else if(nodo_padre.left()==nodo)
        el_avl.insert_left(nodo_padre,Taux);
      else
        el_avl.insert_right(nodo_padre,Taux);
    }
    //CASO NODO CON 2 HIJOS
    else{
      typename bintree<pair<T,altura>>::node pred;
      pred=nodo.left();
      while(!pred.right().null())
        pred=pred.right();
      pair<T,altura> valor_pred(*pred);
      typename bintree<pair<T,altura>>::node nodo_a_borrar=nodo;
      erase( (*pred).first);
      *nodo_a_borrar=valor_pred;
    }
  }
}

template <typename T, class comparar>
void AVL<T,comparar>::swap(AVL<T,comparar> &avl){
  el_avl=avl.el_avl;
  tama=avl.tama;
}

template <typename T, class comparar>
void AVL<T,comparar>::clear(){
  bintree<pair<T,altura> > vacio;
  el_avl=vacio;
}
//____________________________________________________________________________


//                         // OPERACIONES //
//____________________________________________________________________________

template <typename T, class comparar>
bool AVL<T,comparar>::finder(const T &dato, typename bintree<pair<T,AVL<T,comparar>::altura> >::node &n, typename bintree<pair<T,AVL<T,comparar>::altura> >::node &n_padre){
  bool found=false;
  if(!el_avl.empty()){
    n=el_avl.root();
    n_padre=n.parent();


    while(!n.null()  && !found) {
      if((*n).first==dato) // La clave ya aparece
        found=true;
      else{
        n_padre=n.parent();
        if(dato <(*n).first)
           n=n.left(); // Debe estar a la izquierda de n
        else // Debe estar a la derecha de n
           n=n.right();
      }
    }
    return found;
  }
  else
    return false;
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::find(const T &dato){
  bool found;
  typename bintree<pair<T,altura>>::node nodo,nodo_padre;
  found = finder(dato, nodo, nodo_padre);
  if(found==true){
    pair<T,altura> in;
    in.first=dato;
    in.second=0;
    typename AVL<T,comparar>::iterator it(nodo);
    return it;
  }
  else
    return end();
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::lower_bound(const T &dato){
  AVL<T,comparar>::iterator low_bound;
  typename bintree<pair<T,altura>>::node nodo,nodo_padre;
  bool found = finder(dato, nodo, nodo_padre);
  low_bound=begin();
  if(found){     // Si existe
    low_bound=find(dato);
    return low_bound;
  }
  else{         // Si no existe devuelve el siguiente
    while((*low_bound).first<=dato && low_bound!=end())
      ++low_bound;
    return low_bound;
  }
  return end();
}

template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::upper_bound(const T &dato){
  AVL<T,comparar>::iterator upper_bound;
  typename bintree<pair<T,altura>>::node nodo,nodo_padre;
  bool found = finder(dato, nodo, nodo_padre);
  upper_bound=begin();
  if(found){     // Si existe
    upper_bound=find(dato);
    ++upper_bound;
    return upper_bound;
  }
  else{         // Si no existe devuelve el siguiente
    while((*upper_bound).first<dato && upper_bound!=end())
      ++upper_bound;
    return upper_bound;
  }
  return end();
}

//____________________________________________________________________________
