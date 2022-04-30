#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
* Recibe un nodo válido y lo inserta a la lista,
* apunta el puntero "siguiente" del nodo a NULL
*/
int llenar_nodo(nodo_t *nodo, void *elemento)
{
	if (nodo == NULL)
		return -1;
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

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion)
{
	if(lista == NULL)
		return NULL;

	nodo_t *nodo_actual = malloc(sizeof(nodo_t));

	if(nodo_actual == NULL)
		return NULL;
		
	if(posicion > lista->cantidad){
		posicion = lista->cantidad;
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
	if(lista == NULL || lista->cantidad == 0)
		return NULL;

	nodo_t *nodo_anterior = lista->nodo_inicio;
	if(lista->cantidad == 1){
		nodo_anterior = lista->nodo_inicio;
	}
	else{
		for(size_t i = 0; i < lista->cantidad-2; i++){
		if(nodo_anterior == NULL)
			return NULL;
		nodo_anterior = nodo_anterior->siguiente;
		}
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
	if(lista == NULL || lista->cantidad == 0)
		return NULL;
	
	if(posicion > lista->cantidad){
		posicion = lista->cantidad-1;
	}
	nodo_t *nodo_anterior = lista->nodo_inicio;
	nodo_t *nodo_a_eliminar = NULL;
	void *elemento_a_devolver = NULL;

	if(posicion == 0){
		nodo_a_eliminar = lista->nodo_inicio;
		elemento_a_devolver = nodo_a_eliminar->elemento;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		lista->cantidad--;
		free(nodo_a_eliminar);

	}
	else{
		for(size_t i = 0; i < posicion-1; i++){
		if(nodo_anterior == NULL)
			return NULL;
		nodo_anterior = nodo_anterior->siguiente;
		}

		nodo_a_eliminar = nodo_anterior->siguiente;
		elemento_a_devolver = nodo_a_eliminar->elemento;
		nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
		if(posicion == lista->cantidad-1){
			lista->nodo_fin = nodo_anterior;
		}
		lista->cantidad--;
		free(nodo_a_eliminar);
	}
	

	return elemento_a_devolver;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista->cantidad == 0)
		return NULL;
	
	nodo_t *nodo_a_devolver = lista->nodo_inicio;
	void *elemento_a_devolver = NULL;

	if(posicion > lista->cantidad){
		return NULL;
	}
	else if(posicion == 0){
		nodo_a_devolver = lista->nodo_inicio;
		elemento_a_devolver = nodo_a_devolver->elemento;
	}
	else{
		for(size_t i = 0; i < posicion; i++){
			if(lista->nodo_inicio == NULL)
				return NULL;
			nodo_a_devolver = nodo_a_devolver->siguiente;
		}
		if(nodo_a_devolver == NULL)
			return NULL;
		elemento_a_devolver = nodo_a_devolver->elemento;
		
	}
	return elemento_a_devolver;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(lista == NULL || lista->cantidad == 0 || comparador == NULL)
		return NULL;
		
	nodo_t* nodo_actual = lista->nodo_inicio;
	while(comparador(nodo_actual->elemento, contexto) != 0){
		if(nodo_actual->siguiente == NULL)
			return NULL;
		nodo_actual = nodo_actual->siguiente;
	}
	void *primer_elemento_coincidente = nodo_actual->elemento;

	return primer_elemento_coincidente;
}

void *lista_primero(lista_t *lista)
{
	if(lista == NULL || lista->nodo_inicio == NULL || lista->cantidad == 0)
		return NULL;

	void *primer_elemento = lista->nodo_inicio->elemento;
	return primer_elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(lista == NULL || lista->nodo_fin == NULL || lista->cantidad == 0)
		return NULL;
	void *ultimo_elemento = lista->nodo_fin->elemento;
	return ultimo_elemento;
}

bool lista_vacia(lista_t *lista)
{
	bool esta_vacia = false;
	if(lista == NULL)
		esta_vacia = true;
	else if(lista->cantidad == 0)
		esta_vacia = true;
	return esta_vacia;
}

size_t lista_tamanio(lista_t *lista)
{
	if(lista == NULL)
		return 0;
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{	
	if(lista == NULL)
		return;
	for(size_t i = 0; i < lista->cantidad; i++){

		nodo_t *bloque_auxiliar = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = bloque_auxiliar;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(funcion == NULL || lista == NULL){
		lista_destruir(lista);
		return;
	}
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
	if(lista == NULL)
		return NULL;
		
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(iterador == NULL)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->corriente == NULL)
		return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->lista->cantidad == 0)
		return false;

	bool avanzado = false;
	iterador->corriente = iterador->corriente->siguiente;

	if(iterador->corriente != NULL)
		avanzado = true;

	return avanzado;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->corriente == NULL)
		return NULL;
		
	return iterador->corriente->elemento;	
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if(lista == NULL || funcion == NULL)
		return 0;

	size_t elementos_recorridos = 0;
	bool continuar = true;
	nodo_t* nodo_actual = lista->nodo_inicio;

	while(elementos_recorridos < lista->cantidad && continuar == true){
		continuar = funcion(nodo_actual->elemento, contexto);
		nodo_actual = nodo_actual->siguiente;
		elementos_recorridos++;
	}
	return elementos_recorridos;
}
