#ifndef __AVL_H
#define __AVL_H

#include <iostream>
#include <set>
#include <iterator>
#include <map>
#include <utility>
#include "bintree.h"

using namespace std;

template <typename T, class comparar=std::less<T> >
class AVL{
  typedef int altura;
private:
  // Metodos privados
  altura h(typename bintree<pair<T,altura> >::node n);
  altura h(typename bintree<pair<T,altura> >::const_node n);

  // Equilibrio
  bool EquilibrarAVL();
  bool Balanceo(typename bintree<pair<T,altura> >::node &n);
  void AlturaNode(typename bintree<pair<T,altura> >::node n);
  void AlturaTotal(typename bintree<pair<T,altura> >::node n);

  // Rotaciones
  void RSD(typename bintree<pair<T,altura> >::node & n);
  void RSI(typename bintree<pair<T,altura> >::node & n);
  void RDDI(typename bintree<pair<T,altura> >::node & n);
  void RDID(typename bintree<pair<T,altura> >::node & n);

  // Representacion
  bintree<pair<T,altura> > el_avl;
  unsigned int tama;
  comparar cmp;

public:

  class iterator{
  private:
    typename bintree<pair<T,altura>>::inorder_iterator in_it;
    iterator(const typename bintree<pair<T,altura>>::node n);
    friend class AVL;
  public:
    iterator();
    iterator(const iterator &it);
    bool operator!=(const iterator &it);
    bool operator==(const iterator &it);
    iterator & operator=(const iterator &it);
    pair<T,altura> operator*();
    iterator & operator++();
  };

  class const_iterator{
  private:
    typename bintree<pair<T,altura>>::inorder_iterator cin_it;
    const_iterator(const typename bintree<pair<T,altura>>::node n);
    friend class AVL;
  public:
    const_iterator();
    const_iterator(const const_iterator &it);
    bool operator!=(const const_iterator &it);
    bool operator==(const const_iterator &it);
    const_iterator & operator=(const const_iterator &it);
    pair<T,altura> & operator*();
    const_iterator & operator++();
  };

  // Constructores
  AVL();                            //DONE
  AVL(AVL &avl);                    //DONE

  // Operador de asiganción
  AVL & operator=(AVL &avl);        //DONE

  // Capacidad
  bool empty();                           //DONE
  typename bintree<T>::size_type size();  //DONE

  // Modificadores
  //DONE
  bool finder(const T &dato, typename bintree<pair<T,altura> >::node &n, typename bintree<pair<T,altura> >::node &n_padre);
  pair<iterator,bool> insert(const T &dato);    //DONE
  void erase(typename bintree<T>::inorder_iterator &pos);
  void swap(AVL &avl);    //DONE
  void clear();           //DONE


  // Operaciones
  iterator find(const T &dato);           //DONE
  iterator lower_bound(const T &dato);    //DONE
  iterator upper_bound(const T &dato);    //DONE

  // Iteradores
  iterator begin();                       //DONE
  iterator end();                         //DONE
  const_iterator cbegin();                //DONE
  const_iterator cend();                  //DONE


};

#include "AVL.hxx"
#endif
