#include "estructuras.h"
#include "sala.h"
#include <stdlib.h>
#include <stdio.h>
#define LARGO_MAX_LINEA 1024

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *objetos= fopen(objetos, "r");

	if(!objetos)
		return NULL;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, 
	LARGO_MAX_LINEA, objetos);

	struct objeto objeto;
	bool es_asible;

	sscanf(linea,"%[^;];%[^;];%[^\n]\n",objeto.nombre, objeto.descripcion, es_asible);

	while (linea_leida)
	{
		printf("Nombre: %s - Descripcion: %s - Es asible: %s\n", objeto.nombre, objeto.descripcion, es_asible);
		linea_leida = fgets(linea, LARGO_MAX_LINEA, objetos);
		sscanf(linea,"%[^;];%[^;];%[^\n]\n",objeto.nombre, objeto.descripcion, es_asible);
	}
	
	fclose(objetos);
	/*FILE *interacciones = fopen(interacciones, "r");*/


	
	return NULL;
}



char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return NULL;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	return false;
}

void sala_destruir(sala_t *sala)
{
}
