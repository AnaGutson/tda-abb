#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "abb.h"
#include "ptda.h"

#define FIN					"\033[0m"
#define NEGRO				"\033[0m\033[30m"
#define GRIS				"\033[1m\033[30m"
#define ROJO_OSCURO			"\033[0m\033[31m"
#define ROJO_CLARO			"\033[1m\033[31m"
#define VERDE_CLARO			"\033[0m\033[32m"
#define VERDE_OSCURO		"\033[1m\033[32m"
#define AMARILLO			"\033[1m\033[33m"
#define MARRON				"\033[0m\033[33m"
#define AZUL_SUAVE			"\033[0m\033[34m"
#define AZUL 				"\033[1m\033[34m"
#define MAGENTA_SUAVE		"\033[0m\033[35m"
#define MAGENTA				"\033[1m\033[35m"
#define CELESTE_SUAVE 		"\033[0m\033[36m"
#define CELESTE				"\033[1m\033[36m"
#define SILVER				"\033[0m\033[37m"
#define BLANCO				"\033[1m\033[37m"

#define EXITO	0
#define ERROR	-1

#define COLOR_PAJARO_MACHO  			"Negro"
#define COLOR_PAJARO_HEMBRA  			"Gris"

#define MAX_TEXTO				200
#define MAX_CANTIDAD 			100
#define MAX_PAJAROS				100

#define IGUALES 		0
#define PRIMERO_MAYOR 	1
#define PRIMERO_MENOR 	-1

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2
#define RECORRIDO_INVALIDO     3

#define CONTADOR 	0

typedef struct pajaro{

    int id;
    char color[15];
}pajaro_t;

typedef struct contador{

	int totales;
	int ids_impares;
}contador_t;

//___________________________________________FUNCIONES PARA MANDAR POR PARAMETRO

/*06*/
nodo_abb_t* hijo_mayor(nodo_abb_t* nodo){

	if(!nodo)
		return NULL;

	return (nodo->derecha);
}

/*06*/
nodo_abb_t* hijo_menor(nodo_abb_t* nodo){
	
	if(!nodo)
		return NULL;
	
	return (nodo->izquierda);
}

/*06*/
nodo_abb_t* lider_arbol(abb_t* arbol){
	
	if(arbol_vacio(arbol))
		return NULL;

	return (arbol->nodo_raiz);
}

/*10*/
static nodo_abb_t* predecesor_inorden(nodo_abb_t* nodo){
	nodo_abb_t* nodo_reemplazo = nodo;

	while(hijo_mayor(nodo)){

		nodo_reemplazo = hijo_mayor(nodo);
		nodo = hijo_mayor(nodo);
	}

	return nodo_reemplazo;
}

/*03*/
nodo_abb_t* nodo_predesor_inorden(nodo_abb_t* nodo){

	return predecesor_inorden(hijo_menor(nodo));
}

/*10*/
nodo_abb_t* nodo_minimo(nodo_abb_t* nodo){
	nodo_abb_t* nodo_reemplazo = nodo;

	while(hijo_menor(nodo)){

		nodo_reemplazo = hijo_menor(nodo);
		nodo = hijo_menor(nodo);
	}

	return nodo_reemplazo;
}

/*03*/
int id_posiciones(void* posicion){

	return (int)(posicion);
}

/*07*/
int id_recorrido(void* posicion){
	int id = -1;

	if(((pajaro_t*)posicion))
		id = ((pajaro_t*)posicion)->id;

	return id;
}

//__________________________________________________________________VALIDACIONES

/*03*/
bool campos_validos(abb_t* arbol, nodo_abb_t* raiz, abb_comparador comparador, abb_liberar_elemento destructor){

	return (((arbol->nodo_raiz) == raiz)
		&& ((arbol->comparador) == comparador)
		&& ((arbol->destructor) == destructor));
}

/*03*/
bool pajaro_tiene_hijos(nodo_abb_t* nodo_actual){

	return (hijo_mayor(nodo_actual) || hijo_menor(nodo_actual));
}

/*09*/
bool id_correcto(nodo_abb_t* nodo_correcto, pajaro_t** pajaros, size_t pos){
	pajaro_t* pajaro_a_comparar;

	if(!nodo_correcto)
		return false;

	pajaro_a_comparar = (pajaro_t*)(nodo_correcto->elemento);

	return ((pajaro_a_comparar->id) == (pajaros[pos]->id));
}

/*09*/
bool color_correcto(nodo_abb_t* nodo_correcto, pajaro_t** pajaros, size_t pos){
	pajaro_t* pajaro_a_comparar;

	if(!nodo_correcto)
		return false;

	pajaro_a_comparar = (pajaro_t*)(nodo_correcto->elemento);

	return (strcmp(pajaro_a_comparar->color, pajaros[pos]->color) == 0);
}

/*06*/
bool caracteristicas_validas(nodo_abb_t* nodo_correcto, pajaro_t** pajaros, size_t pos){

	if(!nodo_correcto || !(nodo_correcto->elemento))
		return false;

	return (id_correcto(nodo_correcto, pajaros, pos)
		&& color_correcto(nodo_correcto, pajaros, pos));
}

/*12*/
bool es_posicion_borrada(int i, int* vector_borrados, int cant_borrados){
	bool es_posicion = false;
	size_t j = 0;

	while((j < cant_borrados) && !es_posicion){

		if((i + 1) == vector_borrados[j])
			es_posicion = true;
		j++;
	}

	return es_posicion;
}

/*11*/
bool vectores_iguales_insertar(pajaro_t** vector_1, pajaro_t** vector_2, size_t tope){
	bool iguales = true;
	size_t i = 0;

	while((i < tope) && iguales){
		
		iguales = (vector_1[i] == vector_2[i]);
		i++;
	}

	return iguales;
}

/*11*/
bool vectores_iguales_recorrido(pajaro_t** vector_1, pajaro_t** vector_2, int* posiciones, size_t tope){
	bool iguales = true;
	size_t i = 0;

	while((i < tope) && iguales){
		
		iguales = (vector_1[posiciones[i]] == vector_2[i]);
		i++;
	}

	return iguales;
}

/*17*/
bool vectores_iguales_borrar(pajaro_t** vector_1, pajaro_t** vector_2, size_t tope, int* vector_borrados, int cant_borrados){
	bool iguales = true;
	int i = -1, j = -1;

	do{	
		
		if(es_posicion_borrada(i, vector_borrados, cant_borrados)){

			while(es_posicion_borrada(i, vector_borrados, cant_borrados))
				i++;
		}
		i++;
		j++;
		iguales = (vector_1[i] == vector_2[j]);
	}while((j < (tope - 1)) && iguales);

	return iguales;
}

/*06*/
bool pajaro_correcto(abb_t* arbol, nodo_abb_t* nodo_actual, pajaro_t** pajaros, size_t posicion){

	if(!nodo_actual)
		return false;
			
	return arbol->comparador(arbol_buscar(arbol, (void**)pajaros[posicion]), (nodo_actual->elemento)) == IGUALES;
}

/*03*/
bool elemento_en_el_arbol(abb_t* arbol, pajaro_t* pajaro){

	return (arbol_buscar(arbol, (void**)pajaro));
}

//__________________________________________FUNCIONES PARA ABB CON CADA ELEMENTO 

bool cantidad_elementos(void* elemento, void* contador){

	if(elemento && contador)
		(*(int*)contador)++;

	return (!elemento || !contador);
}

bool cantidad_digitos_total(void* elemento, void* contador){

	if(elemento && contador)
		(*(int*)contador) += cant_digitos(((pajaro_t*)(elemento))->id);

	return (!elemento || !contador);
}

int cant_digitos_con_anteriores(int actual){
	
	if(actual == 0)
		return cant_digitos(actual);

	return cant_digitos(actual) + cant_digitos_con_anteriores(actual - 1);
}

bool ids_impares_12_primeras_posiciones(void* elemento, void* contador){

	if(elemento && contador && ((((pajaro_t*)elemento)->id) % 2 != 0) && (((contador_t*)contador)->totales < 12))
		(((contador_t*)contador)->ids_impares)++;
	
	(((contador_t*)contador)->totales)++;

	return (!elemento || !contador || (((contador_t*)contador)->totales >= 12));
}

int ids_impares_segun_recorrido(int numero_recorrido){
	int cantidad = 0;

	switch(numero_recorrido){
		case ABB_RECORRER_INORDEN:
			cantidad = 6;
			break;
		case ABB_RECORRER_PREORDEN:
			cantidad = 5;
			break;
		case ABB_RECORRER_POSTORDEN:
			cantidad = 7;
			break;
	}

	return cantidad;
}

void reiniciar_contador_iterador(contador_t* contador){

	contador->totales = 0;
	contador->ids_impares = 0;
}

//_______________________________________________________________MOSTRAR ERRORES

/*03*/
void mostrar_error_malloc(){

	printf(ROJO_CLARO "No sabemos qué ocurrió, disculpe las molestias. \n" FIN);
}

//____________________________________________________________________CREACIONES

/*16*/
int crear_pajaro(pajaro_t** conjunto_de_pajaros, size_t pos, int id){
	pajaro_t* pajaro;

	pajaro = malloc(sizeof(pajaro_t));
	if(!pajaro)
		return ERROR;

	pajaro->id = id;
	if((pos % 2) == 0)
		strcpy(pajaro->color, COLOR_PAJARO_MACHO);
	else
		strcpy(pajaro->color, COLOR_PAJARO_HEMBRA);

	conjunto_de_pajaros[pos] = pajaro;

    return EXITO;
}

/*19*/
pajaro_t** crear_valores_insertar(size_t cantidad_total, size_t cantidad_rellenar){
	pajaro_t** conjunto_de_pajaros = NULL;
	size_t i = 0;
	int devolucion = EXITO;

	conjunto_de_pajaros = malloc(sizeof(pajaro_t*)*cantidad_total);
	if(!conjunto_de_pajaros){

		mostrar_error_malloc();
		return NULL;
	}
   
	while((i < cantidad_rellenar) && (devolucion == EXITO)){

		devolucion = crear_pajaro(conjunto_de_pajaros, i, (int)i);
		i++;
	}

	return conjunto_de_pajaros;
}

/*11*/
pajaro_t** crear_vector_recorrido(){
	pajaro_t** inorden;

	inorden = malloc(sizeof(pajaro_t*)*MAX_PAJAROS);
	if(!inorden){

		mostrar_error_malloc();
		return NULL;
	}

	return inorden;
}

/*12*/
abb_t* crear_un_arbol(abb_comparador comparador, abb_liberar_elemento destructor, pajaro_t** pajaros){
	abb_t* arbol;

	arbol = arbol_crear(comparador, destructor);
	if(!arbol){
		
		mostrar_error_malloc();
		if(pajaros)
			free(pajaros);	
		return NULL;
	}

	return arbol;
}

//_______________________________________________________FUNCIONES PARA EL ÁRBOL

/*16*/
int comparador_pajaros(void* elemento_1, void* elemento_2){

	if(!elemento_1 || !elemento_2)
		return IGUALES;

	int id_elemento_1 = (((pajaro_t*)elemento_1)->id);
	int id_elemento_2 = (((pajaro_t*)elemento_2)->id);
	int devolucion = id_elemento_1 - id_elemento_2;

	char* color_elemento_1 = (((pajaro_t*)elemento_1)->color);
	char* color_elemento_2 = (((pajaro_t*)elemento_2)->color);

	if((devolucion == 0) && (strcmp(color_elemento_1, color_elemento_2) != 0))
		devolucion = PRIMERO_MENOR;

	return devolucion;
}

/*06*/
void destructor_pajaros(void* elemento){

	if(!elemento)
        return;

	free(elemento);
}

//____________________________________________________________FUNCIONES PRIVADAS

/*12*/
int colocar_un_pajaro(abb_t* arbol, pajaro_t* pajaro){
	int retorno = EXITO;

	retorno = arbol_insertar(arbol, pajaro);
	if(arbol && pajaro && !elemento_en_el_arbol(arbol, pajaro)){
		
		if(arbol->destructor)
			arbol->destructor(pajaro);
		retorno = ERROR;
	}

	return retorno;
}

/*10*/
int colocar_pajaros(abb_t* arbol, pajaro_t** pajaros, int *pos, size_t cantidad){
	int i = 0, retorno = EXITO;

	while((i < cantidad) && (retorno == EXITO)){
		
		retorno = colocar_un_pajaro(arbol, pajaros[pos[i]]);
		i++;
	}
	
	return retorno;
}

/*10*/
int sacar_pajaros(abb_t* arbol, size_t cantidad){
	int retorno = EXITO, i = 0;

	while((i < cantidad) && (retorno == EXITO)){
		
		retorno = arbol_borrar(arbol, arbol_raiz(arbol));
		i++;
	}

	return retorno;
}

/*11*/
void* buscar_pajaros(abb_t* arbol, pajaro_t** pajaros, size_t cantidad, int* posiciones){
	pajaro_t* pajaro_encontrado = arbol_buscar(arbol, pajaros[posiciones[0]]);
	int i = 0;

	while((i < cantidad) && pajaro_encontrado){
		
		pajaro_encontrado = arbol_buscar(arbol, pajaros[posiciones[i]]);
		i++;
	}

	return pajaro_encontrado;
}

/*21*/
void mostrar_accion(char* frase, void** vector, int (*id_mostrar)(void*), size_t tope){
	int id;

	printf(MAGENTA "\n");
	if(tope > 0){

		printf("%s\n", frase);
		for(int i = 0; i < tope; i++){

			id = id_mostrar(vector[i]);
			if(id < 0)
				printf("ID: no tiene");
			else
				printf("ID: %i", id);
			if(i < (tope - 1))
				printf(" - ");
			else
				printf(".\n");
		}
	}
	printf("Cantidad: %i.\n", (int)tope);
}

/*10*/
void mostrar_estado_arbol(abb_t* arbol, size_t(*recorrido)(abb_t*, void**, size_t)){
	size_t cantidad;
	pajaro_t** vector_recorrido = crear_vector_recorrido();
	if(!vector_recorrido)
		return;

	cantidad = recorrido(arbol, (void**)vector_recorrido, MAX_CANTIDAD);
	mostrar_accion("Los pajaros del árbol, ordenados por ID, son:", (void**)vector_recorrido, id_recorrido, cantidad);

	free(vector_recorrido);
}

/*07*/
nodo_abb_t* nodo_correcto_segun_insercion(nodo_abb_t* raiz, nodo_abb_t*(*nodo_segun_funcion)(nodo_abb_t*)){
	nodo_abb_t* nodo_devolver = NULL;

	if(raiz)
		nodo_devolver = nodo_segun_funcion(raiz);

	return nodo_devolver;
}

//___________________________________________________________PRUEBAS POR FUNCIÓN

/*10*/
void probar_crear_arbol_valido(abb_comparador comparador, abb_liberar_elemento destructor, char* frase){
	abb_t* arbol;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "%s: Se puede plantar un árbol.", frase);

	arbol = arbol_crear(comparador, destructor);
	ptda_afirmar(arbol, texto);
	ptda_subafirmar_fin((arbol && campos_validos(arbol, NULL, comparador, destructor)), "El árbol creció con una estructura válida.");
	arbol_destruir(arbol);
}

/*09*/
void probar_crear_arbol(){

	ptda_nuevo_subgrupo("Plantar - árbol");
	
	ptda_afirmar(!arbol_crear(NULL, destructor_pajaros), "No hay criterio para comparar pájaros: No se puede plantar un árbol.");
	
	probar_crear_arbol_valido(comparador_pajaros, NULL, "No hay criterio para que los pájaros emigren");

	probar_crear_arbol_valido(comparador_pajaros, destructor_pajaros, "Criterios parar comparar y emigrar válidos");
}

/*08*/
void probar_cosas_unico_pajaro(abb_t* arbol, nodo_abb_t* nodo_correcto, int retorno){

	if(arbol_vacio(arbol) || !pajaro_tiene_hijos(lider_arbol(arbol))){

		ptda_subafirmar(((retorno == EXITO) && (arbol_raiz(arbol) == (nodo_correcto->elemento))), "El pájaro colocado es el pájaro lider del árbol.");
		ptda_subafirmar(((retorno == EXITO) && !pajaro_tiene_hijos(nodo_correcto)), "El pájaro colocado no tiene hijos.");
		ptda_subafirmar(((retorno == EXITO) && (arbol_raiz(arbol) == (nodo_correcto->elemento)) && !pajaro_tiene_hijos(nodo_correcto)), "El pájaro colocado es el único pájaro del árbol.");
	}
}

/*14*/
void probar_insertar_primer_pajaro(abb_t* arbol, pajaro_t** pajaros, size_t id){
	int retorno;
	nodo_abb_t* nodo_correcto;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Árbol plantado y sin pájaros: Se puede colocar un pájaro (ID %i).", id);
	
	retorno = colocar_un_pajaro(arbol, pajaros[id]);
	ptda_afirmar((retorno == EXITO), texto);
	nodo_correcto = (lider_arbol(arbol));
	ptda_subafirmar(((retorno == EXITO) && nodo_correcto), "La cantidad de pájaros del árbol es 1.");
	probar_cosas_unico_pajaro(arbol, nodo_correcto, retorno);
	ptda_subafirmar(((retorno == EXITO) && nodo_correcto && ((arbol->comparador(nodo_correcto->elemento, pajaros[id])) == 0)), "El pájaro colocado es el esperado.");
	ptda_subafirmar_fin(((retorno == EXITO) && caracteristicas_validas(nodo_correcto, pajaros, id)), "Las características del pájaro colocado son correctas.");
}

/*14*/
void probar_insertar_hijo_lider(abb_t* arbol, pajaro_t** pajaros, size_t pos, char* frase, nodo_abb_t*(*nodo_segun_funcion)(nodo_abb_t*)){
	int retorno;
	nodo_abb_t* nodo_correcto;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Árbol con %s: Se puede colocar un pájaro (ID %i).", frase, pos);
	
	retorno = colocar_un_pajaro(arbol, pajaros[pos]);
	ptda_afirmar((retorno == EXITO), texto);
	nodo_correcto = nodo_correcto_segun_insercion(lider_arbol(arbol), nodo_segun_funcion);
	ptda_subafirmar(((retorno == EXITO) && nodo_correcto && (nodo_correcto->elemento)), "El pájaro está en la rama donde fue colocado.");
	ptda_subafirmar(((retorno == EXITO) && pajaro_correcto(arbol, nodo_correcto, pajaros, pos)), "El pájaro colocado es el hijo del líder.");
	ptda_subafirmar(((retorno == EXITO) && !pajaro_tiene_hijos(nodo_correcto)), "El pájaro colocado no tiene hijos.");
	ptda_subafirmar_fin(((retorno == EXITO) && caracteristicas_validas(nodo_correcto, pajaros, pos)), "Las características del pájaro colocado son correctas.");
}

/*13*/
void probar_insertar_pajaro_sin_identidad(abb_t* arbol, char* frase){
	int retorno;
	nodo_abb_t* nodo_correcto;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Árbol %s: Se puede colocar un pájaro recién nacido (sin identidad).", frase);
	
	retorno = colocar_un_pajaro(arbol, NULL);
	ptda_afirmar((retorno == EXITO), texto);
	nodo_correcto = nodo_correcto_segun_insercion(lider_arbol(arbol), nodo_minimo);
	ptda_subafirmar(((retorno == EXITO) && (nodo_correcto)), "El pájaro está en la rama donde fue colocado.");
	probar_cosas_unico_pajaro(arbol, nodo_correcto, retorno);
	ptda_subafirmar_fin(((retorno == EXITO) && nodo_correcto && !(nodo_correcto->elemento)), "El pájaro colocado es el esperado (es el pájaro más pequeño del árbol).");
}

/*16*/
void probar_insertar_gemelo_lider(abb_t* arbol, pajaro_t** pajaros, size_t pos){
	int id, retorno;
	char texto[MAX_TEXTO];
	nodo_abb_t* nodo_correcto;

	id = ((pajaro_t*)arbol_raiz(arbol))->id;
	snprintf(texto, MAX_TEXTO, "Árbol con 15 pájaros: Se puede colocar el pájaro gemelo del lider (ID %i).", id);

	crear_pajaro(pajaros, pos, id);
	retorno = colocar_un_pajaro(arbol, pajaros[pos]);
	ptda_afirmar((retorno == EXITO), texto);
	nodo_correcto = nodo_correcto_segun_insercion(lider_arbol(arbol), nodo_predesor_inorden);
	ptda_subafirmar(((retorno == EXITO) && nodo_correcto && (nodo_correcto->elemento)), "El pájaro está en la rama donde fue colocado.");
	ptda_subafirmar(((retorno == EXITO) && nodo_correcto && pajaro_correcto(arbol, nodo_correcto, pajaros, pos)), "El pájaro colocado es el esperado.");
	ptda_subafirmar(((retorno == EXITO) && !pajaro_tiene_hijos(nodo_correcto)), "El pájaro colocado no tiene hijos.");
	ptda_subafirmar_fin(((retorno == EXITO) && caracteristicas_validas(nodo_correcto, pajaros, pos)), "Las características del pájaro colocado son correctas.");
}

/*20*/
void probar_insertar_varios(abb_t* arbol, pajaro_t** pajaros, char* frase, int* orden_a_insertar, size_t cantidad_a_insertar){
	size_t cantidad_actual;
	int retorno;
	char texto[MAX_TEXTO];
	pajaro_t** inorden = crear_vector_recorrido();
	if(!inorden)
		return;
	
	size_t cantidad_previa = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);
	size_t cantidad_valida = cantidad_previa + cantidad_a_insertar;
	
	snprintf(texto, MAX_TEXTO, "Árbol con %s: Se pueden colocar los %i pájaros.", frase, cantidad_a_insertar);
	retorno = colocar_pajaros(arbol, pajaros, orden_a_insertar, cantidad_a_insertar);
	ptda_afirmar((retorno == EXITO), texto);
	cantidad_actual = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);
	snprintf(texto, MAX_TEXTO, "La cantidad de pájaros del árbol es %i.", cantidad_valida);
	ptda_subafirmar(((retorno == EXITO) && (cantidad_actual == cantidad_valida)), texto);
	ptda_subafirmar_fin(((retorno == EXITO) && vectores_iguales_insertar(pajaros, (pajaro_t**)inorden, cantidad_actual)), "Cada pájaro está en la rama donde fue colocado.");

	free(inorden);
}

int maximo(int a, int b){

	if(a > b)
		return a;
	else
		return b;
}

int altura_arbol(nodo_abb_t* nodo){
	
	if(!nodo)
		return ERROR;

	return maximo(altura_arbol(nodo->derecha), altura_arbol(nodo->izquierda)) + 1;
}

/*37*/
void probar_insertar_arbol(){
	abb_t* arbol;
	pajaro_t** pajaros = crear_valores_insertar(16, 15);
	if(!pajaros)
		return;
	
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	ptda_nuevo_subgrupo("Inserción - árbol");

	ptda_afirmar(colocar_un_pajaro(NULL, pajaros[0]) == ERROR, "Árbol sin plantar: No se puede colocar un pájaro.");
	probar_insertar_primer_pajaro(arbol, pajaros, 8);
	probar_insertar_hijo_lider(arbol, pajaros, 3, "1 pájaro", hijo_menor);
	probar_insertar_hijo_lider(arbol, pajaros, 10, "2 pájaros (lider e hijo menor)", hijo_mayor);
	
	int posiciones[] = {1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};
	mostrar_accion("Se intentan colocar, en este orden, los pajaros cuyo ID es:", (void**)posiciones, id_posiciones, 12);
	probar_insertar_varios(arbol, pajaros, "3 pájaros (lider, su hijo menor y su hijo mayor)", posiciones, 12);

	probar_insertar_gemelo_lider(arbol, pajaros, 15);
	probar_insertar_pajaro_sin_identidad(arbol, "con 16 pájaros");
	mostrar_estado_arbol(arbol, arbol_recorrido_inorden);

	printf(" ALtura: %i\n", altura_arbol(arbol->nodo_raiz));

	arbol_destruir(arbol);

	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	probar_insertar_pajaro_sin_identidad(arbol, "plantado y sin pájaros");
	mostrar_estado_arbol(arbol, arbol_recorrido_inorden);

	arbol_destruir(arbol);

	free(pajaros);
}

/*07*/
void probar_borrar_unico_pajaro(abb_t* arbol, pajaro_t* pajaro, char* frase){
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Árbol %s: El pájaro emigra.", frase);

	ptda_afirmar((arbol_borrar(arbol, pajaro) == EXITO), texto);
	ptda_subafirmar_fin(arbol_vacio(arbol), "El árbol quedó sin pajaros.");
}

/*23*/
int probar_borrar_un_pajaro(abb_t* arbol, pajaro_t** pajaros, int* borrados, int* cant_borrados, int* cant_valida, char* cant_txt, char* pajaro_sacar){
	int retorno;
	size_t cant_actual;
	char texto[MAX_TEXTO];
	pajaro_t** inorden = crear_vector_recorrido();
	if(!inorden)
		return ERROR;

	snprintf(texto, MAX_TEXTO, "Árbol con %s: Un pájaro %s emigra (ID %i).", cant_txt, pajaro_sacar, borrados[*cant_borrados]);
	retorno = arbol_borrar(arbol, pajaros[borrados[*cant_borrados]]);
	if(retorno == EXITO)
		(*cant_borrados)++;

	ptda_afirmar((retorno == EXITO), texto);
	cant_actual = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);
	snprintf(texto, MAX_TEXTO, "La cantidad de pájaros del árbol es %i.", *cant_valida);
	ptda_subafirmar(((retorno == EXITO) && (cant_actual == *cant_valida)), texto);
	ptda_subafirmar(((retorno == EXITO) && vectores_iguales_borrar(pajaros, (pajaro_t**)inorden, cant_actual, borrados, *cant_borrados)), "Los pájaros del árbol están en la rama que corresponde.");

	(*cant_valida)--;
	free(inorden);

	return retorno;
}

/*04*/
void pruebas_borrar_nieto_sin_hijos(int retorno, abb_t* arbol, pajaro_t** pajaros){
	nodo_abb_t* lider = lider_arbol(arbol);

	ptda_subafirmar_fin(((retorno == EXITO) && !pajaro_tiene_hijos(hijo_menor(lider)) && !pajaro_tiene_hijos(hijo_mayor(lider))), "El pájaro líder no tiene nietos.");
}

/*06*/
void pruebas_borrar_lider_dos_hijos(int retorno, abb_t* arbol, pajaro_t** pajaros, size_t pos){
	nodo_abb_t* lider = lider_arbol(arbol);
	
	ptda_subafirmar(((retorno == EXITO) && pajaro_correcto(arbol, lider, pajaros, pos)), "El hijo menor del exlíder es el nuevo pájaro lider.");
	ptda_subafirmar(((retorno == EXITO) && hijo_mayor(lider) && !hijo_menor(lider)), "El pájaro líder tiene un hijo mayor.");
	ptda_subafirmar_fin(((retorno == EXITO) && caracteristicas_validas(lider, pajaros, pos)), "Las características del pájaro líder son correctas.");
}

/*06*/
void pruebas_borrar_lider_un_hijo(int retorno, abb_t* arbol, pajaro_t** pajaros, size_t pos){
	nodo_abb_t* lider = lider_arbol(arbol);
	
	ptda_subafirmar(((retorno == EXITO) && pajaro_correcto(arbol, lider, pajaros, pos)), "El hijo mayor del exlíder es el nuevo pájaro lider.");
	ptda_subafirmar(((retorno == EXITO) && !pajaro_tiene_hijos(lider)), "El pájaro líder es el único pájaro del árbol.");
	ptda_subafirmar_fin(((retorno == EXITO) && caracteristicas_validas(lider, pajaros, pos)), "Las características del pájaro líder son correctas.");
}

/*14*/
void probar_borrar_todos(abb_t* arbol){
	int retorno;
	size_t cant_borrar;
	pajaro_t** inorden = crear_vector_recorrido();
	if(!inorden)
		return;

	cant_borrar = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);	
	retorno = sacar_pajaros(arbol, cant_borrar);
	ptda_afirmar((retorno == EXITO), "Árbol con muchos pájaros (con pájaros recién nacidos y pájaros gemelos): Todos los pájaros emigran.");
	ptda_subafirmar(((retorno == EXITO) && arbol_vacio(arbol)), "El árbol quedó sin pájaros.");
	ptda_subafirmar_fin((arbol && campos_validos(arbol, NULL, comparador_pajaros, destructor_pajaros)), "El árbol permanece con su estructura válidas.");

	free(inorden);
}

/*20*/
void probar_borrar_inexistente(abb_t* arbol, pajaro_t** pajaros, char* frase, size_t pos, int id){
	char texto[MAX_TEXTO];
	size_t cant_previa, cant_posterior;
	int retorno;
	pajaro_t** inorden = crear_vector_recorrido();
	if(!inorden)
		return;

	crear_pajaro(pajaros, pos, id);

	cant_previa = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);
	retorno = arbol_borrar(arbol, pajaros[pos]);
	cant_posterior = arbol_recorrido_inorden(arbol, (void**)inorden, MAX_CANTIDAD);

	snprintf(texto, MAX_TEXTO, "Árbol %s: El exlider no puede emigrar, que ya emigró del árbol (ID %i).", frase, id);
	ptda_afirmar((retorno == ERROR), texto);
	ptda_subafirmar_fin(((retorno == ERROR) && (cant_previa == cant_posterior)), "Ningún otro pájaro ha emigrado.");
	
	free(pajaros[pos]);
	free(inorden);
}

/*62*/
void probar_borrar_arbol(){
	int retorno;
	abb_t* arbol, *arbol_sin_destructor;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("Borrar - árbol");
	
	pajaros = crear_valores_insertar(6, 6);
	if(!pajaros)
		return;
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;


	ptda_afirmar(arbol_borrar(NULL, pajaros[0]) == ERROR, "Árbol sin plantar: Los pájaros no pueden emigrar.");

	ptda_afirmar(arbol_borrar(arbol, pajaros[0]) == ERROR, "Árbol plantado y sin pájaros: Los pájaros no pueden emigrar.");

	arbol_sin_destructor = crear_un_arbol(comparador_pajaros, NULL, pajaros);
	if(!arbol_sin_destructor)
		return;

	ptda_afirmar(arbol_borrar(arbol_sin_destructor, pajaros[0]) == ERROR, "Árbol plantado sin criterio para que los pájaros emigren, sin pájaros: Los pájaros no pueden emigrar.");

	colocar_un_pajaro(arbol_sin_destructor, pajaros[5]);
	probar_borrar_unico_pajaro(arbol_sin_destructor, pajaros[5], "plantado sin criterio para que los pájaros emigren, 1 pájaro");
	free(pajaros[5]);
	arbol_destruir(arbol_sin_destructor);

	colocar_un_pajaro(arbol, NULL);
	probar_borrar_unico_pajaro(arbol, NULL, "con 1 pájaro, recién nacido");

	colocar_un_pajaro(arbol, pajaros[4]);
	probar_borrar_unico_pajaro(arbol, pajaros[4], "con 1 pájaro");
	
	int insertados[] = {1, 0, 3, 2};
	mostrar_accion("Se colocan, en este orden, los pájaros cuyo ID es:", (void**)insertados, id_posiciones, 4);
	colocar_pajaros(arbol, pajaros, insertados, 4);

	mostrar_estado_arbol(arbol, arbol_recorrido_inorden);
	int borrados[] = {2, 1, 0, 3}, cant_borrados = 0, cant_valida = 3;
	retorno =  probar_borrar_un_pajaro(arbol, pajaros, borrados, &cant_borrados, &cant_valida, "4 pájaros", "que no tiene hijos");
	pruebas_borrar_nieto_sin_hijos(retorno, arbol, pajaros);

	retorno = probar_borrar_un_pajaro(arbol, pajaros, borrados, &cant_borrados, &cant_valida, "3 pájaros", "que tiene dos hijos");
	pruebas_borrar_lider_dos_hijos(retorno, arbol, pajaros, 0);

	probar_borrar_inexistente(arbol, pajaros, "con 2 pájaros", 4, 1);

	retorno = probar_borrar_un_pajaro(arbol, pajaros, borrados, &cant_borrados, &cant_valida, "2 pájaros", "que tiene un hijo");
	pruebas_borrar_lider_un_hijo(retorno, arbol, pajaros, 3);

	probar_borrar_unico_pajaro(arbol, pajaros[borrados[cant_borrados]], "con 1 pájaro");
	
	free(pajaros);
	
	pajaros = crear_valores_insertar(17, 15);
	if(!pajaros)
		return;

	int posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12, 8, -1};
	colocar_pajaros(arbol, pajaros, posiciones, 15);
	crear_pajaro(pajaros, 15, 8);
	colocar_un_pajaro(arbol, pajaros[15]);//coloco una copia del lider
	colocar_un_pajaro(arbol, NULL);//coloco un pájaro recién nacido

	mostrar_accion("Se colocan, en este orden, los pajaros cuyo ID es:", (void**)insertados, id_posiciones, 17);
	probar_borrar_todos(arbol);
	probar_borrar_inexistente(arbol, pajaros, "plantado y sin pájaros", 16, 14);

	arbol_destruir(arbol);
	free(pajaros);
}

/*53*/
void probar_buscar_arbol(){
	abb_t* arbol;
	void* rama_encontrada;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("Buscar - árbol");
	
	pajaros = crear_valores_insertar(3, 3);
	if(!pajaros)
		return;
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	ptda_afirmar(!arbol_buscar(NULL, pajaros[0]), "Árbol sin plantar: No se puede buscar pájaros.");

	ptda_afirmar(!arbol_buscar(arbol, pajaros[0]), "Árbol plantado y sin pájaros: No se puede buscar pájaros.");

	colocar_un_pajaro(arbol, pajaros[1]);
	colocar_un_pajaro(arbol, pajaros[0]);

	rama_encontrada = arbol_buscar(arbol, pajaros[1]);
	ptda_afirmar(rama_encontrada, "Árbol con 2 pájaros: Se puede buscar al pájaro lider.");
	ptda_subafirmar((rama_encontrada && (arbol_raiz(arbol) == ((pajaro_t*)rama_encontrada))), "El pájaro encontrado es el lider del árbol.");
	ptda_subafirmar((rama_encontrada && ((arbol->comparador(((pajaro_t*)rama_encontrada), pajaros[1])) == IGUALES)), "El pájaro encontrado es el buscado.");
	ptda_subafirmar_fin((rama_encontrada && caracteristicas_validas(lider_arbol(arbol), pajaros, 1)), "Las características del pájaro son correctas.");

	rama_encontrada = arbol_buscar(arbol, pajaros[0]);
	ptda_afirmar(rama_encontrada, "Árbol con 2 pájaros: Se puede buscar al pájaro de menor ID.");
	ptda_subafirmar((rama_encontrada && ((arbol->comparador(rama_encontrada, pajaros[0])) == IGUALES)), "El pájaro encontrado es el buscado.");
	ptda_subafirmar_fin(rama_encontrada && caracteristicas_validas(hijo_menor(lider_arbol(arbol)), pajaros, 0), "Las características del pájaro son correctas.");

	ptda_afirmar(!(arbol_buscar(arbol, pajaros[2])), "Árbol con 2 pájaros: No se puede buscar a otro pájaro.");
	free(pajaros[2]);

	sacar_pajaros(arbol, 2);
	free(pajaros);

	pajaros = crear_valores_insertar(16, 15);
	if(!pajaros)
		return;
	int posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12, 8};
	colocar_pajaros(arbol, pajaros, posiciones, 15);
	crear_pajaro(pajaros, 15, 8);
	colocar_un_pajaro(arbol, pajaros[15]);//coloco una copia del lider
	ptda_afirmar(((pajaro_t*)buscar_pajaros(arbol, pajaros, 16, posiciones)), "Árbol con un 16 pájaros: Puedo buscar a todos los pájaros.");
	free(pajaros);
	
	arbol_destruir(arbol);
}

/*41*/
void probar_raiz_arbol(){
	abb_t* arbol;
	pajaro_t* lider;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("Líder - árbol");

	pajaros = crear_valores_insertar(17, 15);
	if(!pajaros)
		return;

	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	ptda_afirmar(!arbol_raiz(NULL), "Árbol sin plantar: No se puede buscar al pájaro lider.");

	ptda_afirmar(!arbol_raiz(arbol), "Árbol plantado y sin pájaros: No se puede buscar al pájaro lider.");

	int posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12, 8, -1};
	colocar_pajaros(arbol, pajaros, posiciones, 15);
	crear_pajaro(pajaros, 15, 8);
	colocar_un_pajaro(arbol, pajaros[15]);//coloco una copia del lider
	colocar_un_pajaro(arbol, NULL);//coloco un pájaro recién nacido

	lider = arbol_raiz(arbol);
	ptda_afirmar(lider, "Árbol con muchos pájaros: Se puede buscar al pájaro lider.");
	ptda_subafirmar_fin((lider && ((arbol->comparador(lider, (lider_arbol(arbol)->elemento))) == IGUALES)), "El lider encontrado es el buscado.");

	sacar_pajaros(arbol, 16);

	lider = (pajaro_t*)arbol_raiz(arbol);
	ptda_afirmar(lider, "Árbol con 1 pájaro: Se puede buscar al pájaro lider.");
	ptda_subafirmar_fin((lider && ((arbol->comparador(lider, lider_arbol(arbol)->elemento)) == IGUALES)), "El lider encontrado es el buscado.");

	free(pajaros);
	
	arbol_destruir(arbol);
}

/*34*/
void probar_arbol_vacio(){
	abb_t* arbol;
	pajaro_t** pajaros;

	ptda_nuevo_subgrupo("¿Hay pájaros? - árbol");

	pajaros = crear_valores_insertar(17, 15);
	if(!pajaros)
		return;

	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	ptda_afirmar(arbol_vacio(NULL), "Árbol sin plantar: El árbol está sin pájaros.");

	ptda_afirmar(arbol_vacio(arbol), "Árbol plantado y sin pájaros: El árbol está sin pájaros.");

	int posiciones[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12, 8, -1};

	colocar_pajaros(arbol, pajaros, posiciones, 15);
	crear_pajaro(pajaros, 15, 8);
	colocar_un_pajaro(arbol, pajaros[15]);//coloco una copia del lider
	colocar_un_pajaro(arbol, NULL);//coloco un pájaro recién nacido

	ptda_afirmar(!arbol_vacio(arbol), "Árbol con muchos pájaros: El árbol no está sin pájaros.");

	sacar_pajaros(arbol, 16);

	ptda_afirmar(!arbol_vacio(arbol), "Árbol con 1 pájaro: El árbol no está sin pájaros.");

	free(pajaros);
	
	arbol_destruir(arbol);
}

/*63*/
void probar_recorrido_segun_orden(size_t (*arbol_recorrido)(abb_t*, void**, size_t), int* salida_esperada_insercion_aleatoria, int* salida_esperada_insercion_ordenada){
	size_t cantidad_actual;
	abb_t* arbol;
	pajaro_t** pajaros;

	pajaros = crear_valores_insertar(15, 15);
	if(!pajaros)
		return;

	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	pajaro_t** recorrido = crear_vector_recorrido();
	if(!recorrido)
		return;
	
	cantidad_actual = arbol_recorrido(NULL, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 0), "Árbol sin plantar: No se puede avistar nada.");
	ptda_subafirmar_fin(((cantidad_actual == 0) && vectores_iguales_insertar(pajaros, (pajaro_t**)recorrido, cantidad_actual)), "No hay pájaros a la vista.");

	cantidad_actual = arbol_recorrido(arbol, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 0), "Árbol plantado y sin pájaros: Se puede avistar que el árbol no tiene pájaros.");
	ptda_subafirmar_fin(((cantidad_actual == 0) && vectores_iguales_insertar(pajaros, (pajaro_t**)recorrido, cantidad_actual)), "No hay pájaros a la vista.");

	int posiciones_insercion_aleatoria[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};
	mostrar_accion("Se colocan, en este orden, los pajaros cuyo ID es:", (void**)posiciones_insercion_aleatoria, id_posiciones, 15);
	colocar_pajaros(arbol, pajaros, posiciones_insercion_aleatoria, 15);

	cantidad_actual = arbol_recorrido(arbol, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 15), "Árbol con 15 pájaros: Se puede avistar la cantidad de pájaros del árbol.");
	ptda_subafirmar_fin(((cantidad_actual == 15) && vectores_iguales_recorrido(pajaros, (pajaro_t**)recorrido, salida_esperada_insercion_aleatoria, cantidad_actual)), "Los pájaros avistados están en donde figura que deberían estar.");

	sacar_pajaros(arbol, 14);
	cantidad_actual = arbol_recorrido(arbol, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 1), "Árbol con 1 pájaro: Se puede avistar la cantidad de pájaros del árbol.");
	ptda_subafirmar_fin(((cantidad_actual == 1) && (recorrido[0] == arbol_raiz(arbol))), "Los pájaros avistados están en donde figura que deberían estar.");

	sacar_pajaros(arbol, 1);
	free(pajaros);

	pajaros = crear_valores_insertar(15, 15);
	if(!pajaros)
		return;

	int posiciones_insercion_ordenada[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	mostrar_accion("Se colocan, en este orden, los pajaros cuyo ID es:", (void**)posiciones_insercion_ordenada, id_posiciones, 15);
	colocar_pajaros(arbol, pajaros, posiciones_insercion_ordenada, 15);

	cantidad_actual = arbol_recorrido(arbol, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 15), "Árbol con 15 pájaros: Se puede avistar la cantidad de pájaros del árbol.");
	ptda_subafirmar_fin(((cantidad_actual == 15) && vectores_iguales_recorrido(pajaros, (pajaro_t**)recorrido, salida_esperada_insercion_ordenada, cantidad_actual)), "Los pájaros avistados están en donde figura que deberían estar.");

	sacar_pajaros(arbol, 14);
	cantidad_actual = arbol_recorrido(arbol, (void**)recorrido, MAX_CANTIDAD);
	ptda_afirmar((cantidad_actual == 1), "Árbol con 1 pájaro: Se puede avistar la cantidad de pájaros del árbol.");
	ptda_subafirmar_fin(((cantidad_actual == 1) && (recorrido[0] == arbol_raiz(arbol))), "Los pájaros avistados están en donde figura que deberían estar.");

	free(recorrido);
	free(pajaros);
	arbol_destruir(arbol);
}

/*25*/
void probar_arbol(){
	
	ptda_nuevo_grupo("Operaciones básicas");
	probar_crear_arbol();
	probar_insertar_arbol();
	probar_borrar_arbol();
	probar_buscar_arbol();
	probar_raiz_arbol();

	ptda_nuevo_grupo("Información");
	probar_arbol_vacio();

	ptda_nuevo_grupo("Recorridos");

	int salida_esperada_menor_a_mayor[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int salida_esperada_preorden_insercion_aleatoria[] = {8, 3, 1, 0, 2, 6, 4, 5, 7, 10, 9, 14, 13, 11, 12};
	int salida_esperada_postorden_insercion_aleatoria[] = {0, 2, 1, 5, 4, 7, 6, 3, 9, 12, 11, 13, 14, 10, 8};
	int salida_esperada_postorden_insercion_ordenada[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	ptda_nuevo_subgrupo("Recorrido Inorden - árbol");
	probar_recorrido_segun_orden(arbol_recorrido_inorden, salida_esperada_menor_a_mayor, salida_esperada_menor_a_mayor);
	ptda_nuevo_subgrupo("Recorrido Preorden - árbol");
	probar_recorrido_segun_orden(arbol_recorrido_preorden, salida_esperada_preorden_insercion_aleatoria, salida_esperada_menor_a_mayor);
	ptda_nuevo_subgrupo("Recorrido Postorden - árbol");
	probar_recorrido_segun_orden(arbol_recorrido_postorden, salida_esperada_postorden_insercion_aleatoria, salida_esperada_postorden_insercion_ordenada);
}

/*26*/
void probar_acciones_basicas_iterador_interno(int numero_recorrido, char* frase){
	int contador;
	size_t elementos_recorridos;
	abb_t* arbol;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Acciones Básicas - Orden: %s - Iterador Interno", frase);
	ptda_nuevo_subgrupo(texto);

	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, NULL);
	if(!arbol)
		return;

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(NULL, numero_recorrido, cantidad_elementos, &contador);
	ptda_afirmar(((elementos_recorridos == 0) && (contador == 0)), "Árbol sin plantar: No se puede avistar pájaros.");

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, NULL, (void*)&contador);
	ptda_afirmar(((elementos_recorridos == 0) && (contador == 0)), "Arbol plantado, sin criterio para evaluar: No se pueden avistar pájaros.");

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, cantidad_elementos, (void*)&contador);
	ptda_afirmar(((elementos_recorridos == 0) && (contador == 0)), "Árbol sin pájaros: Se puede avistar correctamente que no hay pájaros.");
		
	arbol_destruir(arbol);
}

/*36*/
void probar_recorrer_todo_iterador_interno(int numero_recorrido, char* frase){
	int contador;
	size_t elementos_recorridos = 0;
	abb_t* arbol;
	pajaro_t** pajaros;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Recorrer Todo - Orden: %s - Iterador Interno", frase);
	ptda_nuevo_subgrupo(texto);

	pajaros = crear_valores_insertar(16, 16);
	if(!pajaros)
		return;
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	colocar_un_pajaro(arbol, pajaros[15]);

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, cantidad_elementos, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 1), "Árbol con 1 pájaro: Se puede avistar correctamente al pájaro.");
	ptda_subafirmar_fin(((elementos_recorridos == 1) && (contador == 1)), "Se evaluó a todos los pájaros avistados.");

	arbol_borrar(arbol, pajaros[15]);

	int posiciones_insercion_aleatoria[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};

	colocar_pajaros(arbol, pajaros, posiciones_insercion_aleatoria, 15);
	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, cantidad_elementos, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 15), "Árbol con muchos pájaros: Se puede avistar correctamente a los pájaros.");
	ptda_subafirmar_fin(((elementos_recorridos == 15) && (contador == 15)), "Se evaluó a todos los pájaros avistados.");

	arbol_destruir(arbol);
	free(pajaros);
}

/*36*/
void probar_obtener_digitos_iterador_interno(int numero_recorrido, char* frase){
	int contador;
	size_t elementos_recorridos = 0;
	abb_t* arbol;
	pajaro_t** pajaros;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Cantidad Dígitos Total - Orden: %s - Iterador Interno", frase);
	ptda_nuevo_subgrupo(texto);
	
	pajaros = crear_valores_insertar(16, 16);
	if(!pajaros)
		return;
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	colocar_un_pajaro(arbol, pajaros[15]);

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, cantidad_digitos_total, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 1), "Árbol con 1 pájaro: Se pueden avistar correctamente al pájaro.");
	ptda_subafirmar_fin(((elementos_recorridos == 1) && (contador == cant_digitos(pajaros[15]->id))), "Se evaluó a todos los pájaros avistados, y se obtuvo el resultado esperado.");

	arbol_borrar(arbol, pajaros[15]);

	int posiciones_insercion_aleatoria[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};
	colocar_pajaros(arbol, pajaros, posiciones_insercion_aleatoria, 15);

	contador = 0;
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, cantidad_digitos_total, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 15), "Árbol con muchos pájaros: Se puede avistar correctamente a los pájaros.");
	ptda_subafirmar_fin(((elementos_recorridos == 15) && (contador == cant_digitos_con_anteriores(14))), "Se evaluó a todos los pájaros avistados, y se obtuvo el resultado esperado.");

	arbol_destruir(arbol);
	free(pajaros);
}

/*38*/
void probar_obtener_ids_impares_12_primeras_posiciones(int numero_recorrido, char* frase){
	contador_t contador;
	size_t elementos_recorridos = 0;
	abb_t* arbol;
	pajaro_t** pajaros;
	char texto[MAX_TEXTO];

	snprintf(texto, MAX_TEXTO, "Cantidad IDs Impares de los Primeros 12 Pájaros - Orden: %s - Iterador Interno", frase);
	ptda_nuevo_subgrupo(texto);

	pajaros = crear_valores_insertar(16, 16);
	if(!pajaros)
		return;
	arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, pajaros);
	if(!arbol)
		return;

	colocar_un_pajaro(arbol, pajaros[15]);

	reiniciar_contador_iterador(&contador);	
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, ids_impares_12_primeras_posiciones, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 1), "Árbol con 1 pájaro: Se pueden avistar correctamente al pájaro.");
	ptda_subafirmar_fin(((elementos_recorridos == 1) && (contador.totales == 1) && (contador.ids_impares == 1)), "Se obtuvo la información buscada.");

	arbol_borrar(arbol, pajaros[15]);

	int posiciones_insercion_aleatoria[] = {8, 3, 10, 1, 6, 9, 14, 0, 2, 4, 7, 13, 5, 11, 12};
	colocar_pajaros(arbol, pajaros, posiciones_insercion_aleatoria, 15);

	reiniciar_contador_iterador(&contador);
	elementos_recorridos = abb_con_cada_elemento(arbol, numero_recorrido, ids_impares_12_primeras_posiciones, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 12), "Árbol con muchos pájaros: Se puede avistar correctamente a los pájaros.");
	ptda_subafirmar_fin(((elementos_recorridos == 12) && (contador.totales == 12) && (contador.ids_impares == ids_impares_segun_recorrido(numero_recorrido))), "Se evaluó solo a los primeros 12 pájaros, y se obtuvo la información buscada.");

	arbol_destruir(arbol);
	free(pajaros);
}

/*06*/
void probar_iterador_interno_segun_recorrido(int numero_recorrido, char* frase){

	probar_acciones_basicas_iterador_interno(numero_recorrido, frase);
	probar_recorrer_todo_iterador_interno(numero_recorrido, frase);
	probar_obtener_digitos_iterador_interno(numero_recorrido, frase);
	probar_obtener_ids_impares_12_primeras_posiciones(numero_recorrido, frase);
}

/*17*/
void probar_iterador_interno(){

	abb_t* arbol = crear_un_arbol(comparador_pajaros, destructor_pajaros, NULL);
	if(!arbol)
		return;

	int contador = 0;
	size_t elementos_recorridos = abb_con_cada_elemento(arbol, RECORRIDO_INVALIDO, cantidad_elementos, (void*)&contador);
	ptda_afirmar((elementos_recorridos == 0) && (contador == 0), "Árbol plantado, camino inválido: No se pueden avistar pájaros.");
	arbol_destruir(arbol);

	ptda_nuevo_grupo("Orden: Inorden - Iterador Interno ");
	probar_iterador_interno_segun_recorrido(ABB_RECORRER_INORDEN, "Inorden");
	ptda_nuevo_grupo("Orden: Preorden - Iterador Interno ");
	probar_iterador_interno_segun_recorrido(ABB_RECORRER_PREORDEN, "Preorden");
	ptda_nuevo_grupo("Orden: Postorden - Iterador Interno ");
	probar_iterador_interno_segun_recorrido(ABB_RECORRER_POSTORDEN, "Postorden");
}

/*08*/
int main(){
	
	ptda_nueva_categoria("Árbol");
	probar_arbol();	
	ptda_nueva_categoria("Iterador Interno");
	probar_iterador_interno();

	ptda_mostrar_reporte();
}