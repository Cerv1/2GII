/** ESTA PRÁCTICA HA SIDO RESUELTA EN SU TOTALIDAD POR SERGIO CERVILLA ORTEGA, DNI: 14275233F- */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <utility>
#include <list>
#include <set>
#include <unordered_map>
#include <fstream>
#include "fecha.h"
#include "crimen.h"
typedef double Longitud;
typedef double Latitud;
typedef unsigned int ID;
typedef string Termino;
typedef string IUCR;

#ifndef __CSS_H
#define __CSS_H

class CSS{


private:

/** @brief Los distintos delitos se almacenan por orden creciente de ID en un diccionario (map),que llamaremos baseDatos,
    donde la clave será el ID (ya que asumimos que no hay dos delitos con el mismo valor de ID), y en la descripción
    tenemos almacenada toda la información relativa al crimen.Es importante destacar que la inserción y borrado de
    elementos en el map no invalida los iteradores. Esto nos facilitará las labores de implementación de los métodos.
*/
  map<ID,crimen> baseDatos;

/** @brief Esta estructura se utilizará para permitir un acceso eficiente por fecha. Como es importante la secuencia cronológica,
    consideraremos un contenedor asociativo. Además, como puede haber más de un crimen en la misma fecha hemos seleccionado
    como estructura el multimap. En el campo definición solamente almacenamos un iterador que apunta a la dirección del map
    donde se encuentra el elemento.Cuando un nuevo crimen se inserta en baseDatos debemos de insertar la posición en la que
    se insertó en el multimap y en  el caso de borrarlo de la base de datos, también debe ser borrado del multimap.
*/
  multimap<fecha, map<ID,crimen>::iterator > DateAccess;

/** @brief Esta estructura se utiliza para facilitar el acceso por IUCR, en este caso para cada IUCR tenemos el conjunto de delitos,
    representados por su ID, que han sido clasificados mediante dicho código. Utilizamos un map por ser importante el orden
    de los delitos dentro del conjunto. Esta estructura se actualiza cada vez que se inserta o borra un nuevo delito.
*/
  map<IUCR,set<ID> > IUCRAccess;

/** @brief En este caso, para cada termino en la descripción de un delito almacenamos en un conjunto ordenado los IDs de los delitos
    que han sido descritos mediante dicho termino. Esta estructura se actualiza cada vez que se inserta o borra un nuevo delito.
*/
  unordered_map<Termino, set<ID> > index;

/** @brief En este caso la posición geográfica la almacenamos en una estructura ordenada donde la clave, que asumimos única, se
    corresponde con la longitud donde se produce el delito. En este caso, los delitos están ordenados en orden creciente por
    este valor de coordenada. Para cada una de ellas almacenamos las coordenadas de latitud donde se cometió el delito. Como
    para una misma coordenada x,y puede haber más de un delito en el tiempo, se considera una estructura de multimap. Esta
    estructura se actualiza cada vez que se inserta o borra un nuevo delito.
*/
  map<Longitud,multimap<Latitud, ID> > posicionGeo;


/** @brief Una funcion que nos añade todos los ID de los dos conjuntos y además su peso en un map que se retorna.
*/
  map<ID,float> unionPeso( const set<ID> & t1, const set<ID> &t2);

public:

/** @brief Se encarga de leer los elementos de un fichero dado por el argumento nombreDB, e insertar toda la información en
    la base de datos. Recordad que para esta práctica se os pide que extendáis el campo descripción a todas las descripciones
    que se encuentra en la base de datos.Pare ello será necesario modificar la clase crimen utilizada en la práctica anterior.
*/
  void load(string nombreDB);

/** @brief Este método se encarga de insertar un nuevo crimen en CSS. Como prerrequisito se asume que el crimen
    no está ya almacenado en el conjunto.
*/
  void insert( const crimen & x);

/** @brief En este caso, se trata de borrar un crimen de la base de datos dado su ID. Devuelve verdadero si
    el crimen ha sido borrado correctamente, falso en caso contrario.
*/
  bool erase( unsigned int ID);

/** @brief Modifica el campo arrest de un crimen identificado por ID. Será necesario cuando se detenga un criminal
    con posterioridad a la inserción del delito en CSS.
*/
  void setArrest(const unsigned int ID, bool value);

/** @brief Si la lista tiene un único termino, buscamos el término en el index y devolvemos una lista con todos los ID del conjunto asocidado,
    con el valor second del par a 1.0. Si la lista tiene dos términos, debemos hacer una unión de las dos listas de IDs asociadas a los términos,
    pero en el caso en que exista un ID que esté en ambos conjuntos (los dos términos están en la descripción del ID), debemos contar su peso
    como 2, en caso contrario como los IDs pertenecen sólo a una lista y por tanto su peso será 1. En este proceso se puede aprovechar que los
    conjuntos están ordenados en orden creciente de ID. Para ello, podemos diseñar un método privado llamado "unionPeso". Para más de dos términos
    podemos utilizar el método anterior para hacer la unión de las dos primeras listas de ID, y utilizar el siguiente método para ir actualizando
    en el map la información asociada al resto de términos de la consulta.
*/
  vector<pair<ID,float> > Query(list<string> & q, int k);

/** @brief En este caso la posición geográfica la almacenamos en una estructura ordenada donde la clave, que asumimos única,
    se corresponde con la longitud donde se produce el delito. En este caso, los delitos están ordenados en orden creciente
    por este valor de coordenada. Para cada una de ellas almacenamos las coordenadas de latitud donde se cometió el delito.
    Como para una misma coordenada x,y puede haber más de un delito en el tiempo, se considera una estructura de multimap.
*/
  list<ID> inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2 );



//-------------------------------- CLASS ITERATOR ---------------------------------------------------
  class iterator{
    private:
      /** @brief it  itera sobre los ID del map. */
      map<ID,crimen>::iterator it;
      friend class CSS;
    public:
      pair<const ID, crimen > & operator*();
      iterator operator++(int);
  		iterator & operator++();
  		bool operator==(const iterator & it);
  		bool operator!=(const iterator & it);
  };
//-------------------------------- CLASS IUCR_ITERATOR ----------------------------------------------
  class IUCR_iterator{
    private:
      /*@brief it_m itera sobre los IUCR del map. */
      map<IUCR,set<ID> >::iterator it_m;
      /*@brief it_s itera sobre los ID del set. */
      set<ID>::iterator it_s;
      CSS *ptr;
      friend class CSS;
    public:
        pair<const ID, crimen > & operator*();
        IUCR_iterator operator++(int);
    		IUCR_iterator & operator++();
    		bool operator==(const IUCR_iterator & it);
    		bool operator!=(const IUCR_iterator & it);
  };
//-------------------------------- CLASS DATE_ITERATOR ----------------------------------------------
  class Date_iterator{
    private:
         multimap<fecha, map<ID,crimen>::iterator>::iterator it_mm;
         friend class CSS;
    public:
        pair<const ID, crimen > & operator*();
        Date_iterator operator++(int);
    		Date_iterator & operator++();
    		bool operator==(const Date_iterator & it);
    		bool operator!=(const Date_iterator & it);
  };
//---------------------------------------------------------------------------------------------------

  /** @brief Devuelve un iterador al ID pasado por parámetro y en caso
      de no existir devuelve un iterador al principio del conjunto.
  */
    iterator find_ID(const unsigned int ID);

  /** @brief Devuelve un iterador al primer crimen del conjunto ordenado por ID.
  */
    iterator begin();

  /** @brief Devuelve un iterador al último crimen del conjunto ordenado por ID.
  */
    iterator end();

  /** @brief Devuelve un iterador al primer crimen del conjunto ordenado por IUCR.
  */
    IUCR_iterator ibegin();

  /** @brief Devuelve un iterador al último crimen del conjunto ordenado por IUCR.
  */
    IUCR_iterator iend();

  /** @brief Devuelve un iterador al primer crimen del conjunto ordenado por fecha.
  */
    Date_iterator dbegin();

  /** @brief Devuelve un iterador al último crimen del conjunto ordenado por fecha.
  */
    Date_iterator dend();

  /** @brief Devuelve la cota inferior en el contenedor ordenado por IUCR
      del IUCR pasado como parámetro.
  */
    IUCR_iterator lower_bound(IUCR);

  /** @brief Devuelve la cota superior en el contenedor ordenado por IUCR
      del IUCR pasado como parámetro.
  */
    IUCR_iterator upper_bound(IUCR);

  /** @brief Devuelve la cota inferior en el contenedor ordenado por fecha
      de la fecha pasada como parámetro.
  */
    Date_iterator lower_bound(fecha);
  /** @brief Devuelve la cota superior en el contenedor ordenado por fecha
      de la fecha pasada como parámetro.
  */
    Date_iterator upper_bound(fecha);




};
#include "css.hxx"
#endif
