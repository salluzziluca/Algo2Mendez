#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{	
	pila_t *pila = malloc(sizeof(pila_t));
	pila->lista = lista_crear();
	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
<<<<<<< HEAD
	if(pila == NULL)
		return NULL;
	lista_insertar(pila->lista, elemento);
	return pila;
	
}

void *pila_desapilar(pila_t *pila)
{	
	if(pila == NULL)
		return NULL;
	void *elemento_quitado = lista_quitar(pila->lista);
	return elemento_quitado;
=======
	return NULL;
}

void *pila_desapilar(pila_t *pila)
{
	return NULL;
>>>>>>> 3a34f7c107eba4fa210ccb52bc25da2349341006
}

void *pila_tope(pila_t *pila)
{
	if(pila == NULL)
		return NULL;
	void *ultimo_elemento = lista_ultimo(pila->lista);

	return ultimo_elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if(pila == NULL)
		return 0;
	size_t tamanio = lista_tamanio(pila->lista);
	return tamanio;
}

bool pila_vacia(pila_t *pila)
{
<<<<<<< HEAD
	if(pila->lista->cantidad == 0)
		return true;
	else
		return false;
=======
	return false;
>>>>>>> 3a34f7c107eba4fa210ccb52bc25da2349341006
}

void pila_destruir(pila_t *pila)
{	
	free(pila->lista);
	free(pila);
}
