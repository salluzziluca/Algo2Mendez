#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	sala_t *sala = sala_crear_desde_archivos("???", "???");

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}


	sala_destruir(sala);

	return 0;
}
