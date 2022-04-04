#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 5

int agregar_objeto_a_vector(struct objeto **vector, int *tamanio, struct objeto *objeto)
{
	//TODO: cuchame pibe, lo quetenes que hacer es que eesta funcion agregue un objeto al vector dinamico objetos. el struct sala ya lo tenes que tener inicializado.
	 struct objeto *bloque_vector_objetos = realloc(*vector,((*tamanio) + 1) * sizeof(struct objeto));
	
	if (bloque_vector_objetos == NULL)
			return -1;


	bloque_vector_objetos[*tamanio] = *objeto;
	(*tamanio)++;

	*vector = bloque_vector_objetos;

	return 0;



}	
sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	struct sala *sala;

	/*if(sala==NULL)
		return NULL;*/
	
	FILE *archivo_objetos= fopen(objetos, "r");

	if(!archivo_objetos)
		return NULL;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, 
	LARGO_MAX_LINEA, archivo_objetos);

	if (linea_leida == NULL)
		return NULL;
		
	struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);

	agregar_objeto_a_vector(sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);

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
