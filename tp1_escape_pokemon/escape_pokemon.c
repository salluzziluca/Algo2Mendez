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

	if (sala == NULL){
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	int *contador_vector_nombres =calloc(1, sizeof(int));
	char **nombres_objetos = sala_obtener_nombre_objetos(sala, contador_vector_nombres);
	
	printf("Objetos...\n");
	for (int i = 0; i < *contador_vector_nombres-1; i++){
		printf("%i: %s\n", i, nombres_objetos[i]);
	}

	printf("\n");

	printf("Interacciones...\n");

	bool es_examinar_habitacion_valida = sala_es_interaccion_valida(sala, "examinar", "habitacion", "");

	bool es_abrir_pokebola_valida = sala_es_interaccion_valida(sala, "abrir", "pokebola", "");

	bool es_usar_llave_cajon_valido = sala_es_interaccion_valida(sala, "usar", "llave", "cajon");
	
	bool es_quemar_mesa_valido = sala_es_interaccion_valida(sala, "quemar", "mesa", "");
	

	printf("examinar la habitacion: %s\n", interaccion_valida(es_examinar_habitacion_valida));
	printf("Abrir pokebola: %s\n", interaccion_valida(es_abrir_pokebola_valida));
	printf("Usar llave en el cajon: %s\n", interaccion_valida(es_usar_llave_cajon_valido));
	printf("Quemar la mesa: %s\n", interaccion_valida(es_quemar_mesa_valido));
	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa

	

	//sala_destruir(sala);

	return 0;
}
