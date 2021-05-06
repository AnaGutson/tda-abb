#ifndef __PTDA_H_
#define __PTDA_H_
	
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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

#define DECENA	10

#define TILDE	"✔"
#define CRUZ	"✘"

#define LARGO_INICIAL	29
#define LARGO_FINAL		20

int __ptda_cantidad_de_pruebas_corridas = 0;
int __ptda_cantidad_de_pruebas_fallidas = 0;
const char* __ptda_prueba_actual = NULL;
const char* __ptda_texto_1 = NULL;
const char* __ptda_texto_2 = NULL;
const char* __ptda_texto_3 = NULL;
const char* __ptda_texto_4 = NULL;
const int __ptda_numero = 0;

void __ptda_atajarse(void (*handler)(int)){

	signal(SIGABRT, handler);
	signal(SIGSEGV, handler);
	signal(SIGBUS, handler);
	signal(SIGILL, handler);
	signal(SIGFPE, handler);
}

void __ptda_morir(int signum){

	if(__ptda_prueba_actual)
		printf(ROJO_OSCURO "\n\nERROR MIENTRAS SE EJECUTABA LA PRUEBA: " AMARILLO "'%s'\n\n" BLANCO, __ptda_prueba_actual);
	else
		printf(ROJO_OSCURO "\n\nFINALIZACION ANORMAL DE LAS PRUEBAS\n\n"BLANCO);

	fflush(stdout);
	__ptda_atajarse(SIG_DFL);
}

#define ptda_afirmar(afirmacion, descripcion) do{	\
													\
	__ptda_prueba_actual = descripcion;				\
	__ptda_atajarse(__ptda_morir);					\
	if(afirmacion)									\
 		printf("\n" VERDE_OSCURO " " TILDE " ");	\
	else{											\
													\
  		__ptda_cantidad_de_pruebas_fallidas++;		\
  		printf("\n" ROJO_OSCURO " " CRUZ " ");		\
	}												\
	printf(BLANCO "%s\n", __ptda_prueba_actual);	\
	fflush(stdout);									\
	__ptda_prueba_actual = NULL;					\
	__ptda_cantidad_de_pruebas_corridas++;			\
} while(0);

#define ptda_subafirmar(afirmacion, descripcion) do{	\
														\
	__ptda_prueba_actual = descripcion;					\
	__ptda_atajarse(__ptda_morir);						\
	if(afirmacion)										\
  		printf("   ╠» " VERDE_OSCURO TILDE " ");		\
	else{												\
  														\
 		__ptda_cantidad_de_pruebas_fallidas++;			\
  		printf("   ╠» " ROJO_OSCURO CRUZ " ");			\
	}													\
	printf(BLANCO "%s\n", __ptda_prueba_actual);		\
	fflush(stdout);										\
	__ptda_prueba_actual = NULL;						\
	__ptda_cantidad_de_pruebas_corridas++;				\
} while(0);

#define ptda_subafirmar_fin(afirmacion, descripcion) do{	\
															\
	__ptda_prueba_actual = descripcion;						\
	__ptda_atajarse(__ptda_morir);							\
	if(afirmacion)											\
  		printf("   ╚» "VERDE_OSCURO TILDE " ");				\
	else{													\
  															\
		__ptda_cantidad_de_pruebas_fallidas++;				\
  		printf("   ╚» " ROJO_OSCURO CRUZ " ");				\
	}														\
	printf(BLANCO "%s\n", __ptda_prueba_actual);			\
	fflush(stdout);											\
	__ptda_prueba_actual = NULL;							\
	__ptda_cantidad_de_pruebas_corridas++;					\
} while(0);

void ptda_nueva_categoria(const char* descripcion){

	printf(AMARILLO"\n\n\t\t\t\t\t\t\t%s\n\t\t\t\t\t\t\t", descripcion);
	while(*(descripcion++))
		printf("─");
	printf(BLANCO);
}

void ptda_nuevo_grupo(const char* descripcion){

	printf(VERDE_OSCURO "\n\n%s\n", descripcion);
	while(*(descripcion++))
		printf("═══");
	printf(BLANCO);
}

void ptda_nuevo_subgrupo(const char* descripcion){

	printf(CELESTE "\n\n%s\n", descripcion);
	while(*(descripcion++))
		printf("─");
	printf(BLANCO "\n");
}

/*Pre-condiciones: 
	"valor" positivo.
Post-condiciones: 
	la función devolverá la cantidad de digitos del valor.*/
int cant_digitos(int valor){
	int digitos = 0;

	do{

		digitos++;
		valor/=DECENA;
	} while(valor != 0);

	return digitos;
}

/*Pre-condiciones: 
	"cant_espacios" positivo
Post-condiciones: 
	la función mostrará "cant_espacios" espacios*/
void mostrar_caracter(int cant_veces, char* caracter){

	for(int i = 0; i < cant_veces; i++)
		printf("%s", caracter);
}

int ptda_mostrar_reporte() {
	int largo_total;

	largo_total = cant_digitos(__ptda_cantidad_de_pruebas_corridas) + cant_digitos(__ptda_cantidad_de_pruebas_fallidas) + LARGO_INICIAL + LARGO_FINAL;

	printf(AMARILLO"\n\t\t\t\t╔");
	mostrar_caracter(largo_total, "═");
	printf("╗\n");

	printf("\t\t\t\t║ "BLANCO"%i pruebas corridas, %i errores:",
		__ptda_cantidad_de_pruebas_corridas,
		__ptda_cantidad_de_pruebas_fallidas);
	if(__ptda_cantidad_de_pruebas_fallidas == 0)
		printf(VERDE_OSCURO"    Lo lograste.    "AMARILLO"║\n");
	else
		printf(ROJO_CLARO"   No lo lograste.  "AMARILLO"║\n");

	printf("\t\t\t\t╚");
	mostrar_caracter(largo_total, "═");
	printf("╝\n\n"FIN);

	return __ptda_cantidad_de_pruebas_fallidas;
}

#endif // __PTDA_H_
