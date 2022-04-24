#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
* Recibe un nodo y lo inserta a la lista,
* apunta el puntero "siguiente" del nodo a NULL
*/
int llenar_nodo(nodo_t *nodo, void *elemento)
{
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return 0;
}

lista_t *lista_crear()
{	
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL)
		return NULL;
		
	nodo_t *nodo_actual = malloc(sizeof(nodo_t));

	if(nodo_actual == NULL)
		return NULL;
	
	if(lista->cantidad == 0){
		llenar_nodo(nodo_actual, elemento);
		lista->nodo_fin = nodo_actual;
		lista->nodo_inicio = nodo_actual;
		lista->cantidad++;
	}
	else{
		llenar_nodo(nodo_actual, elemento);
		lista->nodo_fin->siguiente = nodo_actual;
		lista->nodo_fin = nodo_actual;
		lista->cantidad++;
	}
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(lista == NULL)
		return NULL;

	nodo_t *nodo_actual = malloc(sizeof(nodo_t));

	if(nodo_actual == NULL)
		return NULL;
		
	if(posicion > lista->cantidad){
		posicion = lista->cantidad;
		printf("Posicion fuera de rango, se insertara al final (%li)\n", posicion);
	}

	if(lista->cantidad == 0){
		llenar_nodo(nodo_actual, elemento);
		lista->nodo_fin = nodo_actual;
		lista->nodo_inicio = nodo_actual;
		lista->cantidad++;
	}
	else if(posicion == 0){
		llenar_nodo(nodo_actual, elemento);
		nodo_actual->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_actual;
		lista->cantidad++;
	}
	else if (posicion > 0 && posicion < lista->cantidad){
		nodo_t *nodo_anterior = lista->nodo_inicio;

		for(size_t i = 0; i < posicion-1; i++){
			if(nodo_anterior == NULL)
				return NULL;
			nodo_anterior = nodo_anterior->siguiente;
		}

		llenar_nodo(nodo_actual, elemento);
		nodo_actual->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_actual;
		lista->cantidad ++;
	}
	else if(posicion == lista->cantidad){
		free(nodo_actual);
		lista_insertar(lista, elemento);
	}
	
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if(lista == NULL)
		return NULL;

	nodo_t *nodo_anterior = lista->nodo_inicio;
	
	for(size_t i = 0; i < lista->cantidad-2; i++){
		if(nodo_anterior == NULL)
			return NULL;
		nodo_anterior = nodo_anterior->siguiente;
	}

	nodo_t* aux_para_eliminar = lista->nodo_fin;
	void * elemento_a_devolver = lista->nodo_fin->elemento;
	lista->nodo_fin = nodo_anterior;
	lista->nodo_fin->siguiente = NULL;
	lista->cantidad--;
	free(aux_para_eliminar);
	
	return elemento_a_devolver;

}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL)
		return NULL;
	
	if(posicion > lista->cantidad){
		posicion = lista->cantidad;
		printf("Posicion fuera de rango, se quitará el final (%li)\n", posicion);
	}

	nodo_t *nodo_anterior = lista->nodo_inicio;

	for(size_t i = 0; i < posicion-1; i++){
		if(nodo_anterior == NULL)
			return NULL;
		nodo_anterior = nodo_anterior->siguiente;
	}

	nodo_t *nodo_a_eliminar = nodo_anterior->siguiente;
	void* elemento_a_devolver = nodo_a_eliminar->elemento;
	nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
	lista->cantidad--;
	free(nodo_a_eliminar);

	return elemento_a_devolver;
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
	for(size_t i = 0; i < lista->cantidad; i++){

		nodo_t *bloque_auxiliar = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = bloque_auxiliar;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	for(size_t i = 0; i < lista->cantidad; i++){

		nodo_t *bloque_auxiliar = lista->nodo_inicio->siguiente;
		funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = bloque_auxiliar;
	}
	free(lista);
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
