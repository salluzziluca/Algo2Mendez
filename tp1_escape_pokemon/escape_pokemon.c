#include "src/sala.h"
#include "src/validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARCHIVO_OBJETOS argv[1] 
#define ARCHIVO_INTERACCIONES argv[2]
#define MAX_NOMBRE 20

int main(int argc, char *argv[])
{	
	sala_t *sala = sala_crear_desde_archivos(ARCHIVO_OBJETOS, ARCHIVO_INTERACCIONES);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}
	int *cantidad_objetos =calloc(1, sizeof(int));
	char **nombres_objetos = sala_obtener_nombre_objetos(sala, cantidad_objetos);
	
	printf("Objetos...\n");
	for (int i = 0; i < *cantidad_objetos-1; i++)
	{
		printf("%i: %s\n", i, nombres_objetos[i]);
	}

	printf("\n");

	printf("Interacciones...\n");

	
	char *examinar_habitacion = calloc(MAX_NOMBRE, sizeof(char));
	interracion_valida(sala_es_interaccion_valida(sala, "examinar", "habitacion", "_"), examinar_habitacion);

	char *abrir_pokebola = calloc(MAX_NOMBRE, sizeof(char));
	interracion_valida(sala_es_interaccion_valida(sala, "abrir", "pokebola", "_"), abrir_pokebola);

	char *usar_llave_cajon = calloc(MAX_NOMBRE, sizeof(char));
	interracion_valida(sala_es_interaccion_valida(sala, "usar", "llave", "cajon"), usar_llave_cajon);
	
	char *quemar_mesa = calloc(MAX_NOMBRE, sizeof(char));
	interracion_valida(sala_es_interaccion_valida(sala, "quemar", "mesa", "_"), quemar_mesa);
	

	printf("examinar la habitacion: %s\n", examinar_habitacion);
	printf("Abrir pokebola: %s\n", abrir_pokebola);
	printf("Usar llave en el cajon: %s\n", usar_llave_cajon);
	printf("Quemar la mesa: %s\n", quemar_mesa);
	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa

	

	//sala_destruir(sala);

	return 0;
}
