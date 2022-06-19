#include "estructura_hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define FACTOR_DE_CARGA_MAXIMO 0.65

uint32_t funcion_hash(const char *clave)
{
	uint32_t hash = 5381;
	uint8_t c;

	while ((c = (uint8_t)*clave++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}

/*
* Recibe un string, devuelve una copia del mismo reservado en memoria o NULL en caso de error. 
*/
char *copiar_string(const char *origen)
{
	if (origen == NULL)
		return NULL;

	char *copia = malloc(strlen(origen) + 1);
	strcpy(copia, origen);

	return copia;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;

	if (capacidad < 3)
		capacidad = 3;

	hash->tabla = calloc(capacidad, sizeof(tabla_t));
	if (!hash->tabla)
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

/*
* Recibe un hash valido, una capacidad y una tabla de hash auxiliar
* Reorganiza los elementos del hash original asignandole nuevas posiciones en funcion
* de la capacidad de la nueva tabla y los inserta en la susodicha. 
*/
void recorrer_reinsertando(hash_t *hash, size_t capacidad, tabla_t *tabla_aux)
{
	for (size_t i = 0; i < hash->capacidad; i++) {
		for (size_t j = 0; j < hash->tabla[i].ocupados; j++) {
			size_t posicion =
				(size_t)funcion_hash(
					hash->tabla[i].par_inicio->clave) %
				capacidad;
			par_t *par_aux = hash->tabla[i].par_inicio->siguiente;

			par_insertar(&tabla_aux[posicion],
				     hash->tabla[i].par_inicio);

			hash->tabla[i].par_inicio = par_aux;
		}
	}
}

/*
* Recibe un hash. Crea una nueva tabla con el doble de capacidad del hash original 
* y reinserta los elementos del hash original en la nueva tabla.
* Devuelve el hash reorganizado o NULL en caso de error.
*/
hash_t *rehash(hash_t *hash, size_t capacidad)
{
	if (!hash)
		return NULL;

	tabla_t *tabla_aux = calloc(capacidad, sizeof(tabla_t));
	if (!tabla_aux)
		return NULL;

	recorrer_reinsertando(hash, capacidad, tabla_aux);

	free(hash->tabla);
	hash->tabla = tabla_aux;
	hash->capacidad = capacidad;

	return hash;
}

/*
* Recibe una posicion de una tabla de hash, una clave, un elemento para sobreescribir y un puntero a elemento anterior.
* itera por la lista de la posicion correspondiente buscando un para con la misma clave.
* Si encuentra un par con la misma clave, sobreescribe el elemento.
* Devuelve true si sobreescribió el elemento o false si no lo hizo.
*/
bool sobreescribir_elemento(tabla_t *tabla, const char *clave, void *elemento,
			    void **anterior)
{
	int i = 0;
	bool sobreescrito = false;
	par_t *par_actual = tabla->par_inicio;
	while (i < tabla->ocupados && !sobreescrito) {
		if (strcmp(par_actual->clave, clave) == 0) {
			if (anterior)
				*anterior = par_actual->elemento;
			par_actual->elemento = elemento;
			sobreescrito = true;
		}
		i++;
		par_actual = par_actual->siguiente;
	}
	return sobreescrito;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	if (hash_cantidad(hash) >=
	    (double)hash->capacidad * FACTOR_DE_CARGA_MAXIMO)
		hash = rehash(hash, hash->capacidad * 2);

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	bool sobreescrito = sobreescribir_elemento(&hash->tabla[posicion],
						   clave, elemento, anterior);

	if (!sobreescrito) {
		char *copia_clave = copiar_string(clave);
		par_t *par = llenar_par(copia_clave, elemento);

		par_insertar(&hash->tabla[posicion], par);
		if (anterior)
			*anterior = NULL;

		hash->ocupados++;
	}
	return hash;
}

/*
* Recibe una posicion de la tabla, y un puntero a elemento eliminado
* Elimina el elemento de la posicion correspondiente, asigna los punteros
* inicio y fin a nulo y disminuye ocupados a cero. 
* Libera la calve y el par eliminado y devuelve el elemento.
*/
void *quitar_con_cantidad_uno(tabla_t *tabla, void *elemento_eliminado)
{
	par_t *par_eliminado = tabla->par_inicio;
	elemento_eliminado = par_eliminado->elemento;
	tabla->par_inicio = NULL;
	tabla->par_fin = NULL;
	tabla->ocupados = 0;
	free(par_eliminado->clave);
	free(par_eliminado);
	return elemento_eliminado;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	void *elemento_eliminado = NULL;

	if (hash->tabla[posicion].ocupados == 1) {
		elemento_eliminado = quitar_con_cantidad_uno(
			&hash->tabla[posicion], elemento_eliminado);
		hash->ocupados--;
	}

	par_t *par_actual = hash->tabla[posicion].par_inicio;
	par_t *par_anterior = NULL;
	int i = 0;
	while (i < hash->tabla[posicion].ocupados && !elemento_eliminado) {
		if (strcmp(par_actual->clave, clave) == 0) {
			elemento_eliminado = par_actual->elemento;
			if (par_anterior)
				par_anterior->siguiente = par_actual->siguiente;
			else
				hash->tabla[posicion].par_inicio =
					par_actual->siguiente;
			hash->tabla[posicion].ocupados--;
			free(par_actual->clave);
			free(par_actual);
			hash->ocupados--;
		}
		if (!elemento_eliminado) {
			i++;
			par_anterior = par_actual;
			par_actual = par_actual->siguiente;
		}
	}
	return elemento_eliminado;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->tabla[posicion].par_inicio;
	void *elemento = NULL;
	int i = 0;

	while (i < hash->tabla[posicion].ocupados && !elemento) {
		if (strcmp(par_actual->clave, clave) == 0) {
			elemento = par_actual->elemento;
		}
		i++;
		par_actual = par_actual->siguiente;
	}
	return elemento;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;
	size_t posicion = (size_t)funcion_hash(clave) % hash->capacidad;
	par_t *par_actual = hash->tabla[posicion].par_inicio;
	bool contiene = false;
	int i = 0;

	while (i < hash->tabla[posicion].ocupados && !contiene) {
		if (strcmp(par_actual->clave, clave) == 0)
			contiene = true;
		i++;
		par_actual = par_actual->siguiente;
	}

	return contiene;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		for (size_t j = 0; j < hash->tabla[i].ocupados; j++) {
			par_t *uxiliar = hash->tabla[i].par_inicio->siguiente;
			if (destructor)
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
	if (!hash || !f)
		return 0;

	size_t claves_iteradas = 0;
	bool continuar = true;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *par_actual = hash->tabla[i].par_inicio;
		int j = 0;

		while (continuar && j < hash->tabla[i].ocupados) {
			continuar =
				f(par_actual->clave, par_actual->elemento, aux);
			claves_iteradas++;
			j++;
			par_actual = par_actual->siguiente;
		}
	}
	return claves_iteradas;
}
