#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX_ENUM 2
struct interaccion *interaccion_crear_desde_string(const char *string)
{
	struct interaccion *interaccion_actual= malloc(sizeof(struct interaccion));
	char valor_enum[MAX_ENUM];
	sscanf(string,"%[^;];%[^;];%[^;];%[^:]:%[^:]:%[^\n]\n", interaccion_actual->objeto, interaccion_actual->verbo,
	interaccion_actual->objeto_parametro, valor_enum,interaccion_actual->accion.objeto,
	interaccion_actual->accion.mensaje
	);
	int valor_enum_int=(int)valor_enum[0];
	
	return NULL;
}
