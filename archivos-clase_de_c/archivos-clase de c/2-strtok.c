#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANIO_NOMBRE 12
#define LARGO_MAX_LINEA 20
#define MODO_LECTURA "r" 

void leer_archivo(char* nombre_achivo, char* modo_apertura)
{
        FILE* archivo = fopen(nombre_achivo, modo_apertura);
        //chequeo si fopen no me devolvió NULL
        if(!archivo)
                return;
        
        char linea[LARGO_MAX_LINEA];

        char* leida = fgets(linea, LARGO_MAX_LINEA, archivo); //fgets devuelve NULL al final del archivo por eso me creo char* leida

        //separo la linea
        char* seccion = strtok(leida, "=");
        char* nombre = strtok(NULL, "=");

        while(leida){
                printf("%s: %s\n", seccion, nombre);

                leida = fgets(linea, LARGO_MAX_LINEA, archivo); //leo la linea próxima
                seccion = strtok(leida, "=");
                nombre = strtok(NULL, "=");
        }

        fclose(archivo);
}


int main()
{
        char archivo[TAMANIO_NOMBRE] = "playlist.txt";

        leer_archivo(archivo, MODO_LECTURA);

        return 0;
}