#ifndef __NODO__H__
#define __NODO__H__

#include <stdbool.h>
#include <stdlib.h>

/*
* Recibe un nodo, un elemento a agregar y una forma de compararlo. Si el nodo es nulo, 
* lo crea. Si es nodo no tiene elemento, le asigna el elemento actual.
* Por ultimo, si el nodo tiene elemento, lo compara con el actual y
* segun si es la comparación devuelve mayor, menor o igual a 0,se desplaza hacia
* el siguiente nodo en el arbol. Nodo derecho o izquierdo respectivaemente.
*/
nodo_abb_t *nodo_insertar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador);

/*
* Recibe el nodo actual, el elemento a quitar, el comparador, un puntero a elemento y un puntero al tamaño del arbol.
* Si el nodo actual es válido, se compara el elemento con el elemento del nodo actual.
* De no se iguales, se iterara recursivamente a la derecha o a la izquierda, respectivamente.
* Si se encuentra el elemento a quitar (la comparación dice que son iguales), se lo reemplaza por su 
* predecesor inorden (de no haber, por su nodo hijo mas cercano) y se resta 1 al tamaño del arbol.
*/
nodo_abb_t *nodo_quitar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado, size_t *tamanio);

/*
* Itera recursivamente por el arbol comparando el elemento igresado por parametro con 
* el elemento del nodo actual. Si el comparador devuelve 0, los elementos son iguales
* y la funcion lo duelve. De lo contrario, itera al proximo nodo. Al derecho si
* la comparacion devuelve mayor a cero o al derecho si devuelve menor a cero. 
*/
void *nodo_buscar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador);

/*
* Recibe un nodo y una funcion destructora.
* Recorre el arbol de forma postorden y destruye, segun el criterio del usuario, 
* los elementos de los nodos. Luego, libera la memoria asignada al nodo.
*/
void nodo_destruir_todo(nodo_abb_t *nodo, void (*destructor)(void *));

/*
* Recibe un nodo y un puntero a un nodo.
* Itera recursivamente el arbol hasta encontrar el nodo mas grande dentro de la rama actual.
* De encontrarlo, se apunta el puntero pasado por parametro al nodo actual.
* Devuelve el nodo izquierda del nodo mayor de esa rama, este puede ser o no NULL.
*/
void *obtener_predecesor_inorder(nodo_abb_t *nodo, nodo_abb_t **nodo_reemplazo);

/*
* Itera recursivamente de forma inorden (izquierda, elemento, derecha) invocando a la funcion
* pasada como parametro en cada uno de los elementos del arbol.
* Si la funcion devuelve false, corta la iteracion.
* A medida que se recorre el arbol, se incrementa el contador de elementos recorridos.
*/
bool inorder_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos);

/*
* Itera recursivamente de forma preorden (elemento, izquierda, derecha) invocando a la funcion
* pasada como parametro en cada uno de los elementos del arbol.
* Si la funcion devuelve false, corta la iteracion.
* A medida que se recorre el arbol, se incrementa el contador de elementos recorridos.
*/
bool preorder_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos);

/*
* Itera recursivamente de forma postorden (izquierda, derecha, elemento) invocando a la funcion
* pasada como parametro en cada uno de los elementos del arbol.
* Si la funcion devuelve false, corta la iteracion.
* A medida que se recorre el arbol, se incrementa el contador de elementos recorridos.
*/
bool postorden_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos);

/*
* Recibe un tipo de recorrido especificado por el usuario y una funcion.
* Segun el tipo de recorrido, invoca a la funcion 
* en cada uno de los elementos del arbol en diferente orden.
* A medida que se recorre el arbol, se incrementa el contador de elementos recorridos.
*/
bool nodo_con_cada_elemento(nodo_abb_t *nodo, abb_recorrido , bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos);


/*
* Recibe un arbol, si no es nulo ni vacio, recorre los nodos segun el tipo de recorrido especificado, 
* a medida que avanza entre nodos, incrementa el contador de elementos recorridos.
* Devuelve el contador de elementos recorridos. Si el arbol es nulo o vacio, devuelve 0.
*/ //TODO: arreglar y revisar este comentario
size_t nodo_recorrer(nodo_abb_t *nodo, abb_recorrido recorrido, void **array, size_t tamanio_array, size_t elementos_recorridos);

#endif /* __NODO_H__ */