#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 5

int agregar_objeto_a_sala(struct sala *sala, int *tamanio, struct objeto *objeto)
{
	//TODO: Resolver el error de realloc que me tira valgrind
	 sala_t *bloque = realloc(sala,sizeof(struct objeto));
	if (bloque == NULL)
		return -1;

	bloque->objetos[*tamanio] = objeto;
	(*tamanio)++;

	*sala = *bloque;

	return 0;



}	
sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	//TODO: fijarse como inicializar un struct como null.
	struct sala sala= NULL;

	int tamanio = 0;
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

	agregar_objeto_a_sala(&sala, &tamanio, objeto_a_agregar);

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
