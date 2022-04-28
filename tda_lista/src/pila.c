#include "pila.h"
#include "lista.h"
struct _pila_t {
	lista_t *lista;
};

pila_t *pila_crear()
{	
	pila_t *pila = malloc(sizeof(pila_t));
	pila->lista = lista_crear();
	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	//TODO: agregar restrciciones
	if(pila == NULL)
		return NULL;
	lista_insertar(pila->lista, elemento);

	//Fijarme si tope se estas acercando mucho a tamanio, en ese caso, damos mas memoria. Propongo un 75%
	// estoy de acuerdo, 75% me parece bien
	//Yo prefiero 50
	//75% es una buena idea
	//50% es una buena idea
	// 25% es una buena idea
	//QUE 
	return pila;
	
}

void *pila_desapilar(pila_t *pila)
{	
	//TODO: agregar restricciones
	if(pila == NULL)
		return NULL;
	void *elemento_quitado = lista_quitar(pila->lista);
	//Fijarme si tope ==0
	return elemento_quitado;
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
	//TODO: arreglar el bug por el que si le pongo == 0 no funciona
	if(pila->lista->cantidad == 0)
		return true;
	else
		return false;
}

void pila_destruir(pila_t *pila)
{	
	free(pila->lista);
	free(pila);
}
