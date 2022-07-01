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

void ayuda(){
	printf("Bienvenido al maravilloso mundo de los Pokemon, donde. . .\n¿Eh? ¿Donde estas? Te despertas en una habitacion desconocida y no recordas lo que estabas haciendo.\nMiras a tu alrededor y notas una unica puerta cerrada,\nla unica posibilidad para salir afuera y escapar de este lugar.\nPodras lograrlo?\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("El juego te va a pedir que ingreses una interaccion\nLuego un objeto, luego un segundo objeto(opcional)\n");
	printf("Al descubrir y abrir, vas a ir descubriendo nuevos objetos que \nte van a ayudar a salir de la habitacion\n");
	printf("Los comandos disponibles son los siguientes:\n");
	printf("describir: describe el objeto\n");
	printf("agarrar: agarra un objeto (recorda que hay objetos que necesitan ser agarrados para ser usados)\n");
	printf("examinar: examina el objeto\n");
	printf("abrir: abre un objeto (puede que necesites de una llave o simil)\n");
	printf("salir: utiliza el objeto para salir\n");
	sleep(5);
}

int main(int argc, char *argv[])
{	
	sala_t *sala = sala_crear_desde_archivos(ARCHIVO_OBJETOS, ARCHIVO_INTERACCIONES);

	if (sala == NULL){
		printf("Error al crear la sala de escape\n");
		return -1;
	}
		bool empezar_juego = false;
		printf("\n");
		printf("\n");
		ayuda();
		printf("\n");
		printf("Queres empezar el juego? (s/n)");
		char respuesta[10];
		scanf("%s", respuesta);
		if(strcmp(respuesta, "s") == 0){
			empezar_juego = true;
		}
	while(!sala_escape_exitoso(sala) && empezar_juego){
		if(empezar_juego){
		printf("--------------------------------------------------------------------------------------------------------------------\n");
			int cantidad_objetos_conocidos = 0;
			int cantidad_objetos_poseidos = 0;
			char **objeto_conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_objetos_conocidos);
			char **objetos_poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_objetos_poseidos);
			bool pidio_ayuda = false;
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
			if(strcmp(verbo, "ayuda") == 0){
			}
			if(!pidio_ayuda){
				printf("Que objeto deseas usar? \n");
				char objeto[MAX_NOMBRE];
				scanf("%s", objeto);
				if(strcmp(verbo, "agarrar")== 0 ){
					bool agarro = sala_agarrar_objeto(sala, objeto);
					necesito_interaccion = false;
					if(agarro)
						printf("Agarraste el objeto\n");
					else
						printf("No pudiste agarrar el objeto\n");
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
					int cantidad = sala_ejecutar_interaccion(sala, verbo, objeto, objeto2,mostrar_mensaje, aux);
					if(cantidad == 0)
						printf("No se puede realizar esa accion\n");
					sleep(3);
				}
			}
			free(objeto_conocidos);
			free(objetos_poseidos);
		}
	}

		printf("\n");
		printf("Gracias por jugar!(o no)\n");
	sala_destruir(sala);

	return 0;
}
