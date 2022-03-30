#include "estructuras.h"
#include "sala.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 5
#define LARGO_MAX_NOMBRE 20
#define LARGO_MAX_DESCRIPCION 100

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *archivo_objetos= fopen(objetos, "r");

	if(!archivo_objetos)
		return NULL;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, 
	LARGO_MAX_LINEA, archivo_objetos);

	//struct objeto objeto;
	char nombre[LARGO_MAX_NOMBRE];
	char descripcion[LARGO_MAX_NOMBRE];
	char es_asible[LARGO_MAX_DESCRIPCION];

	//TODO: ver por que no lee el archivo correctamente
	sscanf(linea,"%[^;];%[^;];%[^\n]\n",nombre, descripcion, es_asible);

	while (linea_leida)
	{
		printf("Nombre: %s - Descripcion: %s - Es asible: %s\n", nombre, descripcion, es_asible);
		linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_objetos);
		sscanf(linea,"%[^;];%[^;];%[^\n]\n",nombre, descripcion, es_asible);
	}
	
	fclose(archivo_objetos);
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
	//tener cuidado de liberar toda la memoria en orden
}
