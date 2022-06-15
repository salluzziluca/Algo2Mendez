#ifndef __ESTRUCTURA_HASH_H__
#define __ESTRUCTURA_HASH_H__
#include <stdio.h>

typedef struct par{
	char *clave;
	void *elemento;
	struct par *siguiente;
}par_t;

typedef struct posiciones{
	par_t *par_inicio;
	par_t *par_fin;
	size_t ocupados;
}posiciones_t;
typedef struct hash {
	size_t capacidad;
	size_t ocupados;
	posiciones_t *posiciones;	
}hash_t;

#endif /*__ESTRUCTURA_HASH.H__*/