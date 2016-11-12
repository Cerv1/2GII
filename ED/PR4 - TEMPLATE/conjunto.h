/*
 * conjunto.h
 *
 * Copyright  (C) Juan F. Huete
*/

#ifndef __CONJUNTO_H
#define __CONJUNTO_H
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include "crimen.h"

using namespace std;
template <typename CMP>


//! Clase conjunto
/*! Métodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Además encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al número de elementos en el conjunto.

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática.

 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 @todo Implementa esta clase, junto con su documentación asociada
 */



class conjunto{

public:

/** @brief entrada permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto
    */
	typedef crimen entrada;

/** @brief size_type numero de elementos en el conjunto
    */
	typedef unsigned int size_type;

/** @brief constructor primitivo.
	*/
	conjunto( );



//declaraciones previa de los iteradores
	class iterator;
   	class const_iterator;
   	class arrest_iterator; // Iterador sobre los delitos que implicaron un arresto (Arrest==true)
   	class const_arrest_iterator;
   	class description_iterator;  // Iterador sobre los delitos que concuerdan con la descripcion
   	class const_description_iterator;

/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	conjunto (const conjunto & d);

	conjunto(conjunto::iterator ini, conjunto::iterator fin);
	conjunto::iterator find(const crimen & c);
	conjunto::const_iterator find(const crimen & c)const;

	/**@brief Devuelven un iterador al primer elemento en el contenedor que no precede a x en el conjunto, esto es
	equivalente a x o le sigue según la relacion de orden definida por CMP.	Esta función utiliza el functor interno
	devolviendo un iterator al primer elemento, e, para el que se satisface que comp(e,x) es falso.
	*/
	conjunto::iterator lower_bound (const conjunto::entrada & x);

	/**@brief Devuelven un iterador al primer elemento en el contenedor que no precede a x en el conjunto, esto es
	equivalente a x o le sigue según la relacion de orden definida por CMP.
	Esta función utiliza el functor interno devolviendo un const_iterator al primer elemento, e, para el que se satisface que comp(e,x) es falso.
	*/
	conjunto::const_iterator lower_bound (const entrada & x) const;

	/**@brief ; Devuelven un iterador al primer elemento que sigue a x según la relacion de orden definida por CMP.
	Esta función utiliza el functor interno devolviendo un iterator al primer elemento, e, para el que se satisface
	que comp(x,e) es cierto.
	*/
	conjunto::iterator upper_bound (const entrada & x);

	/**@brief ; Devuelven un iterador al primer elemento que sigue a x según la relacion de orden definida por CMP.
	Esta función utiliza el functor interno devolviendo un const_iterator al primer elemento, e, para el que se satisface
	que comp(x,e) es cierto.
	*/
	conjunto::const_iterator upper_bound (const entrada & x) const;

/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo


	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	conjunto::iterator  find( const long int & id);

/** @brief busca un crimen en el conjunto
	@param id identificador del crimen  buscar
	@return Si existe una entrada en el conjunto devuelve un iterador a lo posicion donde está el elemento. Si  no se encuentra devuelve end()
	@post no modifica el conjunto.
	\code Ejemplo


	if (C.find(12345)!=C.end() ) cout << "Esta" ;
	else cout << "No esta";
	\endcode
	*/
	conjunto::const_iterator  find(const long int & id) const;

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
	conjunto findIUCR(const string & iucr) const;

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
	conjunto findDESCR(const string & descr) const;

/** @brief Inserta una entrada en el conjunto
	@param e entrada a insertar
	@return true si la entrada se ha podido insertar con éxito. False en caso contrario
	@post Si e no esta en el conjunto, el size() sera incrementado en 1.
	*/
	bool insert(const conjunto::entrada & e);

/** @brief Borra el delito dado un identificacador.
	Busca la entrada con id en el conjunto  y si la encuentra la borra
	@param[in] id a borrar
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	bool erase(const long int & id);


/** @brief Borra una crimen con identificador dado por e.getID() en el conjunto.
	Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra
	@param[in] entrada con e.getID() que geremos borrar, el resto de los valores no son tenidos en cuenta
	@return true si la entrada se ha podido borrar con éxito. False en caso contrario
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	bool erase(const conjunto::entrada & e);


/** @brief operador de asignación
	@param[in] org conjunto  a copiar.
	Crea un conjunto duplicado exacto de org.
	*/
	conjunto & operator=(const conjunto & org);

/** @brief numero de entradas en el conjunto
	@post  No se modifica el conjunto.
	*/
	size_type size() const;


/** @brief Chequea si el conjunto esta vacio
	@return true si size()==0, false en caso contrario.
	*/
	bool empty() const;

/** @brief	Busca en nuestro conjunto el elemento con el ID pasado por parámetro.
	@return Posición del elemento buscado. -1 si no lo encuentra
	*/
	long int ExisteElemento(const long int &ID)const;

	// ================================= ITERADORES ========================================/

/**@brief devuelve iterador al inicio del conjunto
	*/
	iterator begin();

/**@brief devuelve iterador al final (posición siguiente al último del conjunto
	*/
	iterator end();

/** @brief class iterator
	* forward iterador sobre el conjunto, LECTURA
	*  iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
	*/
    class iterator{
    public:
		iterator();
		iterator(const iterator & it);

		const conjunto::entrada & operator*() const;

		iterator operator++(int );
		iterator & operator++();
		iterator operator--(int );
		iterator & operator--();
		bool operator==(const iterator & it);
		bool operator!=(const iterator & it);

	private:
		friend class conjunto;
		conjunto *ptr;
		vector<entrada>::iterator itv;
};

/** @brief Iterador al principio del conjunto.
	@return Devuelve el const_iterator a la primera posición del conjunto.
	@post no modifica el conjunto.
	*/
	const_iterator cbegin() const;

/** @brief Iterador al final del conjunto.
	@return Devuelve el iterador constante a la  posición final del conjunto.
	@post no modifica el conjunto.
	*/
	const_iterator cend() const;

/** @brief class const_iterator
	* forward iterador constante sobre el conjunto, Lectura
	*  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
	*/
	class const_iterator {
	public:
		const_iterator();
		const_iterator(const const_iterator & it);
		const_iterator(const iterator & it);
		const conjunto::entrada & operator*() const;
		const_iterator operator++( int  );
		const_iterator & operator++();
 		const_iterator operator--(int );
		const_iterator & operator--();
		bool operator==(const const_iterator & it);
		bool operator!=(const const_iterator & it);

	private:
		vector<entrada>::const_iterator c_itv;
		const conjunto *ptr;
		friend class conjunto;

	};

/** @brief Iterador al primer arresto del conjunto.
	@return Un iterador al primer arresto del conjunto.
	*/
	arrest_iterator abegin();

/**	@brief Iterador al ultimo arresto del conjunto.
	@return Devuelve un iterador donde se produce el ultimo crimen con arresto del conjunto.
	*/
	arrest_iterator aend();

/** @brief class arrest_iterator
	* forward iterador sobre el conjunto, LECTURA
	*  arrest_iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
	*/
	class arrest_iterator{

	public:
		arrest_iterator();
		arrest_iterator(const arrest_iterator & it);
		const conjunto::entrada & operator*() const;
		arrest_iterator operator++(int);
		arrest_iterator & operator++();
		arrest_iterator operator--(int);
		arrest_iterator & operator--();
		bool operator==(const arrest_iterator & it);
		bool operator!=(const arrest_iterator & it);

	private:
		vector<entrada>::iterator a_itv;
		conjunto *ptr;
		friend class conjunto;

	};
/** @brief Iterador al primer arresto del conjunto.
	@return Devuelve un const_arrest_iterator al primer arresto.
	@post NO modifica el conjunto.
	*/
	const_arrest_iterator cabegin();

/** @brief Iterador al ultimo arresto del conjunto.
	@return Devuelve un const_arrest_iterator al ultimo crimen donde se produce un arresto.
	@post NO modifica el conjunto.
	*/
	const_arrest_iterator caend();
/** @brief class iterator
	* forward iterator sobre el conjunto, LECTURA
	*  const_arrest_iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
	*/
	class const_arrest_iterator{
	public:
		const_arrest_iterator();
		const_arrest_iterator(const const_arrest_iterator & it);
		const conjunto::entrada & operator*() const;
		const_arrest_iterator operator++(int);
		const_arrest_iterator & operator++();
		const_arrest_iterator operator--(int);
		const_arrest_iterator & operator--();
		bool operator==(const const_arrest_iterator & it);
		bool operator!=(const const_arrest_iterator & it);

	private:
		vector<entrada>::const_iterator ca_itv;
		const conjunto *ptr;
		friend class conjunto;
	};
        // ============================== description iterator ===============================


/** @brief devolver primera posicion del elemento que empareja con la descripcion descr
	@param[in] descr descripcion de buscamos
	@return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
	*/
	description_iterator dbegin(const string & descr);

/** @brief Devolver la ultima descripcion que empareje a "descr" del conjunto.
	@return un iterador que apunta a la posicion final
	*/
	description_iterator dend();

/** @brief class description_iterator
	* forward iterador constante sobre el conjunto, Lectura
	*  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
    * esta clase itera sobre todos los elementos que emparejan con una descripcion
	*/
	class description_iterator {
	public:
		description_iterator();
		description_iterator(const description_iterator & it);
		const conjunto::entrada & operator*() const;
		description_iterator operator++( int );
		description_iterator & operator++();
 		description_iterator operator--(int );
   	description_iterator & operator--();
		bool operator==(const description_iterator & it);
		bool operator!=(const description_iterator & it);
		friend class conjunto;
	private:
		friend class conjunto;
		conjunto *ptr;
		string descr;  // la descripcion se asigna en con el metodo dbegin
		vector<entrada>::iterator d_itv;

	};
/** @brief devolver primera posicion del elemento que empareja con la descripcion descr
	@param[in] descr descripcion de buscamos
	@return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
	@post NO modifica el conjunto.
	*/
	const_description_iterator cdbegin(const string & descr);

/** @brief Devolver la ultima descripcion que empareje a "descr" del conjunto.
	@return un iterador que apunta a la posicion final con la subcadena "descr".
	@post NO modifica el conjunto.
	*/
	const_description_iterator cdend();

	class const_description_iterator{
	public:
		const_description_iterator();
		const_description_iterator(const const_description_iterator &it);
		const conjunto::entrada & operator*() const;
		const_description_iterator operator++(int);
		const_description_iterator & operator++();
		const_description_iterator operator--(int);
		const_description_iterator & operator--();
		bool operator==(const const_description_iterator &it);
		bool operator!=(const const_description_iterator &it);

	private:
		string descr;
		const conjunto *ptr;
		vector<entrada>::const_iterator cd_itv;
		friend class conjunto;
	};

private:
	vector<crimen> vc; // vector ORDENADO por crimen.id que almacena los elementos del conjunto
	CMP comp;
/** \invariant

IR: rep ==> bool

\li Para todo i, 0 <= i < vc.size() se cumple
	vc[i].ID > 0;
\li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
	vc[i].ID< vc[i+1].ID

*/


/** @brief Chequea el Invariante de la representacion
	@return true si el invariante es correcto, falso en caso contrario
	*/
	bool cheq_rep( ) const;

	// declaracion del operator<< como metodo amigo
	template <class X>
	friend ostream &  operator<<( ostream & sal, const conjunto<X> & D);


	conjunto::iterator busquedaBinaria (const crimen &d );

// Clases amigas  ....
	friend class description_iterator;
	friend class const_description_iterator;
	friend class iterator;
	friend class const_iterator;
	friend class arrest_iterator;
	friend class const_arrest_iterator;
};

/** @brief imprime todas las entradas del conjunto
	@post No se modifica el conjunto.
	@todo implementar esta funcion
	*/


	template <class X>
	ostream &  operator << ( ostream & sal, const conjunto<X> & D){
		for(int i=0; i<D.size(); i++){
			sal << D.vc[i] << endl;
		}

		return sal;
	}

#include "conjunto.hxx"

#endif
