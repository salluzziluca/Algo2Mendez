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
	if(pila == NULL)
		return NULL;
	lista_insertar_en_posicion(pila->lista, elemento,0);
	return pila;
	
}

void *pila_desapilar(pila_t *pila)
{	
	if(pila == NULL)
		return NULL;
	void *elemento_quitado = lista_quitar_de_posicion(pila->lista, 0);
	return elemento_quitado;
}

void *pila_tope(pila_t *pila)
{
	if(pila == NULL)
		return NULL;
	void *ultimo_elemento = lista_primero(pila->lista);

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
