#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARCHIVO_OBJETOS argv[1] 
#define ARCHIVO_INTERACCIONES argv[2]
#define MAX_NOMBRE 20



int main(int argc, char *argv[])
{	
	
	
	//Los archivos deben venir como parámetros del main
	if((((strcmp(ARCHIVO_OBJETOS, "ejemplo/objetos.txt")) != 0) || ((strcmp(ARCHIVO_INTERACCIONES,"ejemplo/interacciones.txt"))!=0))){
		printf("Error, no se ingresaron los archivos correctamente\n");
		return -1;
	}

	sala_t *sala = sala_crear_desde_archivos(ARCHIVO_OBJETOS, ARCHIVO_INTERACCIONES);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}
	//Mostrar todos los objetos en la sala
	int *cantidad_objetos =calloc(1, sizeof(int));
	char **nombres_objetos = sala_obtener_nombre_objetos(sala, cantidad_objetos);
	
	printf("Objetos...\n");
	for (int i = 0; i < *cantidad_objetos-1; i++)
	{
		printf("%i: %s\n", i, nombres_objetos[i]);
	}

	printf("\n");

	printf("Interacciones...\n");

	char examinar_habitacion[MAX_NOMBRE];
	if(sala_es_interaccion_valida(sala, "examinar", "habitacion", "\0")){
		strcpy(examinar_habitacion, "Válido");
	}
	else{
		strcpy(examinar_habitacion, "Inválido");
	}

	char abrir_pokebola[MAX_NOMBRE];
	if(sala_es_interaccion_valida(sala, "abrir", "pokebola", "\0")){
		strcpy(abrir_pokebola, "Válido");
	}
	else{
		strcpy(abrir_pokebola, "Inválido");
	}

	char usar_llave_cajon[MAX_NOMBRE];
	if(sala_es_interaccion_valida(sala, "usar", "llave", "cajon")){
		strcpy(usar_llave_cajon, "Válido");
	}
	else{
		strcpy(usar_llave_cajon, "Inválido");
	}
	
	char quemar_mesa[MAX_NOMBRE];
	if(sala_es_interaccion_valida(sala, "quemar", "mesa", "\0")){
		strcpy(quemar_mesa, "Válido");
	}
	else{
		strcpy(quemar_mesa, "Inválido");
	}


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
