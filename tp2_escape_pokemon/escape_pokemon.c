#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARCHIVO_OBJETOS argv[1] 
#define ARCHIVO_INTERACCIONES argv[2]
#define MAX_NOMBRE 20
#define MAX_INTERACCION 100;
void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}

int main(int argc, char *argv[])
{	
	sala_t *sala = sala_crear_desde_archivos(ARCHIVO_OBJETOS, ARCHIVO_INTERACCIONES);

	if (sala == NULL){
		printf("Error al crear la sala de escape\n");
		return -1;
	}
	while(!sala_escape_exitoso(sala)){
		printf("\n");
		printf("\n");
		printf("\n");
		printf("--------------------------------------------------------");
		printf("\n");
		int cantidad_objetos_conocidos = 0;
		int cantidad_objetos_poseidos = 0;
		char **objeto_conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_objetos_conocidos);
		char **objetos_poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_objetos_poseidos);
		bool necesito_interaccion = true;

		printf("Conoces los siguientes objetos:\n");
		for (int i = 0; i < cantidad_objetos_conocidos; i++){
			printf("%s\n", objeto_conocidos[i]);
		}

		printf("Posees los siguientes objetos:\n");
		for (int i = 0; i < cantidad_objetos_poseidos; i++){
			printf("%s\n", objetos_poseidos[i]);
		}
		printf("\n");
		printf("\n");
		printf("Que accion deseas realizar? (acciones posibles describir, agarrar, examinar, abrir, salir)\n");
		char verbo[MAX_NOMBRE];
		scanf("%s", verbo);

		printf("Que objeto deseas usar? \n");
		char objeto[MAX_NOMBRE];
		scanf("%s", objeto);
		if(strcmp(verbo, "agarrar")== 0 ){
			sala_agarrar_objeto(sala, objeto);
			necesito_interaccion = false;
			sleep(2);
		}
		if(strcmp(verbo, "describir") == 0){
			printf("%s\n", sala_describir_objeto(sala, objeto));
			necesito_interaccion = false;
			sleep(2);
		}
		if(necesito_interaccion){
		printf("Que segundo objeto deseas usar? (opcional, ingresar 'n' para especificar 'ningun objeto')\n");
		char objeto2[MAX_NOMBRE] = "";
		scanf("%s", objeto2);
		if(strcmp(objeto2, "n") == 0)
			strcpy(objeto2, "");
		void *aux = NULL;
		sala_ejecutar_interaccion(sala, verbo, objeto, objeto2,mostrar_mensaje, aux);
		sleep(3);
		}
		free(objeto_conocidos);
		free(objetos_poseidos);
	}

	sala_destruir(sala);

	return 0;
}
