#ifndef __ESTRUCTURA_HASH_H__
#define __ESTRUCTURA_HASH_H__
#include <stdio.h>
#include "hash.h"
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
struct hash {
	size_t capacidad;
	size_t ocupados;
	posiciones_t *posiciones;	
};

#endif /*__ESTRUCTURA_HASH.H__*/