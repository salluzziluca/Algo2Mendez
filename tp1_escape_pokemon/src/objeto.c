#include "objeto.h"
#include "estructuras.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LARGO_MAX_NOMBRE 20
#define LARGO_MAX_BOOL 15
#define LARGO_MAX_DESCRIPCION 100

struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto_actual= malloc(sizeof(struct objeto));

	char bool_aux[LARGO_MAX_BOOL];

	sscanf(string,"%[^;];%[^;];%[^\n]\n",objeto_actual->nombre, objeto_actual->descripcion, bool_aux);
	
	if(strcmp(bool_aux,"true")==0)
		objeto_actual->es_asible=true;
	else
		objeto_actual->es_asible=false;

	return (objeto_actual);
}
