#include "estructura_hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define FACTOR_DE_CARGA_MAXIMO 0.65



uint32_t funcion_hash(const char *clave) {
	uint32_t hash = 5381;
	uint8_t c;

	while ((c = (uint8_t) *clave++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}
/*
* Recibe un string, devuelve una copia del mismo reservado en memoria
*/
char *copiar_string(const char *origen) {
	if (origen == NULL)
		return NULL;

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

	hash->tabla = calloc(capacidad, sizeof(tabla_t));
	if(!hash->tabla)
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

tabla_t *par_insertar(tabla_t *tabla, par_t *par)
{
	if (tabla == NULL)
		return NULL;

	if (tabla->ocupados == 0) {
		tabla->par_fin = par;
		tabla->par_inicio = par;
		tabla->ocupados++;
	} else {
		tabla->par_fin->siguiente = par;
		tabla->par_fin = par;
		tabla->ocupados++;
	}
	return tabla;
}
void *recorrer_reinsertando(hash_t *hash, size_t capacidad, tabla_t *tabla_aux)
{
	if (hash == NULL)
		return NULL;
	for(size_t i = 0; i < hash->capacidad; i++){
		for (size_t j = 0; j <hash->tabla[i].ocupados; j++) {

			size_t posicion = (size_t)funcion_hash(hash->tabla[i].par_inicio->clave) % capacidad;
			par_t *par_aux = hash->tabla[i].par_inicio->siguiente;
			par_insertar(&tabla_aux[posicion], hash->tabla[i].par_inicio);
			hash->tabla[i].par_inicio = par_aux;

		}

	}
	return hash;
}

hash_t *rehash(hash_t *hash, size_t capacidad)
{
	if(!hash)
		return NULL;

	tabla_t *tabla_aux = calloc(capacidad, sizeof(tabla_t));
	if(!tabla_aux)
		return NULL;

	void *recorrer = recorrer_reinsertando(hash, capacidad, tabla_aux);
	if(!recorrer) //TODO: fijarse si esto vale la pena o es al pepe
		return NULL;

	free(hash->tabla);	
	hash->tabla = tabla_aux;	
	hash->capacidad = capacidad;
	
	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if(!hash || !clave)
		return NULL;

	if(hash_cantidad(hash) >= (double)hash->capacidad *FACTOR_DE_CARGA_MAXIMO)
		hash = rehash(hash, hash->capacidad * 2);

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	int i = 0;
	bool sobreescrito = false;
	par_t *par_actual = hash->tabla[posicion].par_inicio;

	while(i < hash->tabla[posicion].ocupados && !sobreescrito)
	{
		if(strcmp(par_actual->clave, clave) == 0)
		{
			if(anterior )
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

		par_insertar(&hash->tabla[posicion], par);
		if(anterior)
			*anterior = NULL;
			
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

	if(hash->tabla[posicion].ocupados == 1){
		if(strcmp(hash->tabla[posicion].par_inicio->clave, clave) == 0){
			par_t *par_eliminado =  hash->tabla[posicion].par_inicio;
			elemento_eliminado = par_eliminado->elemento;
			hash->tabla[posicion].par_inicio = NULL;
			hash->tabla[posicion].par_fin = NULL;
			hash->tabla[posicion].ocupados = 0;

			free(par_eliminado->clave);
			free(par_eliminado);
			hash->ocupados--;
			return elemento_eliminado;
		}
	}

	if(hash->tabla[posicion].ocupados > 0 && strcmp(hash->tabla[posicion].par_inicio->clave, clave) == 0){
		par_t *par_eliminado =  hash->tabla[posicion].par_inicio;
		elemento_eliminado = par_eliminado->elemento;
		hash->tabla[posicion].par_inicio =par_eliminado->siguiente;
		hash->tabla[posicion].ocupados--;
		free(par_eliminado->clave);
		free(par_eliminado);
		hash->ocupados--;
		return elemento_eliminado;
	}
	int i = 0;
	bool eliminado = false;
	while (i < hash->tabla[posicion].ocupados && eliminado == false) {

		if(strcmp(hash->tabla[posicion].par_inicio->siguiente->clave, clave) == 0){
			par_t *par_anterior = hash->tabla[posicion].par_inicio;
			par_t *par_a_elminiar =par_anterior->siguiente;
			elemento_eliminado = par_a_elminiar->elemento;	
			par_anterior->siguiente = par_a_elminiar->siguiente;
			free(par_a_elminiar->clave);
			free(par_a_elminiar);

			hash->tabla[posicion].ocupados--;
			hash->ocupados--;
			eliminado = true;
		if(i == 0)
			hash->tabla[posicion].par_fin = par_anterior;
		}
		if(!eliminado){
			i++;
			hash->tabla[posicion].par_inicio->siguiente = hash->tabla[posicion].par_inicio->siguiente;
		}
	}
	
	return elemento_eliminado;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return NULL;

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->tabla[posicion].par_inicio;
	void *elemento = NULL;
	bool obtenido = false;
	int i = 0;

	while (i < hash->tabla[posicion].ocupados && !obtenido) {
		if(strcmp(par_actual->clave, clave) == 0){
			obtenido = true;
			elemento = par_actual->elemento;
		}
		i++;
		par_actual = par_actual->siguiente;
	}
	return elemento;

}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash || !clave)
		return false;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->tabla[posicion].par_inicio;
	bool contiene = false;
	int i = 0;

	while (i < hash->tabla[posicion].ocupados && !contiene) {
		if(strcmp(par_actual->clave, clave) == 0)
			contiene = true;
		i++;
		par_actual = par_actual->siguiente;
	}

	return contiene;
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
	for (size_t i = 0; i < hash->capacidad; i++){
		for(size_t j = 0; j < hash->tabla[i].ocupados; j++){
			par_t *uxiliar = hash->tabla[i].par_inicio->siguiente;
			if(destructor )
				destructor(hash->tabla[i].par_inicio->elemento);
			free(hash->tabla[i].par_inicio->clave);
			free(hash->tabla[i].par_inicio);
			hash->tabla[i].par_inicio = uxiliar;
		}
	}
	free(hash->tabla);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if(!hash || !f)
		return 0;

	size_t claves_iteradas = 0;
		bool continuar = true;
	
	for (size_t i = 0; i < hash->capacidad; i++)
	{
		par_t *par_actual = hash->tabla[i].par_inicio;
		int j = 0;

		while(continuar && j < hash->tabla[i].ocupados){
			continuar = f(par_actual->clave, par_actual->elemento, aux);
			claves_iteradas++;
			j++;
			par_actual = par_actual->siguiente;
	
		}
	}
	return claves_iteradas;
}
