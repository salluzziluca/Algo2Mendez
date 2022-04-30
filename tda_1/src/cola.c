#include "cola.h"
#include "lista.h"

struct _cola_t {
	lista_t *lista;
};

cola_t *cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));
	cola->lista = lista_crear();
	return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if(cola == NULL)
		return NULL;
	lista_insertar(cola->lista, elemento);
	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if(cola == NULL)
		return NULL;
	void *elemento_quitado = lista_quitar_de_posicion(cola->lista, 0);
	return elemento_quitado;

}

void *cola_frente(cola_t *cola)
{
	void *primer_elemento = lista_primero(cola->lista);
	return primer_elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio(cola->lista);
}

bool cola_vacia(cola_t *cola)
{
	bool esta_vacia = lista_vacia(cola->lista);
	return esta_vacia;
}

void cola_destruir(cola_t *cola)
{
	free(cola->lista);
	free(cola);
}
