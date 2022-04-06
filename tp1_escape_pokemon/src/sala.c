#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 15




int agregar_objeto_a_vector(struct objeto ***objetos, int *cantidad_objetos, struct objeto *objeto_actual)
{
	struct objeto **bloque_auxiliar = realloc(*objetos, ((unsigned)(*cantidad_objetos)+1) * sizeof(struct objeto*));

	if(bloque_auxiliar == NULL)
		return -1;

	*objetos= bloque_auxiliar;
	bloque_auxiliar[*cantidad_objetos]=objeto_actual;
	(*cantidad_objetos)++;

	return 0;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	struct sala *sala= malloc( sizeof(struct sala));
	sala->objetos = calloc(1, sizeof(struct objetos*));
	
	FILE *archivo_objetos= fopen(objetos, "r");

	if(!archivo_objetos)
		return NULL;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, 
	LARGO_MAX_LINEA, archivo_objetos);

	if (linea_leida == NULL)
		return NULL;
		
	struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);

	agregar_objeto_a_vector(&sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);
	//TODO ver por que no se guarda el segundo objeto
	while (linea_leida){	
		linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_objetos);
		struct objeto *objeto_a_agregar =objeto_crear_desde_string(linea);
		agregar_objeto_a_vector(&sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);
	}
	for (int i = 1; i < sala->cantidad_objetos-1; ++i)
	{
		printf("%s\n", sala->objetos[i]->nombre);
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
