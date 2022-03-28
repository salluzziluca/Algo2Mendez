#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANIO_NOMBRE 100
#define LARGO_MAX_LINEA 20
#define MODO_LECTURA "r"
#define ERROR -1 

void leer_archivo(char* nombre_achivo, char* modo_apertura)
{
        FILE *archivo = fopen(nombre_achivo, modo_apertura);
        //chequeo si fopen no me devolvió NULL
        if(!archivo)
                return;
        
        char linea[LARGO_MAX_LINEA];

        char *linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo); 
       
        char primer_string[TAMANIO_NOMBRE];
        char segundo_string[TAMANIO_NOMBRE];

        //separo la linea
        int resultado_split = sscanf(linea, "%[^=]=%[^\n]\n", primer_string, segundo_string);

        while(linea_leida && resultado_split != ERROR){
                printf("%s: %s\n", primer_string, segundo_string);

                linea_leida = fgets(linea, LARGO_MAX_LINEA, archivo); //leo la linea próxima
                resultado_split = sscanf(linea, "%[^=]=%[^\n]\n", primer_string, segundo_string);
        }

        fclose(archivo);
}


int main()
{
        leer_archivo("playlist.txt", MODO_LECTURA);

        return 0;
}