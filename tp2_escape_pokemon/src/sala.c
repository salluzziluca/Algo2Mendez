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
#define MAX_NOMBRE_INTERACCION 100
#define ACCION_INVALIDA 0
#define	DESCUBRIR_OBJETO 1
#define REEMPLAZAR_OBJETO 2
#define ELIMINAR_OBJETO 3
#define MOSTRAR_MENSAJE 4
#define ESCAPAR 5

/*
* Recibe la direccion de un archivo, un puntero a sala, un puntero a hash y un caracter
* especificando el tipo de elemento que se esta tratando (objeto o interaccion).
* Lee el archivo linea por linea y carga el elemento correspondinte a un hash.
* Utiliza como clave en nombre del objeto o, en el caso de una interaccion, 
* el nombre del objeto_parametro concatenado al nombre del objeto. 
 *devuelve el hash o NULL en caso de error
*/
hash_t *cargar_elementos(sala_t *sala, const char *nombre_archivo,  char tipo_elemento)
{
	if(!sala || !nombre_archivo || !tipo_elemento)
		return NULL;
	FILE *archivo = fopen(nombre_archivo, MODO_LECTURA);
	if(!archivo)
		return NULL;

	hash_t *hash = NULL;
	char linea[LARGO_MAX_LINEA];
	char *linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo);
	if(!linea_leida ){
		fclose(archivo);
		return NULL;
	}

	if(tipo_elemento == OBJETOS){
		struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);
		hash_insertar(sala->jugador->objetos_conocidos, objeto_a_agregar->nombre, objeto_a_agregar);
		sala->jugador->cantidad_objetos_conocidos++;
	}

	while(linea_leida){

		if(tipo_elemento == OBJETOS){
			struct objeto *objeto_a_agregar = objeto_crear_desde_string(linea);
			hash_insertar(sala->objetos, objeto_a_agregar->nombre, objeto_a_agregar);
			hash = sala->objetos;
			sala->cantidad_objetos++;
		}
		else if(tipo_elemento == INTERACCIONES){
			struct interaccion *interaccion_a_agregar = interaccion_crear_desde_string(linea);

			char clave_interaccion[MAX_NOMBRE_INTERACCION] = ""; //TODO: Modularizar el strcat y hacer mas bonita este llamado.
			hash_insertar(sala->interacciones, strcat(strcat(strcat(clave_interaccion, interaccion_a_agregar->objeto), interaccion_a_agregar->verbo), interaccion_a_agregar->objeto_parametro), interaccion_a_agregar);
			hash = sala->interacciones;
			sala->cantidad_interacciones++;
		}
		linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo);
	}
	fclose(archivo);

	return hash;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones) 
{
	if(!objetos || !interacciones)
		return NULL;
		
	struct sala *sala = calloc(1,sizeof(struct sala));
	if(sala == NULL)
		return NULL;

 	sala->objetos = hash_crear(TAMANIO_MIN_HASH);
	if(!sala->objetos)
		return NULL;

	sala->interacciones = hash_crear(TAMANIO_MIN_HASH);
	if(!sala->interacciones)
		return NULL;

	sala->jugador = calloc(1, sizeof(struct jugador));
	if(sala->jugador == NULL){
		sala_destruir(sala);
		return NULL;
	}

	sala->jugador->objetos_conocidos = hash_crear(TAMANIO_MIN_HASH);
	if(sala->jugador->objetos_conocidos == NULL){
		sala_destruir(sala);
		return NULL;
	}
	sala->jugador->objetos_poseidos = hash_crear(TAMANIO_MIN_HASH);
	if(sala->jugador->objetos_poseidos == NULL){
		sala_destruir(sala);
		return NULL;
	}

	if(cargar_elementos(sala, objetos, OBJETOS))
		sala->cantidad_objetos = hash_cantidad(sala->objetos);
	else{
		sala_destruir(sala);
		return NULL;
	}

	if(cargar_elementos(sala, interacciones, INTERACCIONES))
		sala->cantidad_interacciones = hash_cantidad(sala->interacciones);	
	else{
		sala_destruir(sala);
		return NULL;
	}

	if(sala->cantidad_objetos == 0 || sala->cantidad_interacciones == 0){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

char **obtener_nombres_objetos(hash_t *hash, int *cantidad)
{
	if(!hash){
		if(cantidad != NULL)
			*cantidad=-1;
		return NULL;
	}
	char **nombres_objetos = malloc((unsigned)hash_cantidad(hash) * sizeof(char*));
	if(nombres_objetos == NULL){
		if(cantidad != NULL)
			*cantidad=-1;
		return NULL;
	}
	hash_obtener_claves(hash, nombres_objetos);
	if(cantidad != NULL)
		*cantidad =(int)hash_cantidad(hash);
	
	return nombres_objetos;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad != NULL)
			*cantidad=-1;
		return NULL;
	}
	return obtener_nombres_objetos(sala->objetos, cantidad);
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad != NULL)
			*cantidad=-1;
		return NULL;
	}
	return obtener_nombres_objetos(sala->jugador->objetos_conocidos, cantidad);
}


char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad != NULL)
			*cantidad=-1;
		return NULL;
	}
	return obtener_nombres_objetos(sala->jugador->objetos_poseidos, cantidad);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto)
		return false;

	hash_t *hash_objetos_conocidos = sala->jugador->objetos_conocidos;

	struct objeto *objeto_actual = hash_obtener(hash_objetos_conocidos, nombre_objeto);
	if(objeto_actual == NULL)
		return false;

	if(objeto_actual->es_asible){
		hash_quitar(hash_objetos_conocidos, nombre_objeto);
		hash_insertar(sala->jugador->objetos_poseidos, nombre_objeto, objeto_actual);
		return true;
	}

	return false;
}


char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto)
		return NULL;

	hash_t *hash_objetos_conocidos = sala->jugador->objetos_conocidos;
	hash_t *hash_objetos_poseidos = sala->jugador->objetos_poseidos;

	struct objeto *objeto_actual = hash_obtener(hash_objetos_conocidos, nombre_objeto);
	if(objeto_actual == NULL)
		objeto_actual = hash_obtener(hash_objetos_poseidos, nombre_objeto);
	if(objeto_actual == NULL)
		return NULL;
	
	return objeto_actual->descripcion;
}

/*
* Recibe una sala y dos nombres de objetos.
* Si los objetos existen y son conocidos o poseidos por el jugador,
* Devuelve true. Si el objeto1 es conocido pero debe ser poseido (es asible),
* devuelve false. Si el objeto1 no existe o no es conocido, devuelve false.
* El objeto2 no debe ser poseido y puede no ser conocido.
*/
bool son_objetos_validos(sala_t *sala, const char *objeto1, const char *objeto2)
{	
	bool es_interaccion_valida = false;
	bool hay_objeto_parametro = false;
	bool es_objeto_valido = false;
	bool es_objeto_parametro_valido = false;
	struct objeto *objeto1_actual = NULL;
	struct objeto *objeto2_actual = NULL;

	objeto1_actual = hash_obtener(sala->jugador->objetos_poseidos, objeto1);
	if (objeto1_actual != NULL){
		es_objeto_valido = true;
	}
	else{
		objeto1_actual = hash_obtener(sala->jugador->objetos_conocidos, objeto1);
		if (objeto1_actual != NULL){
			if(!objeto1_actual->es_asible){
				es_objeto_valido = true;
			}
		}
	}


	if(strcmp(objeto2, "") != 0){
		objeto2_actual = hash_obtener(sala->jugador->objetos_conocidos, objeto2);
		if (objeto2_actual != NULL){
			es_objeto_parametro_valido = true;
		}
		hay_objeto_parametro = true;
	}

	if(es_objeto_valido && !hay_objeto_parametro){
		es_interaccion_valida = true;
	}
	else if(es_objeto_valido && hay_objeto_parametro && es_objeto_parametro_valido){
		es_interaccion_valida = true;
	}

	return es_interaccion_valida;
}
int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if(!sala || !verbo || !objeto1 || !mostrar_mensaje)
		return 0;

	hash_t *hash_interacciones = sala->interacciones;

	bool hay_objeto_parametro = (strcmp(objeto2, "") != 0);
	if(!son_objetos_validos(sala, objeto1, objeto2)){
			return 0;
		}
		
	char nombre_interaccion[MAX_NOMBRE_INTERACCION] ="";
	strcat(strcat(strcat(nombre_interaccion, objeto1), verbo), objeto2);
	struct interaccion *interaccion_actual = hash_obtener(hash_interacciones, nombre_interaccion);
	if(interaccion_actual == NULL){
		printf("La interaccion ingresada no existe.\n");
		return 0;
	}
	
	int interacciones_ejecutadas = 0;
	while( interaccion_actual != NULL){
		hash_quitar(hash_interacciones, nombre_interaccion);
		switch (interaccion_actual->accion.tipo){
			
			case DESCUBRIR_OBJETO:
				hash_insertar(sala->jugador->objetos_conocidos, interaccion_actual->accion.objeto,
					hash_obtener(sala->objetos, interaccion_actual->accion.objeto));
				hash_quitar(sala->objetos, interaccion_actual->accion.objeto);
				mostrar_mensaje(interaccion_actual->accion.mensaje,interaccion_actual->accion.tipo, aux);
				interacciones_ejecutadas++;
				sala->cantidad_objetos--;
				sala->jugador->cantidad_objetos_conocidos++;
				break;

			case REEMPLAZAR_OBJETO: ;

				void *objeto_reemplazo = hash_quitar(sala->objetos, interaccion_actual->accion.objeto);
				hash_insertar(sala->jugador->objetos_conocidos, interaccion_actual->accion.objeto, objeto_reemplazo);

		
				if(hay_objeto_parametro){
					void *objeto_quitado = hash_quitar(sala->jugador->objetos_conocidos, interaccion_actual->objeto_parametro);
					free(objeto_quitado);
					sala->jugador->cantidad_objetos_conocidos--;
				}
				mostrar_mensaje(interaccion_actual->accion.mensaje, interaccion_actual->accion.tipo, aux);
				interacciones_ejecutadas++;
				sala->cantidad_objetos--;
				sala->jugador->cantidad_objetos_conocidos++;
				sala->jugador->cantidad_objetos_poseidos--;
				break;

			case ELIMINAR_OBJETO: ;
				void *quitado = hash_quitar(sala->jugador->objetos_poseidos, interaccion_actual->accion.objeto);
				mostrar_mensaje(interaccion_actual->accion.mensaje, interaccion_actual->accion.tipo, aux);
				interacciones_ejecutadas++;
				sala->jugador->cantidad_objetos_poseidos--;
				free(quitado);
				break;

			case MOSTRAR_MENSAJE:
				mostrar_mensaje(interaccion_actual->accion.mensaje, interaccion_actual->accion.tipo, aux);
				interacciones_ejecutadas++;
				break;

			case ESCAPAR:
				mostrar_mensaje(interaccion_actual->accion.mensaje, interaccion_actual->accion.tipo, aux);
				interacciones_ejecutadas++;
				sala->jugador->escapo = true;
				free(interaccion_actual);
				return 1;
				break;

			default:
			printf("No se puede realizar la accion que pediste con el objeto actual");
				break;
		}
		free(interaccion_actual);
		interaccion_actual = hash_obtener(hash_interacciones, nombre_interaccion);
	}

	return interacciones_ejecutadas;
}
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,const char *objeto2)
{	
	if(sala == NULL || verbo == NULL || objeto1 == NULL)
		return false;

	
	char nombre_interaccion[30] ="";
	strcat(strcat(nombre_interaccion, objeto1), verbo);

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
	if(!sala)
		return false;
	return sala->jugador->escapo;
}

void jugador_destruir(jugador_t *jugador)
{
	if(!jugador)
		return;
	hash_destruir_todo(jugador->objetos_conocidos, free);
	hash_destruir_todo(jugador->objetos_poseidos, free);
	free(jugador);
}
void sala_destruir(sala_t *sala)
{

	if(!sala)
		return;
	
	jugador_destruir(sala->jugador);
	hash_destruir_todo(sala->objetos, free);
	hash_destruir_todo(sala->interacciones, free);
	free(sala);
}
