/** ESTA PRÁCTICA HA SIDO RESUELTA EN SU TOTALIDAD POR SERGIO CERVILLA ORTEGA, DNI: 14275233F- */
#include "crimen.h"
#include "fecha.h"
#include "css.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
using namespace std;
int main(){

  ifstream fe;
  string cadena;
  string base="crimenes.csv";
  CSS baseDatos;
  baseDatos.load(base);

  cout << "BATERIA DE PRUEBAS - PARTE 1 - ORDENADOS POR ID\n\n";

  CSS::iterator ini=baseDatos.begin();
  CSS::iterator fin=baseDatos.end();
  while(ini!=fin){
    cout << (*ini).first << endl;
    ini++;
  }
  unsigned int ID_Prueba=10230974;
  CSS::iterator it_arrest=baseDatos.find_ID(ID_Prueba);
  cout << "\nBuscamos el ID " << ID_Prueba << " y mostramos su contenido."<<endl;
  cout << (*it_arrest).second<<endl;
  cout << "\nLe ponemos el campo arrest a true y mostramos de nuevo.\n";
  baseDatos.setArrest(ID_Prueba,true);
  cout << (*it_arrest).second<<endl;

//---------------------------------------------------------------------------------

  cout << "\n\n\n\nBATERIA DE PRUEBAS - PARTE 2 - ORDENADOS POR FECHA\n\n";
  CSS::Date_iterator ini_date=baseDatos.dbegin();
  CSS::Date_iterator fin_date=baseDatos.dend();
  while(ini_date!=fin_date){
    cout << (*ini_date).second.getDate()<< endl;
    ini_date++;
  }

  ini_date=baseDatos.dbegin();
  for(int i=0;i<7;i++)
    ini_date++;

  fecha fecha_prueba=(*ini_date).second.getDate();
  ini_date=baseDatos.dbegin();
  fin_date=baseDatos.dend();

  cout << "\n\nCalculamos el lower_bound de 09/10/2015 11:23:00. \nEl crimen es: ";
  ini_date=baseDatos.lower_bound(fecha_prueba);
  cout << (*ini_date).second.getDate()<<endl;


//---------------------------------------------------------------------------------

  cout << "\n\n\n\nBATERIA DE PRUEBAS - PARTE 3 - CONSULTA GEOGRÁFICA\n\n";

  double x1,x2,y1,y2;
  x1=41.6;
  x2=41.9;
  y1=-87.72;
  y2=-87.68;
  ini=baseDatos.begin();
  fin=baseDatos.end();
  while(ini != fin){
    cout << "ID: " << (*ini).second.getID() << "  Latitud: " << (*ini).second.getLatitude() << "  Longitud: " << (*ini).second.getLongitude() << endl;
    ini++;
  }
  list<unsigned int> listgeo;
  list<unsigned int>::iterator itgeoini;
  list<unsigned int>::iterator itgeofin;
  ini=baseDatos.begin();
  listgeo=baseDatos.inArea(x1,y1,x2,y2);
  cout << "\n\nConsultamos los crímenes comprendidos entre \n41.6<Latitud<41.9 y -87.72<Longitud<-87.68\n"<<endl;
  itgeoini=listgeo.begin();
  itgeofin=listgeo.end();
  while(itgeoini != itgeofin){
    cout << *itgeoini << endl;
    itgeoini++;
  }

}
