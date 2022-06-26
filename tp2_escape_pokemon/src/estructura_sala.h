#ifndef ESTRUCTURA_SALA_H
#define ESTRUCTURA_SALA_H
#include "hash.h"
struct sala {
	hash_t *objetos;
	size_t cantidad_objetos;
	hash_t *interacciones;
	size_t cantidad_interacciones;
};
#endif // ESTRUCTURA_SALA_H