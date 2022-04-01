#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#define LARGO_MAX_NOMBRE 20
#define LARGO_MAX_DESCRIPCION 100

struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto;
	//TODO:ver por que tira segfault
	sscanf(string,"%[^;];%[^;];",objeto->nombre, objeto->descripcion);
	return objeto;
}
