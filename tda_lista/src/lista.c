#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{
	return NULL;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	return NULL;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	return NULL;
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
		lista->cantidad--;
		free(nodo_a_eliminar);
	}
	

	return elemento_a_devolver;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL)
		return NULL;
	
	nodo_t *nodo_a_devolver = lista->nodo_inicio;
	void *elemento_a_devolver = NULL;

	if(posicion > lista->cantidad){
		posicion = lista->cantidad;
		printf("Posicion fuera de rango, se devolverá el final (%li)\n", posicion);
		nodo_a_devolver = lista->nodo_fin;
		elemento_a_devolver = nodo_a_devolver->elemento;
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
		elemento_a_devolver = nodo_a_devolver->elemento;
	}
	return elemento_a_devolver;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(lista == NULL)
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
	if(lista == NULL || lista->nodo_inicio == NULL )
		return NULL;

	void *primer_elemento = lista->nodo_inicio->elemento;
	return primer_elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(lista == NULL || lista->nodo_fin == NULL )
		return NULL;
	void *ultimo_elemento = lista->nodo_fin->elemento;
	return ultimo_elemento;
}

bool lista_vacia(lista_t *lista)
{
	bool esta_vacia = false;
	if(lista == NULL)
		esta_vacia = true;
	if(lista->cantidad == 0)
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

}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

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
	if(iterador == NULL)
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
	if(lista == NULL)
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
