#include "hash.h"

struct hash {
	int a;
};

hash_t *hash_crear(size_t capacidad)
{
	return NULL;
}


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	// fijarme primero si me voy a pasar. Si me paso, rehasear y despues insertar
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	return 0;
}

void hash_destruir(hash_t *hash)
{
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
	//esta funcion se deberia aplicar cuando llegamos al 75% de la capacidad
	//mirar ultimos minutos de la clase del 2 de junio
	return hash;
}