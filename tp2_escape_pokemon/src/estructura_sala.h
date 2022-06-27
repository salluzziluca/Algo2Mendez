#ifndef ESTRUCTURA_SALA_H
#define ESTRUCTURA_SALA_H
#include "hash.h"

typedef struct jugador
{
	hash_t *objetos_conocidos;
	size_t cantidad_objetos_conocidos;
	hash_t *objetos_poseidos;
	size_t cantidad_objetos_poseidos;
} jugador_t;

struct sala {
	hash_t *objetos;
	size_t cantidad_objetos;
	hash_t *interacciones;
	size_t cantidad_interacciones;
	jugador_t *jugador;
};


#endif // ESTRUCTURA_SALA_H