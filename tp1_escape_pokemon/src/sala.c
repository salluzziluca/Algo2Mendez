#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LARGO_MAX_LINEA 1024
#define MODO_LECTURA "r"
#define OBJETOS 'o'
#define INTERACCIONES 'i'

int agregar_objeto_a_vector(struct objeto ***objetos, int *cantidad_objetos, struct objeto *objeto_actual)
{
	struct objeto **bloque_auxiliar = realloc(*objetos, ((unsigned)(*cantidad_objetos)+1) * sizeof(struct objeto*));

	if(bloque_auxiliar == NULL)
		return -1;

	*objetos = bloque_auxiliar;
	bloque_auxiliar[*cantidad_objetos]=objeto_actual;
	(*cantidad_objetos)++;

	return 0;
}

int agregar_interaccion_a_vector(struct interaccion ***interacciones, int *cantidad_interacciones, struct interaccion *interaccion_actual)
{
	struct interaccion **bloque_auxiliar = realloc(*interacciones, ((unsigned)(*cantidad_interacciones)+1) * sizeof(struct interaccion*));

	if(bloque_auxiliar == NULL)
		return -1;

	*interacciones = bloque_auxiliar;
	bloque_auxiliar[*cantidad_interacciones]=interaccion_actual;
	(*cantidad_interacciones)++;

	return 0;
}

int cargar_a_memoria(struct sala *sala, const char *archivo, char elemento )
{
	FILE *archivo_actual = fopen(archivo, MODO_LECTURA);

	if(!archivo_actual)
		return -1;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_actual);
	
	if(linea_leida == NULL){
		fclose(archivo_actual);
		return -1;
	}

	if(elemento == 'o'){
		sala->objetos = NULL;
		sala->cantidad_objetos = 0;

	}
	else if(elemento == 'i'){
		sala->interacciones = NULL;
		sala->cantidad_interacciones = 0;
	}

	while(linea_leida!=NULL){
		if(elemento == 'o'){
			struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);

			agregar_objeto_a_vector(&sala->objetos, &sala->cantidad_objetos, objeto_a_agregar);
			linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_actual);
		}
		else if(elemento == 'i'){
			struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea);

			agregar_interaccion_a_vector(&sala->interacciones, &sala->cantidad_interacciones, interaccion_a_agregar);
			linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_actual);
		}
	}
	fclose(archivo_actual);
	return 0;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	struct sala *sala = calloc(1, sizeof(struct sala));

	if(sala == NULL)
		return NULL;

	cargar_a_memoria(sala, objetos, OBJETOS);
	cargar_a_memoria(sala, interacciones, INTERACCIONES);

	if(sala->cantidad_objetos == 0 || sala->cantidad_interacciones == 0){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(sala == NULL){
		if(cantidad != NULL)
			*cantidad=-1;

		return NULL;	
	}

	char **nombres_objetos = malloc((unsigned)sala->cantidad_objetos * sizeof(char*));

	if(nombres_objetos == NULL){
		if(cantidad != NULL)
			*cantidad=-1;

		return NULL;	
	}
	
	for(int i = 0; i < sala->cantidad_objetos; i++){
		nombres_objetos[i] = sala->objetos[i]->nombre;
	}

	if(cantidad != NULL)
		*cantidad = sala->cantidad_objetos;
		
	return nombres_objetos;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,const char *objeto2)
{	
	if(sala == NULL || verbo == NULL || objeto1 == NULL)
		return false;

	bool es_valido = false;

	for(int i = 0; i < sala->cantidad_interacciones; i++){
		
		bool es_objeto_valido = strcmp(sala->interacciones[i]->objeto, objeto1) == 0;

		bool es_objeto_parametro_valido = strcmp(sala->interacciones[i]->objeto_parametro, objeto2) == 0;
		
		bool es_verbo_valido = strcmp(sala->interacciones[i]->verbo, verbo) == 0;

		if(es_objeto_valido && es_objeto_parametro_valido && es_verbo_valido)
			es_valido = true;
	}

	return es_valido;
}

void sala_destruir(sala_t *sala)
{
	for(int i = 0; i < sala->cantidad_objetos; i++){
		free(sala->objetos[i]);
	}

	for(int i = 0; i < sala->cantidad_interacciones; i++){
		free(sala->interacciones[i]);
	}	
	free(sala->objetos);
	free(sala->interacciones);
	free(sala);
}
