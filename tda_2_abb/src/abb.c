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

void *obtener_predecesor_inorder(nodo_abb_t *nodo, nodo_abb_t **nodo_reemplazo)
{
	if(nodo->derecha == NULL){
		*nodo_reemplazo = nodo;
		return nodo->izquierda;
	}
	nodo->derecha = obtener_predecesor_inorder(nodo->derecha, nodo_reemplazo);
	return nodo;
}

nodo_abb_t *nodo_quitar (nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado)
{
	if (nodo == NULL)
		return NULL;
		
	int comparacion = comparador(elemento, nodo->elemento);
		
	if (comparacion == 0){
		*elemento_quitado = nodo->elemento; //este es el elemento que vamos a borrar
		
		if(nodo->izquierda != NULL){
			nodo_abb_t *nodo_reemplazo = NULL; //este va a ser el que pongamos en reemplazo del eliminado
			nodo->izquierda= obtener_predecesor_inorder(nodo->izquierda, &nodo_reemplazo); // buscamos el predecesor inorder
			nodo->elemento = nodo_reemplazo->elemento; // y lo reemplazamos :)
			free(nodo_reemplazo);
			return nodo;
		}

		return nodo->derecha;
			
	}

	if (comparacion < 0)
		nodo->izquierda = nodo_quitar(nodo->izquierda, elemento, comparador, elemento_quitado);
	else nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador, elemento_quitado);

	return nodo;
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
	
	if(elemento_quitado == elemento)
		arbol->tamanio--;

	return elemento_quitado;
}


/*
* Itera recursivamente por el arbol comparando el elemento igresado por parametro con 
* el elemento del nodo actual. Si el comparador devuelve 0, los elementos son iguales
* y la funcion lo duelve. De lo contrario, itera al proximo nodo. Al derecho si
* la comparacion devuelve mayor a cero o al derecho si devuelve menor a cero. 
*/
void *nodo_buscar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador){
	if(nodo == NULL)
		return NULL;

	int comparacion = comparador(elemento, nodo->elemento);

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
	if(arbol == NULL || funcion == NULL || arbol->tamanio == 0)
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
