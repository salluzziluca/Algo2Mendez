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

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	//if comparador > a cero, insertar a la derecha
	//if comparador < a cero, insertar a la izquierda
	if(arbol == NULL)
		return NULL;

	if(arbol->nodo_raiz->elemento == NULL){
		arbol->nodo_raiz->elemento = elemento;
		arbol->tamanio++;
	}
	else if(arbol->comparador(elemento, arbol->nodo_raiz->elemento) > 0){
		abb_insertar(arbol->nodo_raiz->derecha, elemento);
	}
	else if(arbol->comparador(elemento, arbol->nodo_raiz->elemento) == 0){

	}
	else if(arbol->comparador(elemento, arbol->nodo_raiz->elemento) < 0){
		abb_insertar(arbol->nodo_raiz->izquierda, elemento);
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
