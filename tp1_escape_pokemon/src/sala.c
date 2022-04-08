#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define LARGO_MAX_LINEA 1024
#define LARGO_MAX_BOOL 15
#define MODO_LECTURA "r"




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

int agregar_interaccion_a_vector(struct interaccion ***interacciones, int *cantidad_interacciones, struct interaccion *interaccion_actual)
{
	struct interaccion **bloque_auxiliar = realloc(*interacciones, ((unsigned)(*cantidad_interacciones)+1) * sizeof(struct interaccion*));

	if(bloque_auxiliar == NULL)
		return -1;

	*interacciones= bloque_auxiliar;
	bloque_auxiliar[*cantidad_interacciones]=interaccion_actual;
	(*cantidad_interacciones)++;

	return 0;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	struct sala *sala= malloc( sizeof(struct sala));
	sala->objetos =NULL;
	sala->interacciones=NULL;
	
	FILE *archivo_objetos= fopen(objetos, MODO_LECTURA);
	

	if(!archivo_objetos)
		return NULL;

	char linea_objeto[LARGO_MAX_LINEA];
	char *linea_leida_objeto = fgets(linea_objeto, 
	LARGO_MAX_LINEA, archivo_objetos);

	if (linea_leida_objeto == NULL)
		return NULL;
		
	struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea_objeto);

	agregar_objeto_a_vector(&sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);

	while (linea_leida_objeto){	
		linea_leida_objeto = fgets(linea_objeto, LARGO_MAX_LINEA, archivo_objetos);
		struct objeto *objeto_a_agregar =objeto_crear_desde_string(linea_objeto);
		agregar_objeto_a_vector(&sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);
	}

	for (int i = 0; i < sala->cantidad_objetos-1; ++i)
	{
		printf("%s\n", sala->objetos[i]->nombre);
	}

	fclose(archivo_objetos);
/*-----------------------------INTERACCIONES---------------------------------*/
	FILE *archivo_interacciones = fopen(interacciones, MODO_LECTURA);

	if(!archivo_interacciones)
		return NULL;

	char linea_interaccion[LARGO_MAX_LINEA];
	char *linea_leida_interaccion = fgets(linea_interaccion,LARGO_MAX_LINEA, archivo_interacciones);
	
	if(linea_leida_interaccion == NULL)
		return NULL;
	
	struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea_interaccion);

	agregar_interaccion_a_vector(&sala->interacciones, &sala->cantidad_interacciones, interaccion_a_agregar);

	while(linea_leida_interaccion){
		linea_leida_interaccion = fgets(linea_interaccion, LARGO_MAX_LINEA, archivo_interacciones);
		struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea_interaccion);
		agregar_interaccion_a_vector(&sala->interacciones, &sala->cantidad_interacciones, interaccion_a_agregar);
	}

	for (int i = 0; i < sala->cantidad_interacciones-1; ++i)
	{
		printf("%s\n", sala->interacciones[i]->objeto);
		printf("%s\n", sala->interacciones[i]->verbo);
		printf("%s\n", sala->interacciones[i]->objeto_parametro);
	}


	fclose(archivo_interacciones);
	

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
