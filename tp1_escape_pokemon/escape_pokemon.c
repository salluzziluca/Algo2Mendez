#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARCHIVO_OBJETOS argv[1] 
#define ARCHIVO_INTERACCIONES argv[2]



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
		printf("%s\n", nombres_objetos[i]);
	}

	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa

	printf("Interacciones...\n");

	//sala_destruir(sala);

	return 0;
}
