#include "hash.h"
#include <stdlib.h>
#include <string.h>
#define FACTOR_DE_CARGA_MAXIMO 0.75


int funcion_hash(const char *clave) {
	int i = 0;
	int suma = 0;
	while (clave[i] != '\0') {
		suma += clave[i];
		i++;
	}
	return suma;
}

hash_t *hash_crear(size_t capacidad)
{	
	hash_t *hash = malloc(sizeof(hash_t));
	if(!hash)
		return NULL;
	if (capacidad < 3)
		capacidad = 3;
	hash->pares = calloc(capacidad, sizeof(pares_t));
	if(!hash->pares)
		return NULL;
	hash->capacidad = capacidad;
	hash->cantidad = 0;
	return hash;
}

pares_t llenar_par(const char *clave, void *elemento)
{
	pares_t par;
	par.clave = clave;
	par.elemento = elemento;
	return par;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if(!hash || !clave)
		return NULL;
	//TODO: fijarme primero si me voy a pasar. Si me paso, rehasear y despues insertar
	if(hash_cantidad(hash) >= (double)hash->capacidad *FACTOR_DE_CARGA_MAXIMO)
		return NULL;
		//TODO: return rehash(hash);

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	//TODO: Si la posicion esta ocupada y no es la misma clave, colisionar con lista
	if(hash->pares[posicion].clave){
		*anterior = hash->pares[posicion].elemento;
		hash->pares[posicion] = llenar_par(clave, elemento);
	}
	else{
		hash->pares[posicion] = llenar_par(clave, elemento);
		hash->cantidad++;
	}
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	if(!hash->pares[posicion].clave)
		return NULL;
	void *elemento = hash->pares[posicion].elemento;
	hash->pares[posicion].clave = NULL;
	hash->pares[posicion].elemento = NULL;
	hash->cantidad--;
	return elemento;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	if(!hash->pares[posicion].clave)
		return NULL;
	return hash->pares[posicion].elemento;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return false;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	if(!hash->pares[posicion].clave)
		return false;
	return true;
}

size_t hash_cantidad(hash_t *hash)
{
	if(!hash)
		return 0;
	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	free(hash->pares);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{

}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}

hash_t *rehash(hash_t *hash, size_t capacidad)
{
	//BUG: esta funcion se deberia aplicar cuando llegamos al 75% de la capacidad
	//TODO: mirar ultimos minutos de la clase del 2 de junio
	return hash;
}