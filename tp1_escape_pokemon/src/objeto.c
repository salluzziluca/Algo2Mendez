#include "objeto.h"
#include "estructuras.h"
#include "estructuras.h"
#include "validaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BOOL 20
struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto_actual= malloc(sizeof(struct objeto));

	char nombre_aux[MAX_NOMBRE] = "\0";
	char descripcion_aux[MAX_TEXTO] = "\0";
	char bool_aux[MAX_BOOL] = "\0";

	if(string ==NULL)
		return NULL;
		
	else if((strcmp(string,"_") == 0)){
		strcpy(objeto_actual->nombre,"\0");
		strcpy(objeto_actual->descripcion,"\0");
		objeto_actual->es_asible=false;
	}
	else{
		sscanf(string,"%[^;];%[^;];%[^\n]\n",nombre_aux, descripcion_aux, bool_aux);
		
		validar_y_agregar_campos_objeto(nombre_aux, objeto_actual->nombre, objeto_actual);

		validar_y_agregar_campos_objeto(descripcion_aux, objeto_actual->descripcion, objeto_actual);

		if(strcmp(bool_aux,"true") == 0)
			objeto_actual->es_asible = true;
		else if ((strcmp(bool_aux,"false") == 0))
		{
			objeto_actual->es_asible = false;
		}
		else
		{
			return NULL;
		}
	}	

	return objeto_actual;
}
