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

	char objeto_aux[MAX_NOMBRE]= "\0";
	char verbo_aux[MAX_NOMBRE] = "\0";
	char objeto_parametro_aux[MAX_NOMBRE] = "\0";
	char tipo_accion_actual = '\0';
	char accion_objeto_aux[MAX_NOMBRE] = "\0";
	char accion_mensaje_aux[MAX_TEXTO] = "\0";



	if(string == NULL || strcmp(string, "\0")==0){
		strcpy(interaccion_actual->objeto,"\0");
		strcpy(interaccion_actual->verbo,"\0");
		strcpy(interaccion_actual->objeto_parametro,"\0");
		interaccion_actual->accion.tipo = -1;
		strcpy(interaccion_actual->accion.objeto,"\0");
		strcpy(interaccion_actual->accion.mensaje,"\0");
	}
	else{
		sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", objeto_aux, verbo_aux, objeto_parametro_aux, &tipo_accion_actual, accion_objeto_aux, accion_mensaje_aux);

		validar_y_agregar_campos_interaccion(objeto_aux, interaccion_actual->objeto, interaccion_actual);
		validar_y_agregar_campos_interaccion(verbo_aux, interaccion_actual->verbo, interaccion_actual);
		validar_y_agregar_campos_interaccion(objeto_parametro_aux, interaccion_actual->objeto_parametro, interaccion_actual);
		
		switch (tipo_accion_actual){
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
			interaccion_actual->accion.tipo=-1;
			break;
		}

		validar_y_agregar_campos_interaccion(accion_objeto_aux, interaccion_actual->accion.objeto, interaccion_actual);
		validar_y_agregar_campos_interaccion(accion_mensaje_aux, interaccion_actual->accion.mensaje, interaccion_actual);
	}

	return interaccion_actual;
}
