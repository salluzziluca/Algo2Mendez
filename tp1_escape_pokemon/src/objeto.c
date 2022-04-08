#include "objeto.h"
#include "estructuras.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BOOL 20
struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto_actual= malloc(sizeof(struct objeto));

	char nombre_aux[MAX_NOMBRE];
	char descripcion_aux[MAX_TEXTO];
	char bool_aux[MAX_BOOL];

	sscanf(string,"%[^;];%[^;];%[^\n]\n",nombre_aux, descripcion_aux, bool_aux);
	
	if(nombre_aux!=NULL)
		strcpy(objeto_actual->nombre,nombre_aux);
	else
		return NULL;
	
	if(descripcion_aux!=NULL)
		strcpy(objeto_actual->descripcion,descripcion_aux);
	else
		return NULL;

	if(strcmp(bool_aux,"true")==0)
		objeto_actual->es_asible=true;
	else if ((strcmp(bool_aux,"false")==0))
	{
		objeto_actual->es_asible=false;
	}
	else
	{
		return NULL;
	}

	return (objeto_actual);
}
