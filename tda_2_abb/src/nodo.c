#include "abb.h"
#include "nodo.h"

#define INORDEN 0
#define PREORDEN 1
#define POSTORDEN 2

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
		else if(nodo->derecha != NULL)
			return nodo->derecha;
		else{
			free(nodo);
			return NULL;
		}
	}

	if (comparacion < 0)
		nodo->izquierda = nodo_quitar(nodo->izquierda, elemento, comparador, elemento_quitado);
	else nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador, elemento_quitado);

	return nodo;
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