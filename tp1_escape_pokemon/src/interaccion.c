#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
struct interaccion *interaccion_crear_desde_string(const char *string)
{
	struct interaccion *interaccion_actual= malloc(sizeof(struct interaccion));
	char tipo_accion_actual;
	enum tipo_accion;

	sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", interaccion_actual->objeto, interaccion_actual->verbo,
	interaccion_actual->objeto_parametro, &tipo_accion_actual,interaccion_actual->accion.objeto,
	interaccion_actual->accion.mensaje
	);

	switch (tipo_accion_actual)
	{
	case 'd':
		interaccion_actual->accion.tipo=DESCUBRIR_OBJETO;
		break;
	case 'r':
		interaccion_actual->accion.tipo=REEMPLAZAR_OBJETO;
		break;
	case 'e':
		interaccion_actual->accion.tipo=ELIMINAR_OBJETO;
		break;
	case 'm':
		interaccion_actual->accion.tipo=DESCUBRIR_OBJETO;
		break;	
	default:
		break;
	}

	return interaccion_actual;
}
