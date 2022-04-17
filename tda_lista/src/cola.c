#include "cola.h"
#include "lista.h"

struct _cola_t {
	lista_t *lista;
}

cola_t *cola_crear()
{
	return NULL;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	//chequear que tope no sea igual a tamanio
	return NULL;
}

void *cola_desencolar(cola_t *cola)
{
	//chequear que tope no sea 0
	return NULL;
}

void *cola_frente(cola_t *cola)
{
	return NULL;
}

size_t cola_tamanio(cola_t *cola)
{
	return 0;
}

bool cola_vacia(cola_t *cola)
{
	//chequear si tope es 0
	return false;
}

void cola_destruir(cola_t *cola)
{

}
