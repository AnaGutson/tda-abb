#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

#define EXITO 0
#define ERROR -1

#define CANT_TIPOS_DE_ORDEN 3


//------------------------------------------------------------------VALIDACIONES

/* 
Pre-condiciones:
	"nodo" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve si existe "nodo->derecha".
*/
bool tiene_hijo_mayor(nodo_abb_t* nodo){

	return (nodo->derecha);
}

/* 
Pre-condiciones:
	"nodo" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve si existe "nodo->izquierda".
*/
bool tiene_hijo_menor(nodo_abb_t* nodo){

	return (nodo->izquierda);
}

/* 
Pre-condiciones:
	"nodo" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve si "nodo->derecha" y "nodo->izquierda" son nulos.
*/
bool es_nodo_hoja(nodo_abb_t* nodo){

	return (!tiene_hijo_mayor(nodo) && !tiene_hijo_menor(nodo));
}

/* 
Pre-condiciones:
	"nodo" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve si "nodo->derecha" o "nodo->izquierda" no son nulos.
*/
bool tiene_un_hijo(nodo_abb_t* nodo){

	return (!tiene_hijo_mayor(nodo) || !tiene_hijo_menor(nodo));
}

/* 
Pre-condiciones:
	.
Post-condiciones:
	la función devuelve si "recorrido" es igual a alguno de los valores válidos.
*/
bool es_recorrido_valido(int recorrido){

	return ((recorrido == ABB_RECORRER_INORDEN)
		|| (recorrido == ABB_RECORRER_PREORDEN)
		|| (recorrido == ABB_RECORRER_POSTORDEN));
}

//-----------------------------------------------------------OBTENER INFORMACIÓN

/* 
Pre-condiciones:
	"nodo" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve el nodo más a la derecha posible de "nodo".
*/
nodo_abb_t* predecesor_inorden(nodo_abb_t* nodo){
	nodo_abb_t* nodo_reemplazo = nodo;

	while(nodo->derecha){

		nodo_reemplazo = nodo->derecha;
		nodo = nodo->derecha;
	}

	return nodo_reemplazo;
}

/* 
Pre-condiciones:
	"nodo_padre" debe no ser nulo y sus campos ser válidos.
Post-condiciones:
	la función devuelve "nodo_padre->derecha" o "nodo_padre->izquierda".
*/
nodo_abb_t* nodo_hijo(nodo_abb_t* nodo_padre){
	nodo_abb_t* nodo_hijo;

	if(tiene_hijo_mayor(nodo_padre))
		nodo_hijo = (nodo_padre->derecha);
	else
		nodo_hijo = (nodo_padre->izquierda);

	return nodo_hijo;
}

/* 
Pre-condiciones:
	"**nodo_actual" debe no ser nulo y tener sus campos válidos:
		"nodo_actual->elemento" debe no ser nulo.
Post-condiciones:
	la función actualiza "nodo_actual" y "nodo_auxiliar";
	la función devuelve nodo_actual->elemento.
*/
void* elemento_auxiliar(nodo_abb_t* nodo_actual){
	nodo_abb_t* nodo_auxiliar = predecesor_inorden(nodo_actual->izquierda);
	void* elemento_auxiliar = nodo_actual->elemento;
	
	nodo_actual->elemento = nodo_auxiliar->elemento;
	nodo_auxiliar->elemento = elemento_auxiliar;

	return elemento_auxiliar;
}

//------------------------------------------------------------FUNCIONES PRIVADAS

/*
Pre-condiciones:
	"*arbol" es diferente a NULL;
	"comparador" es diferente a NULL.
Post-condiciones:
	la función actualiza el valor de sus campos por valores válidos.
*/
void inicializar_arbol(abb_t* arbol, abb_comparador comparador,
	abb_liberar_elemento destructor){
	
	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->destructor = destructor;
}

/*Pre-condiciones:
	-.
Post-condiciones:
	la función reserva, de ser posible, la cantidad de memoria necesaria para
		un nodo y lo inicializa, devolviendo un puntero al puntero creado o
		NULL en caso de error.
*/
nodo_abb_t* crear_nodo(void* elemento, nodo_abb_t* nodo_izquierda,
	nodo_abb_t* nodo_derecha){
	
	nodo_abb_t* nuevo_nodo;

	nuevo_nodo = malloc(sizeof(nodo_abb_t));
	if(!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->izquierda = nodo_izquierda;
	nuevo_nodo->derecha = nodo_derecha;

	return nuevo_nodo;
}

/* 
Pre-condiciones:
	"**siguiente" debe ser NULL;
	"*inserto" debe ser false.
Post-condiciones:
	la función actualiza "*siguiente" por "nuevo_nodo";
	la función actualiza el valor de "*inserto".
*/
void insertar_nodo(nodo_abb_t** siguiente, nodo_abb_t* nuevo_nodo, bool* inserto){
	
	*siguiente = nuevo_nodo;
	*inserto = true;
}

/* 
Pre-condiciones:
	"**nodo_actual" debe ser diferente de null y tener sus campos válidos:
		"nodo_actual->elemento" debe no ser nulo;
	"*nuevo_nodo" debe ser diferente de null y tener sus campos válidos:
		"nuevo_nodo->elemento" debe no ser nulo;
		"nuevo_nodo->derecha" debe ser nulo;
		"nuevo_nodo->izquierda" debe ser nulo;
Post-condiciones:
	la función actualiza "*nodo_actual" por "siguiente";
	la función, si "siguiente" es NULL, actualiza "siguiente" con "nuevo_nodo"; 
	la función devuelve si realizó la actualización de "siguiente" por "nuevo_nodo".
*/
bool avanzar(nodo_abb_t** nodo_actual, nodo_abb_t** siguiente, nodo_abb_t* nuevo_nodo){
	bool inserto = false;

	if(!*siguiente)
		insertar_nodo(siguiente, nuevo_nodo, &inserto);
	*nodo_actual = *siguiente;

	return inserto;
}

/* 
Pre-condiciones:
	"**nodo_actual" debe no ser nulo y tener sus campos válidos:
		"nodo_actual->elemento" debe no ser nulo;
	"*nuevo_nodo" debe ser diferente de null y tener sus campos válidos:
		"nuevo_nodo->elemento" debe no ser nulo;
		"nuevo_nodo->derecha" debe ser nulo;
		"nuevo_nodo->izquierda" debe ser nulo;
	"comparador" debe no ser nulo.
Post-condiciones:
	la función actualiza el abb, insertando "nuevo_nodo" en donde sea válido.
*/
void recorrer_e_insertar(nodo_abb_t* nodo_actual, nodo_abb_t* nuevo_nodo, abb_comparador comparador){
	int comparacion;
	bool inserto = false;

	do{

		comparacion = comparador(nuevo_nodo->elemento, nodo_actual->elemento);
		if(comparacion > 0)
			inserto = avanzar(&nodo_actual, &(nodo_actual->derecha), nuevo_nodo);
		else
			inserto = avanzar(&nodo_actual, &(nodo_actual->izquierda), nuevo_nodo);
	} while(!inserto);
}

/* 
Pre-condiciones:
	"**nodo" debe no ser nulo y tener sus campos válidos:
		"nodo->elemento" debe no ser nulo;
	"*destructor" puede ser o no nulo.
Post-condiciones:
	la función invoca a "destructor" de ser posible, para liberar "nodo->elemento";
	la función libera la memoria reservada para "nodo". 
*/
void destruir(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	
	if(destructor && nodo->elemento)
		destructor(nodo->elemento);
	if(nodo)
		free(nodo);
}

/*
Pre-condiciones:
	"cantidad_elementos" debe ser menor a "max".
	"array" debe tener max posiciones como mínimo.
Post-condiciones:
	la función se autoinvoca, así ir relllenando las posiciones de "array" en el 
		orden INORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de rellenar
		"array";
	la función retorna si "nodo_actual" es nulo, o si "cantidad_elementos" es 
		mayor o igual a "max".
*/
void rellenar_vector_inorden(nodo_abb_t* nodo_actual, void** array,
	size_t* cantidad_elementos, size_t max){

	if(!nodo_actual || (*cantidad_elementos >= max))
		return;

	rellenar_vector_inorden(nodo_actual->izquierda, array, cantidad_elementos, max);

	if(*cantidad_elementos >= max)
		return;
	array[*cantidad_elementos] = nodo_actual->elemento; 
	(*cantidad_elementos)++;

	rellenar_vector_inorden(nodo_actual->derecha, array, cantidad_elementos, max);
}

/*
Pre-condiciones:
	"cantidad_elementos" debe ser menor a "max".
	"array" debe tener max posiciones como mínimo.
Post-condiciones:
	la función se autoinvoca, así ir relllenando las posiciones de "array" en el 
		orden PREORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de rellenar
		"array";
	la función retorna si "nodo_actual" es nulo, o si "cantidad_elementos" es 
		mayor o igual a "max".
*/
void rellenar_vector_preorden(nodo_abb_t* nodo_actual, void** array,
	size_t* cantidad_elementos, size_t max){

	if(!nodo_actual || (*cantidad_elementos >= max))
		return;

	array[*cantidad_elementos] = nodo_actual->elemento; 
	(*cantidad_elementos)++;

	rellenar_vector_preorden(nodo_actual->izquierda, array, cantidad_elementos, max);

	rellenar_vector_preorden(nodo_actual->derecha, array, cantidad_elementos, max);	
}

/*
Pre-condiciones:
	"cantidad_elementos" debe ser menor a "max".
	"array" debe tener max posiciones como mínimo.
Post-condiciones:
	la función se autoinvoca, así ir relllenando las posiciones de "array" en el 
		orden POSTORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de rellenar
		"array";
	la función retorna si "nodo_actual" es nulo, o si "cantidad_elementos" es 
		mayor o igual a "max".
*/
void rellenar_vector_postorden(nodo_abb_t* nodo_actual, void** array,
	size_t* cantidad_elementos, size_t max){

	if(!nodo_actual || (*cantidad_elementos >= max))
		return;

	rellenar_vector_postorden(nodo_actual->izquierda, array, cantidad_elementos, max);

	rellenar_vector_postorden(nodo_actual->derecha, array, cantidad_elementos, max);	

	if(*cantidad_elementos >= max)
		return;
	array[*cantidad_elementos] = nodo_actual->elemento; 
	(*cantidad_elementos)++;
}

/*
Pre-condiciones:
	"arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser válido o nulo.
Post-condiciones:
	la función actualiza "array" con los elementos del arbol, colocandolos
		en las posiciones en el orden indicado;
	la función devuelve la cantidad de elementos del arbol, y en caso
		de que la cantidad sea mayor a "tamanio_array", devuelve 
		"tamanio_array" (cuantos elementos del array llenó);
	la función retorna 0 si el arbol está vacío, si "array" es nulo o si "max"
		es 0.
*/
size_t arbol_recorrido(abb_t* arbol, void** array, size_t max,
	void(*rellenar_vector)(nodo_abb_t*, void**, size_t*, size_t)){
	
	size_t cantidad_elementos = 0;

	if(arbol_vacio(arbol) || !array || !max)
		return 0;

	rellenar_vector(arbol->nodo_raiz, array, &cantidad_elementos, max);

	return cantidad_elementos;
}

/*
Pre-condiciones:
	"nodo_actual" debe no ser nulo y ser sus campos válidos;
	"destructor" debe ser válido o nulo.
Post-condiciones:
	la función se autoconvoca hasta que "nodo_actual->derecha" o
		"nodo_actual->izquierda" sean nulos, y ahí se libera el espacio ocupado
		por el nodo, y si es posible, por el elemento.
*/
void liberar_nodo(nodo_abb_t* nodo_actual, abb_liberar_elemento destructor){

	if(tiene_hijo_menor(nodo_actual))
		liberar_nodo(nodo_actual->izquierda, destructor);
	if(tiene_hijo_mayor(nodo_actual))
		liberar_nodo(nodo_actual->derecha, destructor);
	
	destruir(nodo_actual, destructor);
}

/*
Pre-condiciones:
	"funcion" debe no ser nula.
Post-condiciones:
	la función se autoinvoca, así ir invocando a "funcion()" en el orden INORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de invocar a 
		"funcion()";
	la función "termino" segun lo que devuelva "funcion()";
	la función retorna si "nodo_actual" es nulo, o si "termino" es true.
*/
void recorrido_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*),
	void* extra, bool* termino, size_t* cantidad_elementos){

	if(!nodo_actual || *termino)
		return;

	recorrido_inorden(nodo_actual->izquierda, funcion, extra, termino, cantidad_elementos);

	if(*termino)
		return;
	*termino = funcion(nodo_actual->elemento, extra);
	(*cantidad_elementos)++;
	
	recorrido_inorden(nodo_actual->derecha, funcion, extra, termino, cantidad_elementos);	
}

/*
Pre-condiciones:
	"funcion" debe no ser nula.
Post-condiciones:
	la función se autoinvoca, así ir invocando a "funcion()" en el orden PREORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de invocar a 
		"funcion()";
	la función "termino" segun lo que devuelva "funcion()";
	la función retorna si "nodo_actual" es nulo, o si "termino" es true.
*/
void recorrido_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*),
	void* extra, bool *termino, size_t* cantidad_elementos){

	if(!nodo_actual || *termino)
		return;

	*termino = funcion(nodo_actual->elemento, extra);
	(*cantidad_elementos)++;

	recorrido_preorden(nodo_actual->izquierda, funcion, extra, termino, cantidad_elementos);

	recorrido_preorden(nodo_actual->derecha, funcion, extra, termino, cantidad_elementos);	
}

/*
Pre-condiciones:
	"funcion" debe no ser nula.
Post-condiciones:
	la función se autoinvoca, así ir invocando a "funcion()" en el orden POSTORDEN;
	la función actualiza el valor de "cantidad_elementos" en caso de invocar a 
		"funcion()";
	la función "termino" segun lo que devuelva "funcion()";
	la función retorna si "nodo_actual" es nulo, o si "termino" es true.
*/
void recorrido_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*),
	void* extra, bool *termino, size_t* cantidad_elementos){

	if(!nodo_actual || *termino)
		return;

	recorrido_postorden(nodo_actual->izquierda, funcion, extra, termino, cantidad_elementos);

	recorrido_postorden(nodo_actual->derecha, funcion, extra, termino, cantidad_elementos);	

	if(*termino)
		return;
	*termino = funcion(nodo_actual->elemento, extra);
	(*cantidad_elementos)++;
}

/* 
Pre-condiciones:
	"*arbol" debe estar inicializado y tener todos sus campos válidos:
		"arbol->nodo_raiz" debe apuntar a una posición válida o ser nulo;
		"arbol->comparador" debe ser válido;
		"arbol->destructor" debe ser mayor válido o nulo.
	"*extra" debe ser el parámetro que se va a usar en funcion().
Post-condiciones:
	la función invoca a "funcion()" hasta que esta devuelva true;
	la función devuelve cuantas veces se invocó a funcion().
*/
size_t recorrer_cada_elemento(abb_t* arbol, bool (*funcion)(void*, void*),
	void* extra, void (*tipo_recorrido)(nodo_abb_t*,
	bool(*funcion)(void*, void*), void*, bool*, size_t*)){
	
	size_t cantidad_elementos = 0;
	bool termino = false;

	tipo_recorrido(arbol->nodo_raiz, funcion, extra, &termino, &cantidad_elementos);

	return cantidad_elementos;
}

//-------------------------------------------------------------------------ARBOL

/*** Pre y post condiciones en abb.h ***/
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* arbol = NULL;

	if(!comparador)
		return NULL;

	arbol = malloc(sizeof(abb_t));
	if(arbol)
		inicializar_arbol(arbol, comparador, destructor);

	return arbol;
}

/*** Pre y post condiciones en abb.h ***/
int arbol_insertar(abb_t* arbol, void* elemento){
	nodo_abb_t* nuevo_nodo;
	
	if(!arbol)
		return ERROR;

	nuevo_nodo = crear_nodo(elemento, NULL, NULL);
	if(!nuevo_nodo)
		return ERROR;
	
	if(arbol_vacio(arbol))
		arbol->nodo_raiz = nuevo_nodo;
	else
		recorrer_e_insertar(arbol->nodo_raiz, nuevo_nodo, arbol->comparador);

	return EXITO;
}

/*
Pre-condiciones:
	"elemento" debe debe ser válido;
   	"comparador" debe no ser nulo.
Post-condiciones:
	la función se autoinvoca (siempre con diferentes parámetros) hasta que
		"raiz->elemento" y "elemento" son iguales;
	la función, si "raiz->elemento" y "elemento" son iguales, analiza si
		"nodo->derecha" y "nodo->izquierda" son iguales, a partir de eso destruye
		libera o no la memoria reservada para raiz;
	la función retorna NULL o "raiz", con sus campos válidos;
	la función, si se pudo liberar la memoria para un nodo, actualiza el valor de "*devolución" a EXITO.
*/
nodo_abb_t* borrar_recursiva(nodo_abb_t* raiz, void* elemento, abb_comparador comparador,
	abb_liberar_elemento destructor, int *devolucion){

	if(!raiz)
		return NULL;

	if(comparador(elemento, raiz->elemento) < 0)
		raiz->izquierda = borrar_recursiva(raiz->izquierda, elemento, comparador, destructor, devolucion);
	else if(comparador(elemento, raiz->elemento) > 0)
		raiz->derecha = borrar_recursiva(raiz->derecha, elemento, comparador, destructor, devolucion);
	else{

		if(es_nodo_hoja(raiz)){

			destruir(raiz, destructor);
			*devolucion = EXITO;
			return NULL;
		}
		else if(tiene_un_hijo(raiz)){

			nodo_abb_t* nodo_auxiliar = nodo_hijo(raiz);
			destruir(raiz, destructor);
			*devolucion = EXITO;
			return nodo_auxiliar;
		}
		else{

			void* elemento_actual = elemento_auxiliar(raiz);
			raiz->izquierda = borrar_recursiva(raiz->izquierda, elemento_actual, comparador, destructor, devolucion);
		}
	}

	return raiz;
}

/*** Pre y post condiciones en abb.h ***/
int arbol_borrar(abb_t* arbol, void* elemento){
	int devolucion = ERROR;

	if(arbol_vacio(arbol))
		return ERROR;
	
	arbol->nodo_raiz = borrar_recursiva(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor, &devolucion);

	return devolucion;
}

/*** Pre y post condiciones en abb.h ***/
void* arbol_buscar(abb_t* arbol, void* elemento){
	nodo_abb_t* nodo_actual, *nodo_siguiente = NULL;
	int comparacion;
	bool encontro = false;
	void* devolucion = NULL;

	if(arbol_vacio(arbol))
		return NULL;

	nodo_actual = arbol->nodo_raiz;
	do{

		comparacion = arbol->comparador(elemento, nodo_actual->elemento);
		if(comparacion > 0)
			nodo_siguiente = nodo_actual->derecha;
		else if(comparacion < 0)
			nodo_siguiente = nodo_actual->izquierda;
		else
			devolucion = nodo_actual->elemento;

		if(!nodo_siguiente || devolucion)
			encontro = true;
		nodo_actual = nodo_siguiente;
	} while(!encontro);

	return devolucion;
}

/*** Pre y post condiciones en abb.h ***/
void* arbol_raiz(abb_t* arbol){

	if(arbol_vacio(arbol))
		return NULL;

	return ((arbol->nodo_raiz)->elemento);
}

/*** Pre y post condiciones en abb.h ***/
bool arbol_vacio(abb_t* arbol){

	return (!arbol || !(arbol->nodo_raiz));
}

/*** Pre y post condiciones en abb.h ***/
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t max){

	return arbol_recorrido(arbol, array, max, rellenar_vector_inorden);
}

/*** Pre y post condiciones en abb.h ***/
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t max){

	return arbol_recorrido(arbol, array, max, rellenar_vector_preorden);
}

/*** Pre y post condiciones en abb.h ***/
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t max){

	return arbol_recorrido(arbol, array, max, rellenar_vector_postorden);
}

/*** Pre y post condiciones en abb.h ***/
void arbol_destruir(abb_t* arbol){

	if(!arbol_vacio(arbol))
		liberar_nodo(arbol->nodo_raiz, arbol->destructor);
	if(arbol)
		free(arbol);
}

/*** Pre y post condiciones en abb.h ***/
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido,
	bool (*funcion)(void*, void*), void* extra){
	
	size_t cantidad = 0;
	void(*tipo_recorrido[CANT_TIPOS_DE_ORDEN])(nodo_abb_t*, bool(*funcion)(void*, void*), void*, bool*, size_t*)
		= {recorrido_inorden , recorrido_preorden, recorrido_postorden};
	
	if(funcion && !arbol_vacio(arbol) && es_recorrido_valido(recorrido))
		cantidad = recorrer_cada_elemento(arbol, funcion, extra, tipo_recorrido[recorrido]);

	return cantidad;
}