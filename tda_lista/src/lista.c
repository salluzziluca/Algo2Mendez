#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

int insertar_nodo(lista_t *lista, nodo_t *nodo, void *elemento)
{
	nodo->elemento = elemento;
	nodo->siguiente = NULL;
	lista->nodo_fin = nodo;

	return 0;
}

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));

	if(lista == NULL)
		return NULL;
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));

	if(nodo == NULL)
		return NULL;

	//TODO: Revisar la sintaxis, ver si se puede optimizar
	
	if(lista->cantidad == 0){
		insertar_nodo(lista, nodo, elemento);
		/*nodo->elemento = elemento;
		nodo->siguiente = NULL;
		lista->nodo_fin = nodo;*/
		lista->nodo_inicio = nodo;
		lista->cantidad++;
	}
	else{
		insertar_nodo(lista, nodo, elemento);
		/*nodo->elemento = elemento;
		nodo->siguiente = NULL;
		lista->nodo_fin = nodo;*/
		lista->nodo_fin->siguiente = nodo;
		lista->cantidad++;
	}
	
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	return NULL;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return NULL;
}

bool lista_vacia(lista_t *lista)
{
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	return 0;
}

void lista_destruir(lista_t *lista)
{
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
//tener en cuenta en uso de cantidad. 
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{

}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
