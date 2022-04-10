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

	if(string==NULL || strcmp(string, "\0") == 0)
		return NULL;
	else{
		int leidos = sscanf(string,"%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", objeto_aux, verbo_aux, objeto_parametro_aux, &tipo_accion_actual, accion_objeto_aux, accion_mensaje_aux);

		if(leidos != 6)
			return NULL;
		
		char objeto[MAX_NOMBRE] = "objeto";
		int objeto_validado = validar_y_agregar_campos_interaccion(objeto_aux, interaccion_actual->objeto, interaccion_actual, objeto);

		char verbo[MAX_NOMBRE] = "verbo";
		int verbo_validado = validar_y_agregar_campos_interaccion(verbo_aux, interaccion_actual->verbo, interaccion_actual, verbo);

		char objeto_parametro[MAX_NOMBRE] = "objeto_parametro";
		int objeto_parametro_validado = validar_y_agregar_campos_interaccion(objeto_parametro_aux, interaccion_actual->objeto_parametro, interaccion_actual, objeto_parametro);
		
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
			interaccion_actual->accion.tipo=MOSTRAR_MENSAJE;
			break;	
		default:
			interaccion_actual->accion.tipo=0;
			break;
		}

		char accion_objeto[MAX_NOMBRE] = "accion_objeto";
		int accion_objeto_validado = validar_y_agregar_campos_interaccion(accion_objeto_aux, interaccion_actual->accion.objeto, interaccion_actual, accion_objeto);

		char accion_mensaje[MAX_TEXTO] = "accion_mensaje";
		int accion_mensaje_validado = validar_y_agregar_campos_interaccion(accion_mensaje_aux, interaccion_actual->accion.mensaje, interaccion_actual, accion_mensaje);

		if(objeto_validado == -1 || verbo_validado == -1 || objeto_parametro_validado == -1 || interaccion_actual->accion.tipo == 0|| accion_objeto_validado == -1 || accion_mensaje_validado == -1)
			interaccion_actual = NULL;
	}

	return interaccion_actual;
}
