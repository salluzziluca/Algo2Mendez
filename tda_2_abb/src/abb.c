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

nodo_abb_t *nodo_insertar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador){
	if (nodo == NULL){
		nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
		if (nodo == NULL){
			return NULL;
		}
		nodo->elemento = elemento;
		return nodo;
	}

	if(nodo->elemento == NULL){
		nodo->elemento = elemento;
		return nodo;
	}

	int comparacion = comparador(elemento, nodo->elemento);
	
	if (comparacion > 0)
		nodo->derecha = nodo_insertar(nodo->derecha, elemento, comparador);
	
	else if (comparacion <= 0)
		nodo->izquierda = nodo_insertar(nodo->izquierda, elemento, comparador);

	
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;

	arbol->nodo_raiz = nodo_insertar(arbol->nodo_raiz, elemento, arbol->comparador);
	arbol->tamanio++;


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

	return arbol->tamanio;
}

void nodo_destruir(nodo_abb_t *nodo){
	if(nodo == NULL)
		return;
		
	nodo_destruir(nodo->izquierda);
	nodo_destruir(nodo->derecha);
	free(nodo);
	
}
void abb_destruir(abb_t *arbol)
{
	nodo_destruir(arbol->nodo_raiz);

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
