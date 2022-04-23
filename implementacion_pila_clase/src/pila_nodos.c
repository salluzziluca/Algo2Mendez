#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

struct nodo {
	void *elemento;
	struct nodo *siguiente;
};

struct pila {
	struct nodo *tope;
	int cantidad;
};

pila_t *pila_crear()
{
	return calloc(1, sizeof(pila_t));
}

int pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila)
		return -1;

	struct nodo *nodo = malloc(sizeof(struct nodo));
	if (!nodo)
		return -1;

	nodo->elemento = elemento;
	nodo->siguiente = pila->tope;

	pila->tope = nodo;
	pila->cantidad++;

	return 0;
}

void *pila_desapilar(pila_t *pila)
{
	struct nodo *nuevo_tope = pila->tope->siguiente;
	void *elemento = pila->tope->elemento;

	free(pila->tope);
	pila->tope = nuevo_tope;

	return elemento;
}

void *pila_tope(pila_t *pila)
{
	if (pila->tope == NULL)
		return NULL;

	return pila->tope->elemento;
}

int pila_cantidad(pila_t *pila)
{
	return pila->cantidad;
}

void pila_destruir(pila_t *pila)
{
	while (pila->tope) {
		struct nodo *aux = pila->tope->siguiente;
		free(pila->tope);
		pila->tope = aux;
	}

	free(pila);
}

void pila_mostrar_elementos(pila_t *pila, void (*formateador)(void*))
{
	struct nodo *actual = pila->tope;
	while (actual != NULL) {
		formateador(actual->elemento);

		actual = actual->siguiente;
	}
}



void *pila_buscar(pila_t *pila, int (*comparador)(void *, void *),
		  void *contexto)
{
	struct nodo *actual = pila->tope;
	while (actual != NULL) {
		if(comparador(actual->elemento, contexto) == 0)
			return actual->elemento;

		actual = actual->siguiente;
	}
	return NULL;
}
