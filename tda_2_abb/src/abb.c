#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

#define INORDEN 0
#define PREORDEN 1
#define POSTORDEN 2

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
/*
* Recibe un nodo, un elemento a agregar y una forma de compararls. Si el nod es nulo, 
* lo crea. Si es nodo no tiene elemento, le asigna el elemento actual.
* Por ultimo, si el nodo tiene elemento, lo compara con el actual y
* segun si es la comparación devuelve mayor, menor o igual a 0,se desplaza hacia
* el siguiente nodo en el arbol. Nodo derecho o izquierdo respectivaemente.
*/
nodo_abb_t *nodo_insertar(nodo_abb_t *nodo, void *elemento, abb_comparador comparador){
	if (nodo == NULL){
		nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
		if (nodo == NULL){
			return NULL;
		}
		nodo->elemento = elemento;
		return nodo;
	}

	if(nodo->elemento == NULL){
		nodo->elemento = elemento;
		return nodo;
	}

	int comparacion = comparador(elemento, nodo->elemento);
	
	if (comparacion > 0)
		nodo->derecha = nodo_insertar(nodo->derecha, elemento, comparador);
	
	else if (comparacion <= 0)
		nodo->izquierda = nodo_insertar(nodo->izquierda, elemento, comparador);

	
	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;

	arbol->nodo_raiz = nodo_insertar(arbol->nodo_raiz, elemento, arbol->comparador);
	arbol->tamanio++;


	return arbol;
}

void *obtener_predecesor_inorder(nodo_abb_t *nodo, void **nodo_reemplazo)
{
	if(nodo->derecha == NULL){
		*nodo_reemplazo = nodo;
		return nodo->izquierda;
	}
	nodo->derecha = obtener_predecesor_inorder(nodo->derecha, nodo_reemplazo);
	return nodo;
}

nodo_abb_t *nodo_quitar (nodo_abb_t *nodo, void *elemento, abb_comparador comparador, nodo_abb_t **nodo_quitado, abb_t *arbol)
{
	if (nodo == NULL)
		return NULL;
		
	int comparacion = comparador(elemento, nodo->elemento);
		
	if (comparacion == 0){
		*nodo_quitado = nodo; //este es el elemento que vamos a borrar
		
		if(nodo->izquierda != NULL && nodo->derecha != NULL){
			void *elemento_reemplazo = NULL; //este va a ser el que pongamos en reemplazo del eliminado
			nodo->izquierda= obtener_predecesor_inorder(nodo->izquierda, &elemento_reemplazo); // buscamos el predecesor inorder
			nodo->elemento = elemento_reemplazo; // y lo reemplazamos :)
			if(arbol->nodo_raiz == *nodo_quitado)
				arbol->nodo_raiz = nodo;
			return nodo;
		}
		if(nodo->izquierda != NULL)
			return nodo->izquierda;
		return nodo->derecha;
			
	}

	if (comparacion < 0)
		nodo->izquierda = nodo_quitar(nodo->izquierda, elemento, comparador, nodo_quitado, arbol);
	else nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador, nodo_quitado, arbol);

	return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL|| elemento == NULL || arbol->tamanio == 0)
		return NULL;
	if (arbol->tamanio == 1)
		return arbol->nodo_raiz->elemento;

	nodo_abb_t *nodo_quitado = NULL;
	nodo_quitar(arbol->nodo_raiz, elemento, arbol->comparador, &nodo_quitado, arbol);
	
	if(nodo_quitado != NULL){
		arbol->tamanio--;
		void *elemento_quitado = nodo_quitado->elemento;
		free(nodo_quitado);
		return elemento_quitado;
	}		
	else
		return NULL;
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

	if(comparacion == 0){
		return nodo->elemento;
	}
	else if(comparacion > 0)
		return nodo_buscar(nodo->derecha, elemento, comparador);
	else if(comparacion < 0)
		return nodo_buscar(nodo->izquierda, elemento, comparador);
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

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t nodo_recorrer(nodo_abb_t *nodo, abb_recorrido recorrido, void **array, size_t tamanio_array, size_t elementos_recorridos)
{
	

	
	switch (recorrido){
	case INORDEN:
		if (nodo->izquierda)
			elementos_recorridos = nodo_recorrer(nodo->izquierda, recorrido, array, tamanio_array, elementos_recorridos);

		array[elementos_recorridos] = nodo->elemento;
		(elementos_recorridos)++;

		if (nodo->derecha)
			elementos_recorridos = nodo_recorrer(nodo->derecha, recorrido, array, tamanio_array, elementos_recorridos);
		break;

	case PREORDEN:
		array[elementos_recorridos] = nodo->elemento;
		(elementos_recorridos)++;
		
		if (nodo->izquierda)
			elementos_recorridos = nodo_recorrer(nodo->izquierda, recorrido, array, tamanio_array, elementos_recorridos);

		if (nodo->derecha)
			elementos_recorridos = nodo_recorrer(nodo->derecha, recorrido, array, tamanio_array, elementos_recorridos);
		break;

	case POSTORDEN:
		if (nodo->izquierda)
			elementos_recorridos = nodo_recorrer(nodo->izquierda, recorrido, array, tamanio_array, elementos_recorridos);

		if (nodo->derecha)
			elementos_recorridos = nodo_recorrer(nodo->derecha, recorrido, array, tamanio_array, elementos_recorridos);
		
		array[elementos_recorridos] = nodo->elemento;
		(elementos_recorridos)++;
		break; 

	default:
		break;
	}
	return elementos_recorridos;	
}
size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if(arbol == NULL)
		return 0;

	size_t elementos_recorridos = 0;
	elementos_recorridos = nodo_recorrer(arbol->nodo_raiz, recorrido, array, tamanio_array, elementos_recorridos);
	return elementos_recorridos;
	
}
