#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 5

sala_t *sala_con_objeto_agregado(struct sala *sala, int *tamanio, struct objeto *objeto)
{
	//TODO: preguntar como alocarle memoria a un struct
	struct *(bloque)=realloc(*sala,sizeof(struct objeto));
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	struct sala sala;
	//TODO: Chequear los campos del struct sala y pensar como pasarlos a sala_obtener_nombre_objetos()
	FILE *archivo_objetos= fopen(objetos, "r");

	if(!archivo_objetos)
		return NULL;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, 
	LARGO_MAX_LINEA, archivo_objetos);

	if (linea_leida == NULL)
		return NULL;
		
	struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);

	while (linea_leida){	
		linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_objetos);
		objeto_a_agregar=objeto_crear_desde_string(linea);
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
