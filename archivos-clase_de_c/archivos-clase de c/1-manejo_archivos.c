#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LARGO_MAX_LINEA 20
#define MODO_LECTURA "r"

void leer_archivo(char *nombre_achivo, char *modo_apertura)
{
	FILE *archivo = fopen(nombre_achivo, modo_apertura);
	//chequeo si fopen no me devolvió NULL
	if(!archivo)
		return;
	

	char linea[LARGO_MAX_LINEA];

	char *leida = fgets(linea, LARGO_MAX_LINEA, archivo); 

	while(leida){
		printf("%s\n", linea); 
		leida = fgets(linea, LARGO_MAX_LINEA, archivo); //leo la linea próxima
	}

	fclose(archivo);
}


int main()
{
	leer_archivo("playlist.txt", MODO_LECTURA);

	return 0;
}