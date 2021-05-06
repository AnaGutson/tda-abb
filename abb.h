#ifndef __ARBOL_BINARIO_DE_BUSQUEDA_H__
#define __ARBOL_BINARIO_DE_BUSQUEDA_H__

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2

#include <stdbool.h>
#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*abb_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*abb_liberar_elemento)(void*);


typedef struct nodo_abb {
  void* elemento;
  struct nodo_abb* izquierda;
  struct nodo_abb* derecha;
} nodo_abb_t;

typedef struct abb{
  nodo_abb_t* nodo_raiz;
  abb_comparador comparador;
  abb_liberar_elemento destructor;
} abb_t;

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
/*
Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		un arbol y lo inicializa, devolviendo un puntero al arbol creado o
		NULL en caso de error.
*/
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor);

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo;
   "*elemento" debe ser distinto de null, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función solicita memoria para un nuevo nodo, en caso de obtenerla
		inicializa sus campos de manera válida. Se coloca el nuevo nodo en una
		posición válida;
	la función devuelve ERROR si no hay árbol o si no se pudo reservar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int arbol_insertar(abb_t* arbol, void* elemento);

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo;
   "*elemento" debe no ser nulo, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función libera la memoria reservada para el elemento y el nodo que lo
		contiene, de ser posible;
	la función devuelve ERROR si no hay árbol o si no se pudo liberar memoria;
	la función devuelve EXITO si pudo cumplir con éxito su cometido.
*/
int arbol_borrar(abb_t* arbol, void* elemento);

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo;
   "*elemento" debe no ser nulo, sino no se podrá diferenciar de una
   		posición vacía.
Post-condiciones:
	la función devuelve el nodo buscado;
	la función devuelve NULL en caso de que el arbol esté vacío o que no se
		encuentre el nodo buscado.
*/
void* arbol_buscar(abb_t* arbol, void* elemento);

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función devuelve NULL en caso de que "arbol" no exista o esté vacío;
	la función devuelve "(arbol->nodo_raiz)->elemento".
*/
void* arbol_raiz(abb_t* arbol);

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
/*
Pre-condiciones:
	.
Post-condiciones:
	la función devuelve si no existe el árbol o si su nodo raíz es nulo.
*/
bool arbol_vacio(abb_t* arbol);

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función actualiza "array" con los elementos del arbol, colocandolos
		en las posiciones en el orden INORDEN;
	la función devuelve la cantidad de elementos del arbol, y en caso
		de que la cantidad sea mayor a "tamanio_array", devuelve 
		"tamanio_array" (cuantos elementos del array llenó).
*/
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array);

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función actualiza "array" con los elementos del arbol, colocandolos
		en las posiciones en el orden PREORDEN;
	la función devuelve la cantidad de elementos del arbol, y en caso
		de que la cantidad sea mayor a "tamanio_array", devuelve 
		"tamanio_array" (cuantos elementos del array llenó).
*/
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array);

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función actualiza "array" con los elementos del arbol, colocandolos
		en las posiciones en el orden POSTORDEN;
	la función devuelve la cantidad de elementos del arbol, y en caso
		de que la cantidad sea mayor a "tamanio_array", devuelve 
		"tamanio_array" (cuantos elementos del array llenó).
*/
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array);

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función libera la memoria reservada para el árbol, lo que involucra también
		liberar la memoria ocupada por los nodos del árbol;
	la función libera la memoria reservada para los elementos del árbol, si es que
		hay un destructor válido;
	la función termina si no hay árbol.
*/
void arbol_destruir(abb_t* arbol);

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/
/* 
Pre-condiciones:
	"*arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser mayor válido o nulo.
	"*extra" debe ser el parámetro que se va a usar en funcion().
Post-condiciones:
	la función invoca a "funcion()" hasta que esta devuelva true;
	la función devuelve cuantas veces se llamó a funcion();
	la función devuelve 0 si no hay arbol, hay pero está vacío, si 
		no hay función o si el recorrido indicado no es válido.
*/
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);

#endif /* __ARBOL_BINARIO_DE_BUSQUEDA_H__ */
