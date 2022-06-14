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

char *copiar_string(const char *origen) {
	char *copia = malloc(strlen(origen) + 1);
	strcpy(copia, origen);
	return copia;
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
	hash->ocupados = 0;
	return hash;
}

par_t *llenar_par(char *clave, void *elemento)
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

	if (pares->ocupados == 0) {
		pares->par_fin = par;
		pares->par_inicio = par;
		pares->ocupados++;
	} else {
		pares->par_fin->siguiente = par;
		pares->par_fin = par;
		pares->ocupados++;
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

	int i = 0;
	bool hay_que_sobreescribir = false;
	bool sobreescrito = false;
	if(hash->pares[posicion].ocupados != 0)
		hay_que_sobreescribir = hash_contiene(hash, clave);
	par_t *par_actual = hash->pares[posicion].par_inicio;

	while(hay_que_sobreescribir && i < hash->pares[posicion].ocupados && !sobreescrito)
	{
		if(strcmp(par_actual->clave, clave) == 0)
		{
			*anterior = par_actual->elemento;
			par_actual->elemento = elemento;
			sobreescrito = true;
		}
		i++;
		par_actual = par_actual->siguiente;
	}
	if(!sobreescrito){
		char *copia_clave = copiar_string(clave);
		par_t *par = llenar_par(copia_clave, elemento);
		par_insertar(&hash->pares[posicion], par);
		hash->ocupados++;
	}
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	void *elemento_eliminado = NULL;

	if( hash->pares[posicion].ocupados == 1){
		if(strcmp(hash->pares[posicion].par_inicio->clave, clave) == 0){
			par_t *par_eliminado =  hash->pares[posicion].par_inicio;
			elemento_eliminado = par_eliminado->elemento;
			hash->pares[posicion].par_inicio = NULL;
			hash->pares[posicion].par_fin = NULL;
			hash->pares[posicion].ocupados = 0;
			free(par_eliminado->clave);
			free(par_eliminado);

			hash->ocupados--;
			return elemento_eliminado;
		}
	}

	int i = 0;
	bool eliminado = false;
	while (i < hash->pares[posicion].ocupados && eliminado == false) {

		if(strcmp(hash->pares[posicion].par_inicio->siguiente->clave, clave) == 0){
			par_t *par_anterior = hash->pares[posicion].par_inicio;
			par_t *par_a_elminiar =par_anterior->siguiente;
			elemento_eliminado = par_a_elminiar->elemento;	
			par_anterior->siguiente = par_a_elminiar->siguiente;
			free(par_a_elminiar->clave);
			free(par_a_elminiar);

			hash->pares->ocupados--;
			hash->ocupados--;
			eliminado = true;
		}
		i++;
		hash->pares[posicion].par_inicio = hash->pares[posicion].par_inicio->siguiente;
		
	}
	
	return elemento_eliminado;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->pares[posicion].par_inicio;

	for(size_t i = 0; i < hash->pares[posicion].ocupados; i++){
		if(par_actual->clave != NULL && strcmp(par_actual->clave, clave) == 0)
			return par_actual->elemento;
		par_actual =par_actual->siguiente;
	}

	return NULL;

}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return false;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->pares[posicion].par_inicio;

	for(size_t i = 0; i < hash->pares[posicion].ocupados; i++){
		if(par_actual->clave != NULL && strcmp(par_actual->clave, clave) == 0)
			return true;
		par_actual = par_actual->siguiente;
	}
	
	return false;
}
size_t hash_cantidad(hash_t *hash)
{
	if(!hash)
		return 0;
	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if(!hash)
		return;
	for (size_t i = 0; i < hash->capacidad; i++)
	{
		for(size_t j = 0; j < hash->pares[i].ocupados; j++){
			par_t *uxiliar = hash->pares[i].par_inicio->siguiente;
			if(destructor != NULL)
				destructor(hash->pares[i].par_inicio->elemento);
			free(hash->pares[i].par_inicio->clave);
			free(hash->pares[i].par_inicio);
			hash->pares[i].par_inicio = uxiliar;
		}
	}
	free(hash->pares);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if(!hash || !f)
		return 0;

	size_t ocupados_claves_iteradas = 0;
	
	for (size_t i = 0; i < hash->capacidad; i++)
	{
		par_t *par_actual = hash->pares[i].par_inicio;
		int j = 0;
		bool continuar = true;

		while(continuar && j < hash->pares[i].ocupados){
			continuar = f(par_actual->clave, par_actual->elemento, aux);
			ocupados_claves_iteradas++;
			j++;
			par_actual = par_actual->siguiente;
		}
	}
	return ocupados_claves_iteradas;
}

hash_t *rehash(hash_t *hash, size_t capacidad)
{
	//BUG: esta funcion se deberia aplicar cuando llegamos al 75% de la capacidad
	//TODO: mirar ultimos minutos de la clase del 2 de junio
	return hash;
}