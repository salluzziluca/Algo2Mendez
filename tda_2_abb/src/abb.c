#include "abb.h"
#include "nodo.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(comparador == NULL)
		return NULL;
	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (arbol == NULL) {
		return NULL;
	}
	
	arbol->comparador = comparador;
	return arbol;
}


abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;
	if(arbol->nodo_raiz == NULL){
		arbol->nodo_raiz = calloc(1, sizeof(nodo_abb_t));
	
		if (arbol->nodo_raiz == NULL){
			free(arbol);
			return NULL;
		}
	}
	arbol->nodo_raiz = nodo_insertar(arbol->nodo_raiz, elemento, arbol->comparador);
	arbol->tamanio++;


	return arbol;
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL || arbol->tamanio == 0 || arbol->comparador == NULL)
		return NULL;
	void *elemento_quitado = NULL;
	
	arbol->nodo_raiz =  nodo_quitar(arbol->nodo_raiz, elemento, arbol->comparador, &elemento_quitado, &arbol->tamanio);

	return elemento_quitado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL || arbol->tamanio == 0 || arbol->comparador == NULL)
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
	if(arbol == NULL)
		return 0;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	if(arbol == NULL)
		return;
	abb_destruir_todo(arbol, NULL);
	return;
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(arbol == NULL)
		return;
	nodo_destruir_todo(arbol->nodo_raiz, destructor);
	free(arbol);
	return;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	if(arbol == NULL || funcion == NULL || arbol->tamanio == 0)
		return 0;
	size_t elementos_recorridos = 0;
	nodo_con_cada_elemento(arbol->nodo_raiz, recorrido, funcion, aux, &elementos_recorridos);
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
