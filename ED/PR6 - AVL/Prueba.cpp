#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "AVL.h"
using namespace std;

int main(){

  AVL<int,less<int>> arbol;
  AVL<char> arbolc;
  AVL<int> arboli;
  AVL<int> arbolll(arbol);
  bintree<pair<int,int>>::node n, n_padre;
  /*
  cout << "Vacío -> " << arbol.empty() << endl;
  cout << "Finder-> " << arbol.finder(dato, n, n_padre)<<endl;
  arbol.insert(3);
  cout << "Vacío -> " << arbol.empty() << endl;
  cout << "Finder-> " << arbol.finder(dato, n, n_padre)<<endl;
  cout << "Size-> " << arbol.size() << endl;
  */
  cout << "Insertamos la secuencia 3-2-4-8-6-1 "<<endl;
  arbol.insert(3);
  arbol.insert(2);
  arbol.insert(4);
  arbol.insert(8);
  arbol.insert(6);
  arbol.insert(1);
  AVL<int>::iterator itf1,itf2;

/*
  itf1=arbol.find(1);
  itf1=arbol.upper_bound(2);
  cout << "F1: "<< (*itf1).first <<endl;
  itf2=arbol.find(3);


  cout << "F2: "<< (*itf2).first <<endl;
  cout << "Ahora el tamaño de nuestro arbol es: " << arbol.size() << endl;
  cout << "Recorremos los datos en inorden y los mostramos: ";
  */
  cout << "Mostramos en inorden el arbol\n\n[DATO-ALTURA]\n";
  AVL<int,less<int>>::iterator it;
  it=arbol.begin();
  while(it!=arbol.end()){
    cout <<"   [" <<(*it).first << "-"<<(*it).second << "]\n";
    ++it;
  }

}
