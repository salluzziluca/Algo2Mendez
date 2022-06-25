#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "estructura_sala.h"
#include "funciones_aux.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LARGO_MAX_LINEA 1024
#define MODO_LECTURA "r"
#define OBJETOS 'o'
#define INTERACCIONES 'i'
#define TAMANIO_MIN_HASH 15
#define MAX_NOMBRE_INTERACCION 30

/*
* Recibe la direccion de un archivo, un puntero a sala, un puntero a hash y un caracter
* especificando el tipo de elemento que se esta tratando (objeto o interaccion).
* Lee el archivo linea por linea y carga el elemento correspondinte a un hash.
* Utiliza como clave en nombre del objeto o, en el caso de una interaccion, 
* el nombre del objeto_parametro concatenado al nombre del objeto. 
 *devuelve el hash o NULL en caso de error
*/
hash_t *cargar_elementos(sala_t *sala, const char *nombre_archivo, hash_t *hash,  char tipo_elemento)
{
	if(!sala || !nombre_archivo || !tipo_elemento)
		return NULL;
	FILE *archivo = fopen(nombre_archivo, MODO_LECTURA);
	if(!archivo)
		return NULL;
	
	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo);
	if(!linea_leida )
		return NULL;
	void* anterior = NULL;
	while(linea_leida){

		if(tipo_elemento == OBJETOS){
			struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);
			hash_insertar(hash, objeto_a_agregar->nombre, objeto_a_agregar, anterior);
		}
		else if(tipo_elemento == INTERACCIONES){
			struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea);
			hash_insertar(hash, strcat(interaccion_a_agregar->objeto, interaccion_a_agregar->objeto_parametro), interaccion_a_agregar, anterior);
		}
		linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo);
	}
	fclose(archivo);
	if(anterior)
		return NULL;

	return hash;
}


/*
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

//TODO: documentar esta funcion
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

//TODO: documentar esta funcion
int cargar_a_memoria(struct sala *sala, const char *archivo, char elemento )
{
	if(!sala || !archivo)
		return -1;
	FILE *archivo_actual = fopen(archivo, MODO_LECTURA);

	if(!archivo_actual)
		return -1;

	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo_actual);
	
	if(linea_leida == NULL){
		fclose(archivo_actual);
		return -1;
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
*/
sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	if(!objetos || !interacciones)
		return NULL;
		
	struct sala *sala = calloc(1, sizeof(struct sala));
	if(sala == NULL)
		return NULL;
	hash_t* hash_objetos = hash_crear(TAMANIO_MIN_HASH);
	if(cargar_elementos(sala, objetos, hash_objetos, OBJETOS)){
 		sala->objetos = hash_objetos;
		sala->cantidad_objetos = hash_cantidad(hash_objetos);
	}

	hash_t* hash_interacciones = hash_crear(TAMANIO_MIN_HASH);
	if(cargar_elementos(sala, interacciones, hash_interacciones, INTERACCIONES)){
		sala->interacciones = hash_interacciones;
		sala->cantidad_interacciones = hash_cantidad(hash_interacciones);
	}

	//cargar_a_memoria(sala, objetos, OBJETOS);
	//cargar_a_memoria(sala, interacciones, INTERACCIONES);

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
	
	/*for(int i = 0; i < sala->cantidad_objetos; i++){
		nombres_objetos[i] = sala->objetos[i]->nombre;
	}*/

	hash_obtener_claves(sala->objetos, nombres_objetos);

	if(cantidad != NULL)
		*cantidad = (int)sala->cantidad_objetos;
		
	return nombres_objetos;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	return NULL;
}


char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	return NULL;
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	return false;
}


char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	return NULL;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	return 0;
}
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,const char *objeto2)
{	
	if(sala == NULL || verbo == NULL || objeto1 == NULL)
		return false;


	char nombre_interaccion[30] ="";
	strcat(nombre_interaccion, objeto1);

	if(strcmp(objeto2, "") != 0)
		strcat(nombre_interaccion, objeto2);
	struct interaccion *interaccion = hash_obtener(sala->interacciones, nombre_interaccion);
	if(interaccion == NULL)
		return false;
	if(strcmp(interaccion->verbo, verbo) == 0)
		return true;
	return false;
}


bool sala_escape_exitoso(sala_t *sala)
{
	return false;
}

void sala_destruir(sala_t *sala)
{

	if(sala == NULL)
		return;
	
	hash_destruir(sala->objetos);
	hash_destruir(sala->interacciones);
	free(sala);
}
