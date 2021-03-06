#include "estructuras.h"
#include "interaccion.h"
#include "validaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BOOL 20

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	struct interaccion *interaccion_actual= malloc(sizeof(struct interaccion));

	char objeto_aux[MAX_NOMBRE] = "\0";
	char verbo_aux[MAX_NOMBRE] = "\0";
	char objeto_parametro_aux[MAX_NOMBRE] = "\0";
	char tipo_accion_actual = '\0';
	char accion_objeto_aux[MAX_NOMBRE] = "\0";
	char accion_mensaje_aux[MAX_TEXTO] = "\0";

	if(string==NULL || strcmp(string, "\0") == 0){
		free(interaccion_actual);
		return NULL;
	}

	else{
		int leidos = sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", objeto_aux, verbo_aux, objeto_parametro_aux, &tipo_accion_actual, accion_objeto_aux, accion_mensaje_aux);

		if(leidos != 6){
			free(interaccion_actual);
			return NULL;
		}

		strcpy(interaccion_actual->objeto, objeto_aux);
		strcpy(interaccion_actual->verbo, verbo_aux);

		if(strcmp(objeto_parametro_aux, "_") == 0)
			strcpy(interaccion_actual->objeto_parametro, "");
		else
			strcpy(interaccion_actual->objeto_parametro, objeto_parametro_aux);
		
		switch (tipo_accion_actual){
		case 'd':
			interaccion_actual->accion.tipo = DESCUBRIR_OBJETO;
			break;
		case 'r':
			interaccion_actual->accion.tipo = REEMPLAZAR_OBJETO;
			break;
		case 'e':
			interaccion_actual->accion.tipo = ELIMINAR_OBJETO;
			break;
		case 'm':
			interaccion_actual->accion.tipo = MOSTRAR_MENSAJE;
			break;	
		default:
			interaccion_actual->accion.tipo = 0;
			break;
		}

		if(strcmp(accion_objeto_aux,"_") == 0)
			strcpy(interaccion_actual->accion.objeto, "");
		else
			strcpy(interaccion_actual->accion.objeto, accion_objeto_aux);

		strcpy(interaccion_actual->accion.mensaje, accion_mensaje_aux);
	}

	return interaccion_actual;
}
