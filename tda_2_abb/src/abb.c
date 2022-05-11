#include "abb.h"
#include "nodo.h"
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
	if (arbol == NULL || arbol->tamanio == 0)
		return NULL;
	return nodo_buscar(arbol->nodo_raiz, elemento, arbol->comparador);;	
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol == NULL || arbol->tamanio == 0)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(arbol == NULL || arbol->tamanio == 0)
		return 0;
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

size_t nodo_con_cada_elemento(nodo_abb_t *nodo, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux, size_t elementos_recorridos) //TODO: Revisar por que no itera correctamente, hace dibujito no seas pajero
{	
	if(funcion(nodo->elemento, aux) ==false){
		return elementos_recorridos;
	}

	switch (recorrido){
	case INORDEN:
		if (nodo->izquierda)
			elementos_recorridos = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos);

		
		(elementos_recorridos)++;

		if (nodo->derecha)
			elementos_recorridos = nodo_con_cada_elemento(nodo->derecha,  recorrido, funcion, aux, elementos_recorridos);
		break;

	case PREORDEN:
		
		(elementos_recorridos)++;
		
		if (nodo->izquierda)
			elementos_recorridos = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos);


		if (nodo->derecha)
			elementos_recorridos = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos);
		break;

	case POSTORDEN:
		if (nodo->izquierda)
			elementos_recorridos = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos);

		if (nodo->derecha)
			elementos_recorridos = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos);
	
		(elementos_recorridos)++;
		break; 
	default:
		break;
	}
	return elementos_recorridos;		
}
size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	if(arbol == NULL || arbol->tamanio == 0)
		return 0;
	size_t elementos_recorridos = 0;

	elementos_recorridos = nodo_con_cada_elemento(arbol->nodo_raiz, recorrido, funcion, aux, elementos_recorridos);
	return elementos_recorridos;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array, size_t tamanio_array)
{
	if(arbol == NULL || arbol->tamanio == 0)
		return 0;

	size_t elementos_recorridos = 0;
	elementos_recorridos = nodo_recorrer(arbol->nodo_raiz, recorrido, array, tamanio_array, elementos_recorridos);
	return elementos_recorridos;
	
}
