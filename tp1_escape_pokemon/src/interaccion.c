#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LARGO_MAX_BOOL 15
int validar_y_agregar_campos(char *campo_actual, char valor_aux[MAX_NOMBRE], struct interaccion *interaccion_actual)
	{
		if(campo_actual!=NULL)
		{
			strcpy(valor_aux,campo_actual);
			return 1;
		}
		else
		{
			return 0;
		}
	}
struct interaccion *interaccion_crear_desde_string(const char *string)
{
	struct interaccion *interaccion_actual= malloc(sizeof(struct interaccion));
	


	char objeto_aux[MAX_NOMBRE];
	char verbo_aux[MAX_NOMBRE];
	char objeto_parametro_aux[MAX_NOMBRE];
	char tipo_accion_actual;
	char accion_objeto_aux[MAX_NOMBRE];
	char accion_mensaje_aux[MAX_TEXTO];

	sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", objeto_aux, verbo_aux, objeto_parametro_aux, &tipo_accion_actual, accion_objeto_aux, accion_mensaje_aux);

	validar_y_agregar_campos(objeto_aux, interaccion_actual->objeto, interaccion_actual);
	validar_y_agregar_campos(verbo_aux, interaccion_actual->verbo, interaccion_actual);
	validar_y_agregar_campos(objeto_parametro_aux, interaccion_actual->objeto_parametro, interaccion_actual);
	
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

	validar_y_agregar_campos(accion_objeto_aux, interaccion_actual->accion.objeto, interaccion_actual);
	validar_y_agregar_campos(accion_mensaje_aux, interaccion_actual->accion.mensaje, interaccion_actual);

	return interaccion_actual;
}
