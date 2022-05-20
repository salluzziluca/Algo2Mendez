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

	if(nodo->elemento == NULL){ //TODO: ver si puedo hacer que llene el nodo pero sin que no pueda cargar elementos nulos, fijame bajo que condicion
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

nodo_abb_t *nodo_quitar (nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado, size_t *tamanio)
{
	if (nodo == NULL)
		return NULL;
		
	int comparacion = comparador(elemento, nodo->elemento);
		
	if (comparacion == 0){
		*elemento_quitado = nodo->elemento;
		
		if(nodo->izquierda != NULL || (nodo->izquierda != NULL && 	nodo->derecha != NULL)){
			nodo_abb_t *nodo_reemplazo = NULL;
			nodo->izquierda= obtener_predecesor_inorder(nodo->izquierda, &nodo_reemplazo);
			nodo->elemento = nodo_reemplazo->elemento;
			free(nodo_reemplazo);
			(*tamanio)--;
			return nodo;
		}
		else{
			nodo_abb_t *nodo_aux = nodo;

			if(nodo->izquierda != NULL)
				nodo = nodo->izquierda;
			else if(nodo->derecha != NULL)
				nodo = nodo->derecha;
			else
				nodo = NULL;
			(*tamanio)--;
			free(nodo_aux);

			return nodo;
		}
	
	}

	if (comparacion < 0)
		nodo->izquierda = nodo_quitar(nodo->izquierda, elemento, comparador, elemento_quitado, tamanio);
	else nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador, elemento_quitado, tamanio);

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


size_t nodo_recorrer(nodo_abb_t *nodo, abb_recorrido recorrido, void **array, size_t tamanio_array, size_t elementos_recorridos)
{
	
	switch (recorrido){
	case INORDEN:
		if (nodo->izquierda)
			elementos_recorridos = nodo_recorrer(nodo->izquierda, recorrido, array, tamanio_array, elementos_recorridos);

		if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;

		array[elementos_recorridos] = nodo->elemento;
		(elementos_recorridos)++;

		if (nodo->derecha)
			elementos_recorridos = nodo_recorrer(nodo->derecha, recorrido, array, tamanio_array, elementos_recorridos);
		break;

	case PREORDEN:
		if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;

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
		if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;
		
		array[elementos_recorridos] = nodo->elemento;
		(elementos_recorridos)++;
		break; 
	default:
		break;
	}
	return elementos_recorridos;	
}