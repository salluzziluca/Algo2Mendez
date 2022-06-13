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

par_t *llenar_par(const char *clave, void *elemento)
{
	par_t *par = malloc(sizeof(par_t));
	par->clave = clave;
	par->elemento = elemento;
	return par;
}

pares_t *par_insertar(pares_t *pares, par_t *par)
{
	if (pares == NULL)
		return NULL;

	if (pares->cantidad == 0) {
		pares->par_fin = par;
		pares->par_inicio = par;
		pares->cantidad++;
	} else {
		pares->par_fin->siguiente = par;
		pares->par_fin = par;
		pares->cantidad++;
	}
	return pares;
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
	par_t *par = llenar_par(clave, elemento);
	
	if(hash->pares[posicion].cantidad == 0){
	if(!par_insertar(&hash->pares[posicion], par))
		return NULL;
	hash->cantidad++;
	return hash;
	}

	for (size_t i = 0; i < hash->pares[posicion].cantidad; i++)
	{
		par_t *par_actual = hash->pares[posicion].par_inicio;
		if(strcmp(hash->pares[posicion].par_inicio->clave, clave) == 0)
		{
			*anterior = par_actual->elemento;
			par_actual->elemento = elemento;
			//TODO: ver como hacer para no tener que liberar este nodo
			free(par);
			return hash;
		}
		else{
			hash->pares[posicion].par_fin->siguiente = par;
			hash->pares[posicion].par_fin = par;
			hash->cantidad++;
			hash->pares[posicion].cantidad++;
			return hash;
		}
		par_actual = par_actual->siguiente;
	}
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	void *elemento_eliminado = NULL;
	pares_t lista_pares = hash->pares[posicion];

	for(size_t i = 0; i < lista_pares.cantidad; i++){

		if(strcmp(lista_pares.par_inicio->clave, clave) == 0){
		elemento_eliminado = lista_pares.par_inicio->elemento;	
		par_t *par_a_elminiar = lista_pares.par_inicio;
		lista_pares.par_inicio = par_a_elminiar->siguiente;
		free(par_a_elminiar);

		hash->pares->cantidad--;
		hash->cantidad--;
		}
		
	}
	
	return elemento_eliminado;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	pares_t lista_pares = hash->pares[posicion];
	for(size_t i = 0; i < lista_pares.cantidad; i++){
		if(strcmp(lista_pares.par_inicio->clave, clave) == 0)
			return lista_pares.par_inicio->elemento;
		lista_pares.par_inicio = hash->pares[posicion].par_inicio->siguiente;
	}
	return NULL;

}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return false;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	pares_t lista_pares = hash->pares[posicion];
	for(size_t i = 0; i < lista_pares.cantidad; i++){
		if(lista_pares.par_inicio->clave != NULL && strcmp(lista_pares.par_inicio->clave, clave) == 0)
			return true;
		lista_pares.par_inicio = hash->pares[posicion].par_inicio->siguiente;
	}
	return false;
}
size_t hash_cantidad(hash_t *hash)
{
	if(!hash)
		return 0;
	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	if(!hash)
		return;
	for(size_t i = 0; i < hash->capacidad; i++){
		for(size_t j = 0; j < hash->pares[i].cantidad; j++){
			par_t *uxiliar = hash->pares[i].par_inicio->siguiente;
			free(hash->pares[i].par_inicio);
			hash->pares[i].par_inicio = uxiliar;
		}
	}
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
	if(!hash || !f)
		return 0;
	size_t cantidad_claves_iteradas = 0;
	for (size_t i = 0; i < hash->capacidad; i++)
	{
		par_t *par_actual = hash->pares[i].par_inicio;
		int j = 0;
		bool continuar = true;
		while(continuar && j < hash->pares[i].cantidad){
			continuar = f(par_actual->clave, par_actual->elemento, aux);
			cantidad_claves_iteradas++;
			j++;
			par_actual = par_actual->siguiente;
		}
	}
	return cantidad_claves_iteradas;
}

hash_t *rehash(hash_t *hash, size_t capacidad)
{
	//BUG: esta funcion se deberia aplicar cuando llegamos al 75% de la capacidad
	//TODO: mirar ultimos minutos de la clase del 2 de junio
	return hash;
}