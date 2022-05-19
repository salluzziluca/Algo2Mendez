#ifndef __NODO__H__
#define __NODO__H__

#include <stdbool.h>
#include <stdlib.h>

/*
* Recibe un nodo, un elemento a agregar y una forma de compararls. Si el nod es nulo, 
* lo crea. Si es nodo no tiene elemento, le asigna el elemento actual.
* Por ultimo, si el nodo tiene elemento, lo compara con el actual y
* segun si es la comparación devuelve mayor, menor o igual a 0,se desplaza hacia
* el siguiente nodo en el arbol. Nodo derecho o izquierdo respectivaemente.
*/
nodo_abb_t *nodo_insertar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador);

/*
* Itera recursivamente por el arbol comparando el elemento igresado por parametro con 
* el elemento del nodo actual. Si el comparador devuelve 0, los elementos son iguales
* y la funcion lo duelve. De lo contrario, itera al proximo nodo. Al derecho si
* la comparacion devuelve mayor a cero o al derecho si devuelve menor a cero. 
*/
void *nodo_buscar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador);

/*
* Recibe el nodo actual y un puntero a un nodo.
* Itera rescursivamente el arbol hasta encontrar el nodo con el elemento a eliminar.
* De encontrarlo, se busca su predecesor inorden y se reemplaza el elemento a eliminar
* por el elemento predecesor.
* Devuelve el nodo eliminado de haberlo encontrado, sino devuelve NULL.
*/
void *obtener_predecesor_inorder(nodo_abb_t *nodo, nodo_abb_t **nodo_reemplazo);

/*
* Recibe el nodo actual, el elemento a quitar, el comparador, y un puntero a elemento.
* Si el nodo actual es válido, se compara el elemento con el elemento del nodo actual.
* De no se iguales, se iterara recursivamente a la derecha o a la izquierda, respectivamente.
* Si se encuentra el elemento a quitar, 
*/
nodo_abb_t *nodo_quitar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado, size_t *tamanio);

/*
* Recibe un arbol, si no es nulo ni vacio, recorre los nodos segun el tipo de recorrido especificado, 
* a medida que avanza entre nodos, incrementa el contador de elementos recorridos.
* Devuelve el contador de elementos recorridos. Si el arbol es nulo o vacio, devuelve 0.
*/
size_t nodo_recorrer(nodo_abb_t *nodo, abb_recorrido recorrido, void **array, size_t tamanio_array, size_t elementos_recorridos);

#endif /* __NODO_H__ */