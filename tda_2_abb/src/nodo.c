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
		
		if(nodo->izquierda != NULL || (nodo->izquierda != NULL && nodo->derecha != NULL)){
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

void *obtener_predecesor_inorder(nodo_abb_t *nodo, nodo_abb_t **nodo_reemplazo)
{
	if(nodo->derecha == NULL){
		*nodo_reemplazo = nodo;
		return nodo->izquierda;
	}
	nodo->derecha = obtener_predecesor_inorder(nodo->derecha, nodo_reemplazo);
	return nodo;
}

bool inorder_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos){
	if(!nodo)
		return true;
		
	if(inorder_con_cada_elemento(nodo->izquierda, funcion, aux, elementos_recorridos)== false)
		return false;

	(*elementos_recorridos)++;
	if (!funcion(nodo->elemento, aux))
		return false;
	
	if(inorder_con_cada_elemento(nodo->derecha, funcion, aux, elementos_recorridos) == false)
		return false;
	return true;
}

bool preorder_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos){

	if(!nodo)
		return true;

	(*elementos_recorridos)++;
	if (!funcion(nodo->elemento, aux))
			return false;
	if(preorder_con_cada_elemento(nodo->izquierda, funcion, aux, elementos_recorridos) == false)
		return false;
	if(preorder_con_cada_elemento(nodo->derecha, funcion, aux, elementos_recorridos) == false)
		return false;
	return true;
}


bool postorden_con_cada_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos)
{
	if(!nodo)
		return true;
			
	if(postorden_con_cada_elemento(nodo->izquierda, funcion, aux, elementos_recorridos) == false)
		return false;

	if(postorden_con_cada_elemento(nodo->derecha, funcion, aux, elementos_recorridos) == false)
		return false;
	
	(*elementos_recorridos)++;

	if (!funcion(nodo->elemento, aux))
		return false;

	return true;
}





bool nodo_con_cada_elemento(nodo_abb_t *nodo, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux, size_t *elementos_recorridos)
{
	switch (recorrido){
	case INORDEN:

		inorder_con_cada_elemento(nodo, funcion, aux, elementos_recorridos);
		break;

	case PREORDEN:
		
		preorder_con_cada_elemento(nodo, funcion, aux, elementos_recorridos);

		break;

	case POSTORDEN:
		
		postorden_con_cada_elemento(nodo, funcion, aux, elementos_recorridos);

		break;

	default:
		break;
	}
	return true;		
}

size_t inorder_recorrer(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t elementos_recorridos)
{
	if (nodo->izquierda)
		elementos_recorridos = inorder_recorrer(nodo->izquierda, array, tamanio_array, elementos_recorridos);

	if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;

	array[elementos_recorridos] = nodo->elemento;
	(elementos_recorridos)++;

	if (nodo->derecha)
		elementos_recorridos = inorder_recorrer(nodo->derecha, array, tamanio_array, elementos_recorridos);
	return elementos_recorridos;
}

size_t preorder_recorrer(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t elementos_recorridos)
{

	if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;

	array[elementos_recorridos] = nodo->elemento;
	(elementos_recorridos)++;
	
	if (nodo->izquierda)
		elementos_recorridos = preorder_recorrer(nodo->izquierda, array, tamanio_array, elementos_recorridos);

	if (nodo->derecha)
		elementos_recorridos = preorder_recorrer(nodo->derecha, array, tamanio_array, elementos_recorridos);
	
	return elementos_recorridos;
}

size_t postorder_recorrer(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t elementos_recorridos)
{
	if (nodo->izquierda)
		elementos_recorridos = postorder_recorrer(nodo->izquierda, array, tamanio_array, elementos_recorridos);

	if (nodo->derecha)
		elementos_recorridos = postorder_recorrer(nodo->derecha, array, tamanio_array, elementos_recorridos);
	if(elementos_recorridos >= tamanio_array)
		return elementos_recorridos;
	
	array[elementos_recorridos] = nodo->elemento;
	(elementos_recorridos)++;
	return elementos_recorridos;
}

size_t nodo_recorrer(nodo_abb_t *nodo, abb_recorrido recorrido, void **array, size_t tamanio_array, size_t elementos_recorridos)
{
	
	switch (recorrido){
	case INORDEN:
		elementos_recorridos = inorder_recorrer(nodo, array, tamanio_array, elementos_recorridos);
		break;

	case PREORDEN:
		elementos_recorridos = preorder_recorrer(nodo, array, tamanio_array, elementos_recorridos);
		break;

	case POSTORDEN:
		elementos_recorridos = postorder_recorrer(nodo, array, tamanio_array, elementos_recorridos);
		break; 
	default:
		break;
	}
	return elementos_recorridos;	
}