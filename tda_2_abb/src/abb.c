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
	if (arbol == NULL|| elemento == NULL || arbol->tamanio == 0)
		return NULL;
	void *elemento_quitado = NULL;

	if (arbol->tamanio == 1){
		elemento_quitado = arbol->nodo_raiz->elemento;
		arbol->nodo_raiz->elemento = NULL;
		arbol->tamanio--;
		return elemento_quitado;
	}
	
	nodo_quitar(arbol->nodo_raiz, elemento, arbol->comparador, &elemento_quitado);
	
	if(*(int*)elemento_quitado == *(int*)elemento)
		arbol->tamanio--;

	return elemento_quitado;
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
	if(arbol == NULL)
		return;
	abb_destruir_todo(arbol, NULL);
	return;
}

void nodo_destruir_todo(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if(nodo == NULL)
		return;
	
	if(nodo->izquierda != NULL)
		nodo_destruir_todo(nodo->izquierda, destructor);
	
	if(nodo->derecha != NULL)
		nodo_destruir_todo(nodo->derecha, destructor);
	
	if(destructor != NULL)
		destructor(nodo->elemento);
		
	free(nodo);

	return;
}
void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	nodo_destruir_todo(arbol->nodo_raiz, destructor);
	free(arbol);
	return;
}

bool nodo_con_cada_elemento(nodo_abb_t *nodo, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos, bool continuar) //TODO: Revisar por que no itera correctamente, hace dibujito no seas pajero
{	
	if(continuar == false)
		return false;
	switch (recorrido){
	case INORDEN:
		if(nodo->izquierda != NULL)
			continuar = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos, continuar);

		if (!funcion(nodo->elemento, aux))
			return false;
		(*elementos_recorridos)++;
		
		if(nodo->derecha != NULL)
			continuar = nodo_con_cada_elemento(nodo->derecha,  recorrido, funcion, aux, elementos_recorridos, continuar);
		break;

	case PREORDEN:
		
		if (!funcion(nodo->elemento, aux))
			return false;
		(*elementos_recorridos)++;
		if(nodo->izquierda != NULL)
			continuar = nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos, continuar);
		if(nodo->derecha != NULL)
			continuar = nodo_con_cada_elemento(nodo->derecha,  recorrido, funcion, aux, elementos_recorridos, continuar);
		break;

	case POSTORDEN:
		
		if(!nodo)
			return true;
			
		if(!nodo_con_cada_elemento(nodo->izquierda, recorrido, funcion, aux, elementos_recorridos, continuar))
			return false;

		if(!nodo_con_cada_elemento(nodo->derecha,  recorrido, funcion, aux, elementos_recorridos, continuar))
			return false;
		
		(*elementos_recorridos)++;

		if (!funcion(nodo->elemento, aux))
			return false;

		break;

	default:
		break;
	}
	return true;		
}
size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	if(arbol == NULL || funcion == NULL || arbol->tamanio == 0)
		return 0;
	size_t elementos_recorridos = 0;
	bool continuar = true;
	nodo_con_cada_elemento(arbol->nodo_raiz, recorrido, funcion, aux, &elementos_recorridos, continuar);
	return false;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array, size_t tamanio_array)
{
	if(arbol == NULL || arbol->tamanio == 0)
		return 0;

	size_t elementos_recorridos = 0;
	nodo_recorrer(arbol->nodo_raiz, recorrido, array, tamanio_array, elementos_recorridos);
	return false;
	
}
