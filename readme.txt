Buen día Lucas, ¿cómo estás? Se procederá a aclarar algunas cuestiones sobre el trabajo, ya que capaz podrían generar duda - y además es obligatorio hacerlo.

────────────────────────────────────────────────────────────────────Convenciones────────────────────────────────────────────────────────────────────

● Las convenciones que se utilizan en el trabajo son con base en qué me parece más legible, siempre respetando el uso del ​snake_case​.

● Con respecto al código, se separa en tres partes:

...{
    declaraciones​;

    código​;

    return​;
}

En caso de no haber una de las partes, se hace lo siguiente:

● Si no hay declaraciones:
...{
    código​;

    return​;
}

● Si no hay return:
...{
    declaraciones​;

    código​;
}

● Si solo hay código:
...{

    código​;
}

● Si solo hay return:
...{

    return;
}

La razón por la que se deja un enter arriba de "código" pero no debajo es debido a que cuando se minimiza el bloque, no resulta agradable que quede una línea en blanco, ya que si hubiera un enter abajo quedaría como:
...{​░░

}

Y es preferible que quede sin el espacio:
...{​░░
}

-esto es más entendible con colores y dibujos pero no se puede, para más información consultar por privado-

Añado: Dentro de bloques de código se suele seguir la misma regla, es decir, dentro de funciones de control por ejemplo, a excepción de un caso:
En funciones recursivas, que se autoinvocan, suelo proceder de esta manera:

if(condicion){

    declaraciones;
    codigo;
    return;
}

En vez de hacer:

if(condicion){
    declaraciones;

    codigo;

    return;
}


● Y dentro de funciones, si la función recibe muchos parámetros, como se trata de respetar el uso de 80 caracteres máximo por línea, se procede de la siguiente manera:

void* funcion(int ..., char ..., double ..., size_t ..., const int ..., char* ...,
    void (*funcion)(int, int)){

    declaraciones​;

    código​;

    return​;
}

Es decir, se deja una línea de separación para que se entienda dónde comienzan las declaraciones.

● Se prefiere escribir sin corchetes si es posible, como

for(...)
    ...;

o

if(...)
    ...;

Tratando de respetar, siempre que sea posible, una acción por línea.

● Para escribir funciones de control, se escribe la función y al lado los paréntesis, sin dejar espacio, por ejemplo:

while(...){
    ...;
}

● Para escribir un booleano (ya sea función o variable) dentro de una condición, se prefiere sin el "==", sino que con el mero nombre alcanza, y en caso de querer negarlo, un "!" antes del mismo. Por ejemplo:

while(es_rojo(tateti_suerte_pa_mi) || !termino){
    ...;
}

● Para escribir varias condiciones, se trata de usar la siguiente convención:
En caso de no haber una de las partes, se hace lo siguiente:

● En caso de haber varias operaciones de comparación:
if((condicion_1 > 0) && (condicion_2 > 0))
 ➜ se respetan las buenas prácticas de cada comparación -acción- en un paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de haber funciones booleanas y operaciones de comparación:
if(es_valido(condicion_1) && (condicion_2 > 0))
 ➜ las funciones no se separan entre paréntesis, se respetan las buenas prácticas de cada comparación -acción- en un paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de haber funciones booleanas solamente:
if(es_valido(condicion_1) && es_valido(condicion_1))
 ➜ las funciones no se separan entre paréntesis, además no se dejan espacios entre el primer y último paréntesis.

● En caso de que haya punteros con campos:
if(((condicion_1->tata) > 0) && ...)
 ➜ toda la variable se coloca entre paréntesis, para evitar confusiones.

● Para declarar punteros, se prefiere hacerlo así
nodo_t* nodo;

En vez de:
nodo_t *nodo;
 ➜ el asterisco al lado del tipo de dato.

De la misma manera se procede en la declaración de funciones, al emplear el uso del "*" para indicar que el valor se actualizará.

● Se prefiere escribir de precondiciones razones por las que no se podría cumplir el cometido de una función. Por ejemplo, si la intención es hacer algo con un árbol, y no hay árbol, no se podrá hacer.
Entonces, el programa no se rompe si se manda NULL como árbol, pero en las pre condiciones se prefiere aclarar que no hay que mandar arbol = NULL.

● Se prefiere hacer un return en medio de una función solo si es debido a que no se cumplieron las pre condiciones. También, si surge un problema al pedir memoria dinámica. El último posible caso donde se realiza un return en medio de la función es en las funciones recursivas. Sino, SOLO se realiza al final de todo, nunca se hacen varios return: gusto personal, y no cuesta nada hacerlo como gusta.

● Para el TDA se trató de reutilizar el código de otras funciones anteriores, menos las del iterador: era más gustoso recorrer las funciones a mano que con el iterador interno.

● Los colores para mostrar las pruebas fueron elegidos con intención, y también con intención se decidió solo colorear el texto, no resaltarlo. Esto último no agrada visualmente.

● Se exhorta usar el programa en pantalla completa, sino no se podrá asegurar la correcta visualización del mismo.

● En "abb_pruebas.c" y "arbol.c" se prefiere agrupar las funciones por lo que devuelven, y de qué tratan.

● Las constantes se tienen alineadas en grupos, así resulta más fácil organizarse. Es decir, los valores de cada una se tienen a la misma altura solo si son del mismo grupo. Por ejemplo:

#define LEER                         "r"
#define ESCRIBIR                     "w"

#define EXITO        0
#define ERROR        -1


───────────────────────────────────────────────────────────────────────Ejecución───────────────────────────────────────────────────────────────────────


Objetivo:
    
    El objetivo de esta entrega es realizar un TDA de un árbol binario de búsqueda (para más información leer "¿Qué es un Árbol Binario de Búsqueda?" y realizar las pruebas necesarias para saber que funciona en todos los casos.

Descripción breve del funcionamiento de mi programa y cómo compilarlo:

    Para ver el funcionamiento de estas pruebas sobre el TDA hay que compilar todos los .c de la carpeta entregada (menos el abb_minipruebas.c) y ejecutar lo compilado.

    La línea de compilación recomendada es: gcc *.c -o ABB -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

    Si dentro de la carpeta hay algún .c con un main (además de pruebas.c) se debe hacer: gcc abb_pruebas.c abb.c -o ABB -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

    Es decir, se quieren compilar todos los .c (o los que se indiquen) con todos los warnings posibles, leyendo estos como error, y mostrando todas las conversiones que pueden generar cambios en el valor de una variable, y que el ejecutable se llame "ABB".

    Para usar el TDA, basta con hacer dentro de un .c un "#include "abb.h"" y ya se pueden usar las funciones.

    Para ver el uso de memoria, correr con valgrind. Se recomienda correr con: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./ABB

    Antes de correr con valgrind, recordar que hay que tener el ejecutable creado (en este caso "ABB").
    
    Sino, ejecutar normal: "./ABB".

    -En este ejemplo se llamó "ABB" al ejecutable: es irrelevante el nombre, se puede usar otro si uno lo prefiere, pero si se decide cambiarlo, recordar cambiarlo al compilar y al ejecutar (usar el mismo).-


───────────────────────────────────────────────────────────────Funciones del TDA───────────────────────────────────────────────────────────────


Aclaración: El trabajo entero se realizó tratando de practicar las habilidades con punteros. Por más que no sea tan cómodo, se trató de usar punteros a funciones todas las veces posibles en el que su uso no sea engorroso.

A continuación explicaré las funciones que contiene el TDA y el por qué se realizaron así:

    ●    abb_t* arbol_crear();

Lo que se hace es reservar memoria en el heap para un árbol. Se hace en el heap porque así se puede tener la cantidad de nodos que se quiera sin preocuparse por el espacio. Si se obtiene la memoria para el árbol, se inicializa: se podría hacer creandolo directamente inicializado, pero se prefiere hacerlo a mano para tenerlo a la vista. Se devuelve el árbol: si no se pudo reservar memoria para el mismo, se devuelve NULL.
Su complejidad es O(1).

    ●    int arbol_insertar(abb_t* arbol, void* elemento);

Si no hay árbol (no se leyeron las pre condiciones), se devuelve ERROR. Sino, se trata de reservar memoria dinámica para el nuevo nodo a insertar. Si no se logra hacerlo, se devuelve ERROR.
En caso de poder reservar memoria dinámica, si el árbol está vacío, se inserta un nodo al comienzo de la mismo, en arbol->nodo_raiz. Sino, en donde corresponda según lo que indique arbol->comparador.
Se retorna EXITO.
Su complejidad en el caso ideal es O(log(n)), en el peor caso es O(n).

    ●    int arbol_borrar(abb_t* arbol, void* elemento);

Si no hay árbol o si hay pero está vacío (no se leyeron las pre condiciones), se devuelve ERROR. Sino, se busca en el árbol, con arbol->comparador, el nodo que contenga al mismo elemento que el recibido por parámetro, procediendo a borrar de la siguiente manera:
 - Si "nodo->derecha" y "nodo->izquierda" (los hijos del nodo) son nulos, se libera la memoria para el nodo, haciendo antes que si algún nodo apuntaba al que se va a liberar, este ahora apunte a NULL.
 - Si "nodo->derecha" o "nodo->izquierda" no son nulos, se libera la memoria para el nodo, haciendo antes que si algún nodo apuntaba al que se va a liberar, este ahora apunte al hijo.
 - Si "nodo->derecha" y "nodo->izquierda" no son nulos, se reemplaza el nodo a liberar con su predecesor inorden, dejando en el lugar del predecesor inorden a su hijo (si es que tiene). Luego, se libera la memoria del nodo a liberar.
Se retorna EXITO o ERROR, dependiendo de si se encontró el elemento a borrar.
Su complejidad en el caso ideal es O(log(n)), en el peor caso es O(n).

    ●    void* arbol_buscar(abb_t* arbol, void* elemento);

Si no hay arbol o si hay pero está vacío (no se leyeron las pre condiciones), se devuelve NULL. Sino, se recorre el árbol hasta el elemento pedido (mediante arbol->comparador) y se devuelve el elemento.
Si no se encontró el elemento, devuelve NULL.
Su complejidad en el caso ideal es O(log(n)), en el peor caso es O(n).

    ●    void* arbol_raiz(abb_t* arbol);

Si no hay árbol o si hay pero está vacío (no se leyeron las pre condiciones), se devuelve NULL. Sino, se devuelve "arbol->nodo_raiz".
Su complejidad es O(1).

    ●    bool arbol_vacio(abb_t* arbol);

Si no hay arbol o si hay pero no tiene raíz, se devuelve true. Sino, se devuelve false.
Su complejidad es O(1).

    ●    size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t max);

Si no hay arbol, si no hay array o si max es 0, se retorna 0. Sino, se recorre el árbol en el orden inorden, comenzando por arbol->nodo_raiz: por cada nodo, se atraviesa el subárbol izquierdo, luego se rellena el array con dicho nodo, y por último se atraviesa el subárbol derecho.   
La operación se detiene si en algún momento se llega hasta la última posición del vector (posición es max-1).
Se devuelve la cantidad de elementos en el array (máximo es max).
Su complejidad es O(n).

    ●    size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t max);

Si no hay arbol, si no hay array o si max es 0, se retorna 0. Sino, se recorre el árbol en el orden preorden, comenzando por arbol->nodo_raiz: por cada nodo, se rellena el array con dicho nodo, se atraviesa el subárbol izquierdo, y por último se atraviesa el subárbol derecho.
La operación se detiene si en algún momento se llega hasta la última posición del vector (posición es max-1).
Se devuelve la cantidad de elementos en el array (máximo es max).
Su complejidad es O(n).

    ●    size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t max);

Si no hay árbol, si no hay array o si max es 0, se retorna 0. Sino, se recorre el árbol en el orden postorden, comenzando por arbol->nodo_raiz: por cada nodo, se atraviesa el subárbol izquierdo, luego se atraviesa el subárbol derecho y por último, se rellena el array con dicho nodo.
La operación se detiene si en algún momento se llega hasta la última posición del vector (posición es max-1).
Se devuelve la cantidad de elementos en el array (máximo es max).
Su complejidad es O(n).

    ●    void arbol_destruir(abb_t* arbol);

Si no hay árbol (no se leyeron las pre condiciones), se termina la función. Si el árbol tiene al menos un elemento, se los libera en orden postorden: primero se atraviesa el subárbol izquierdo, luego el derecho y por último se libera el nodo: si el árbol posee un destructor, se libera el elemento que el nodo posea (Para más información ir a la sección "¿Por qué el árbol se crea con un destructor?"). Por último, siempre se libera la memoria reservada para el árbol.
Su complejidad es O(n).

    ●    size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);

Si no hay función, no existe el árbol, si existe pero está vacío, o si el recorrido recibido no es válido,(no se leyeron las precondiciones), se termina la función. Sino se invoca a una función recursiva para recorrer el árbol en el orden indicado (según "recorrido"), hasta que se recorra todos los elementos del árbol o hasta que la función recibida por parámetro devuelva true.
Se retorna la cantidad de elementos recorridos.
Su complejidad es O(n) en el peor caso.


─────────────────────────────────────────────────Analogía de las pruebas del TDA─────────────────────────────────────────────────


En las pruebas del TDA, para hacerlas más interesantes (y porque se obtuvo el permiso del corrector), se realizó una analogía con pajaritos: a continuación se procederá a explicar qué significa cada cosa.
En términos generales, el ambiente es un campo, donde hay un lugar para un árbol: el árbol puede estar plantado o no. Sobre el árbol pueden posarse pajaritos de diferentes IDs, cada uno con un id único. Cada pájaro tiene dos parentesco, el pájaro a su derecha, y el que está a su izquierda: les decimos hijos mayor y menor respectivamente, ya que el que esté a su derecha tendrá un id mayor, y el de su izquierda, uno menor.
A los pájaros se los observa, en cada pájaro tienen un criterio para emigrar (pueden no tenerlo) y tiene un criterio para posarse sobre el mismo. Además, se los revisa, cuenta y anota en una lista en cierto orden.

Las analogías utilizadas son:
Árbol NULL: Árbol sin plantar.
Comparador: Criterio para comparar pájaros.
Destructor: Criterio para que los pájaros emigren.
Campos del árbol: estructura.
arbol_crear(): Plantar un árbol.
arbol_insertar(): Colocar un pájaro en el árbol.
arbol->nodo_raiz: Líder del árbol.
nodo: rama.
nodo->elemento: pájaro.
Dos elementos iguales: gemelos.
Elemento NULL: Pájaro recién nacido (todavía no le asignaron id).
arbol_borrar(): Dejar que un pájaro emigre.
arbol_recorrido_...(): Se avista a los pájaros y se checkea que estén donde deberían estar, siguiendo el criterio indicado (inorden, preorden o postorden).
abb_con_cada_elemento(): Se evalúa a la cantidad de pájaros indicados hasta que el criterio para evaluar indique que hay que detenerse.

─────────────────────────────────────────────────────────────────Pruebas del TDA─────────────────────────────────────────────────────────────────

En este trabajo se entregan 177 pruebas.

Dentro de las pruebas, se valida que cada función del TDA funcione tal como corresponde: para esto, se ha decidido asumir que todas las funciones del TDA andan menos la que se está probando (previamente preguntado en clase si se podía proceder así).

Las pruebas están divididas (visualmente) en "categoría", "grupo" y "subgrupo": la categoría es el tipo de TDA a probar, el grupo es de qué van a ser las pruebas (información del TDA o operaciones en el mismo), y el subgrupo es sobre qué función del TDA se está probando.

Las pruebas principales empiezan con la situación actual, seguida de "Se puede" o "No se puede": es por gusto personal.

Para las pruebas relacionadas con una prueba anterior, se decidió ponerlo como "subprueba".

Para las pruebas que devuelven la misma información, se decidió poner el mismo texto.
Como:
"Árbol con ... pájaros: Se puede colocar un pájaro (ID ...)."
"Las características del árbol son correctas"
"La cantidad de pájaros es ..."
"El pájaro está en la rama donde fue colocado".

Es posible que dentro de cada prueba capaz se vuelva a validar lo mismo que lo anterior y algo más.

Al probar cada función se crea una estructura de tipo abb_t* y se destruye al final de la prueba.



──────────────────────────────────────────────────────────────────────────TEORÍA──────────────────────────────────────────────────────────────────────────



──────────────────────────────────────────────────────────────────¿Qué es un TDA?


TDA hace referencia a Tipo de Dato Abstracto. Un Tipo de Dato Abstracto en programación se le considera al modelo que define valores y operaciones que se pueden realizar sobre él. Se crea una biblioteca con una o varias estructuras relacionadas a este tipo de dato, buscando que quien lo utilice no necesite conocer internamente cómo funciona: necesita saber qué hace, no cómo se hace. A este concepto se lo conoce como "caja blanca".

Se le llama abstracto ya que se busca concentrarse solo en lo que se necesita e importa a la hora de implementarlo.

El objetivo de usar un TDA es poder proveer de mayor flexibilización a la hora de programar: si una parte cambia, las demás no se ven afectadas. Esto nos lo brinda la abstracción.

Además, algo muy importante, al menos para mi, es que el usuario al no tener acceso al código, no puede romperlo, sabemos que la parte interna del mismo estará bien en todo momento, los casos bordes solo pueden ser generados por los parámetros recibidos en cada función.

En esta entrega, están "abb.c" junto a "abb.h", los cuales nos brindan las funciones necesarias para poder usar un árbol binario de búsqueda. Lo ideal es que el usuario reciba el .h y un .o para utilizarlo, sin nada más.

Árbol Binario y Árbol Binario de Búsqueda son tipos de TDA.


───────────────────────────────────────────────────────¿Qué es un Árbol Binario?


Un árbol binario (AB) es un tipo de dato abstracto, cuya idea es la siguiente: dentro de la misma, hay nodos, cada uno con la siguiente información: su nodo izquierdo y su nodo derecho. Solo está relacionado con dos nodos (por eso "binario"). Justamente, de esta forma las búsquedas ya no son lineales y se genera una menor complejidad del código.

Cada nodo del árbol, además es la raíz de un árbol binario.

Cuando un nodo no tiene relación con otros subnodos, se lo denomina "nodo hoja".

El árbol binario puede estar o no equilibrado: en el peor de los casos, actúa como una lista enlazada.

Mientras que un árbol tiene bastantes desventajas, entre ellas que no podemos buscar fácilmente información en él: pues no está ordenado, también posee sus ventajas, y más al compararlo con una lista: recorrerlo es mucho menos complejo.

Además, otra desventaja de este tipo de dato es que se trabaja con punteros y memoria dinámica, lo cual incrementa la dificultad de programarlos.

Las operaciones de un árbol binario son:
● Creación.
● Inserción (en cualquier lugar).
● Eliminación (en cualquier lugar).
● Búsqueda.
● Recorrido.
● Está vacío.
● Destrucción.

Una explicación de cómo realizar cualquiera de estas operaciones se encuentra al inicio de este .txt

Un ejemplo sería:
                    
				  ________90__________
			_____0_____			_____91_____    
			1			6__		9		  __0__
							2			90		18
                    
Este concepto se extrapola a uno nuevo que es el recreado en este trabajo: un árbol binario de búsqueda.


───────────────────────────────────────────¿Qué es un Árbol Binario de Búsqueda?


Un árbol binario de búsqueda (ABB) es un tipo de Árbol Binario (AB). Su especificidad radica en que está ordenado de cierta manera, al contrario de un simple árbol binario. La convención es insertar nodos en el árbol teniendo el siguiente criterio:
- los elementos mayores, a la derecha.
- los elementos menores, a la izquierda.
- si no hay elementos, es el primer elemento del árbol (la raíz).

Una de las grandes ventajas de este tipo de Árbol Binario es la facilidad que nos otorga para realizar búsquedas en él. Además, nos brinda mayor rapidez (menor complejidad) que las listas enlazadas, pudiendo obtener información de algún elemento con una complejidad de o(log(n)), cuando en una lista la complejidad de búsqueda es de o(n). Igualmente, más tarde será aclarado, pero es factible que un Árbol Binario de Búsqueda se degenere en una lista enlazada: siempre insertando un valor menor al anterior o siempre mayor al anterior.

Es decir, la diferencia entre un Árbol Binario y un Árbol Binario de Búsqueda es que el último tiene un criterio de relación entre nodos mientras el primero no, otorgandonos muchas ventajas principalmente para la búsqueda de elementos.

Las operaciones de un árbol binario son:
● Creación.
● Inserción (en cualquier lugar).
● Eliminación (en cualquier lugar).
● Búsqueda.
● Recorrido.
● Está vacío.
● Destrucción.

Un ejemplo sería:
                    
				  ________8__________
			_____3_____			_____10_____    
			1			6__		9		  __14__
							7			13		18

Una explicación de cómo realizar cualquiera de estas operaciones se encuentra al inicio de este .txt

Cuando se crea el árbol binario de búsqueda se hace junto a un comparador o un destructor. Sí o sí tiene que tener un comparador (para saber cómo comparar entre elementos), pero no necesariamente un destructor. Pero entonces, ¿por qué querríamos un destructor?


────────────────────────────────────¿Por qué el árbol se crea con un destructor?


Cuando el usuario crea un árbol binario de búsqueda, puede decidir si lo hace con un destructor o no. Si lo hace sin, tendrá que encargarse de los elementos que insertó en el árbol después de que el mismo se destruya; en cambio, si el árbol tiene destructor, al borrarse cada nodo con su respectivo elemento, se invocará al destructor para que se actúe de determinada manera con el elemento.

La ventaja de tener un destructor es que al finalizar el uso del ABB no hay que preocuparse por los elementos. Sin embargo, no podremos reutilizarlos tan fácilmente en otro árbol: se debe recordar que han sido cambiados de alguna forma por el destructor.

Un Árbol Binario de Búsqueda generalmente trabaja con elementos cuya memoria está reservada en el heap (memoria dinámica): esto amplifica la cantidad de datos con los que se puede trabajar, al saber que no se necesita espacio contiguo de memoria y prácticamente se tiene infinita memoria.

Se sabe que para poder reservar espacio para un elemento en la memoria dinámica, hay que solicitarlo al sistema. Del mismo modo, hay que avisarle al sistema cuando queremos que libere esa memoria.

De ahí surge tener un destructor en el árbol: cuando se inserta un elemento en el árbol, hay que preocuparse solamente por la reserva de memoria para el elemento (en palabras básicas, nos alcanza con hacer un simple "malloc()"): el TDA se encarga de la liberación de la memoria reservada para el mismo.

Es entonces que se decide crear un Árbol Binario de Búsqueda con o sin destructor: si se quiere utilizar el elemento solo en ese Árbol Binario de Búsqueda, y luego, al eliminar el árbol, que se elimine el elemento, creamos el árbol con el destructor. Sino, no.

En el caso de tener elementos almacenados en la memoria estática (stack), el destructor se utiliza para un fin muy similar, pero sin liberar la memoria. Por ejemplo, reiniciando los elementos (booleanos en "false", números a 0, char = '\0', etc).

Se presenta el mismo dilema: el usuario creará un árbol con un destructor si desea no tener que hacerse problemas por el reinicio de los elementos. Si necesita utilizar los datos para otra cosa, no podrá hacerlo tan fácilmente una vez invocado el destructor para dicho elemento.


─────¿Cuál es la complejidad de las operaciones de un Árbol Binario de Búsqueda?


Las operaciones de un árbol binario son:

● Creación (arbol_crear()): O(1). La acción no depende de factores externos: siempre costará lo mismo realizar la creación.

● Inserción (arbol_insertar()): O(n). Idealmente sería O(log(n)), pero en el peor caso, el árbol se comporta como una lista enlazada, y hay que recorrerla entera para insertar: el costo de la acción depende de la cantidad de elementos que haya en el arbol, teniendo una relación directamente proporcional.

● Eliminación (arbol_borrar()): O(n). Idealmente sería O(log(n)), pero en el peor caso, el árbol se comporta como una lista enlazada, y hay que recorrerla entera para borrar: el costo de la acción depende de la cantidad de elementos que haya en el arbol, teniendo una relación directamente proporcional.

● Búsqueda (arbol_buscar()): O(n). Idealmente sería O(log(n)), pero en el peor caso, el árbol se comporta como una lista enlazada, y hay que recorrerla entera para encontrar el elemento buscado: el costo de la acción depende de la cantidad de elementos que haya en el arbol, teniendo una relación directamente proporcional.

● Recorrido (arbol_recorrido_inorden(), arbol_recorrido_preorden(), arbol_recorrido_postorden(), abb_con_cada_elemento()): En el peor de los casos O(n). Se recorre el árbol con sus n elementos, uno por uno: el costo de la acción depende de la cantidad de elementos que haya en el arbol, teniendo una relación directamente proporcional. En caso que termine de recorrer antes, la complejidad será menor (ya sea porque se llenó el array o porque la función devolvió "true"): ahí ya no recorrería la totalidad del árbol.

● Está vacío (arbol_vacio()): O(1). La acción no depende de factores externos, es un simple checkeo: siempre costará lo mismo realizarlo.

● Obtener la raiz (arbol_raiz()): O(1). La acción no depende de factores externos: siempre costará lo mismo realizar la destrucción.

● Destrucción (arbol_destruir()): O(n). Hay que destruir la totalidad del árbol, por eso hay que recorrer sus n elementos: el costo de la acción depende de la cantidad de elementos que haya en el arbol, teniendo una relación directamente proporcional.

Inserción, eliminación y búsqueda serían idealmente O(log(n)) ya que si el árbol estuviera balanceado, la cantidad de tiempo que conlleve recorrer el arbol aumentaría linealmente mientras que la cantidad de datos recorridos aumentaría exponencialmente, ya que al ser un árbol binario, no se tendrían que recorrer todos los elementos: por cada elemento, se divide a la mitad el problema. Es decir, si en un segundo recorro 10 elementos, en dos segundos recorro 100 elementos.

______________________________________________________________________________FIN______________________________________________________________________________
