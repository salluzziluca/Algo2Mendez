#include "abb.h"
#include <stddef.h>
#include <stdlib.h>


abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *arbol = malloc(sizeof(abb_t));
	if (arbol == NULL) {
		return NULL;
	}
	arbol->nodo_raiz = calloc(1, sizeof(nodo_abb_t));
	
	if (arbol->nodo_raiz == NULL){
		free(arbol);
		return NULL;
	}
	arbol->comparador = comparador;
	arbol->tamanio = 0;
	return arbol;
}

// nodo_abb_t *nodo_insertar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador){
// 	if (nodo == NULL)
// 		return

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	//if comparador > a cero, insertar a la derecha
	//if comparador < a cero, insertar a la izquierda
	if(arbol == NULL)
		return NULL;

	if(arbol->nodo_raiz == NULL){
		nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
		if(nodo == NULL)
			return NULL;
		arbol->nodo_raiz = nodo;
		nodo->elemento = elemento;
		arbol->nodo_raiz->elemento = elemento;
		arbol->tamanio++;
	}
	else {	
		int comparacion = arbol->comparador(elemento, arbol->nodo_raiz->elemento);

		if(comparacion > 0){ //si es mayor lo inserta a la derecha
			abb_t *subarbol_derecho = malloc(sizeof(abb_t));
			subarbol_derecho->nodo_raiz = arbol->nodo_raiz->derecha;
			subarbol_derecho->comparador = arbol->comparador;
			subarbol_derecho->tamanio = arbol->tamanio;
			//TODO: Fijarme bien el tema del calloc, como deberia ser para la liberacion. Por ahi conviene directamente asignar todo a NULL
			subarbol_derecho->nodo_raiz = calloc(1, sizeof(nodo_abb_t));

			arbol->nodo_raiz->derecha = abb_insertar(subarbol_derecho, elemento)->nodo_raiz;
		}
		else if(comparacion <= 0){ // si es menor lo inserta a la izquierda
			abb_t *subarbol_izquierdo = malloc(sizeof(abb_t));
			subarbol_izquierdo->nodo_raiz = arbol->nodo_raiz->izquierda;
			subarbol_izquierdo->comparador = arbol->comparador;
			subarbol_izquierdo->tamanio = arbol->tamanio;
			subarbol_izquierdo->nodo_raiz = NULL;
			
			arbol->nodo_raiz->izquierda = abb_insertar(subarbol_izquierdo, elemento)->nodo_raiz;
		}
	}
	

	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{
	return 0;
}

void abb_destruir(abb_t *arbol)
{
	free(arbol->nodo_raiz);
	free(arbol);
	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
