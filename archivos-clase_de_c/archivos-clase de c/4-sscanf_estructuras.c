#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"

typedef struct colaborador colaborador_t; //quiero usar el tipo de dato struct colaborador como colaborador_t

#define TAMANIO_NOMBRE 100
#define LARGO_MAX_LINEA 20
#define MODO_LECTURA "r"
#define ERROR -1 

void leer_archivo(char *nombre_achivo, char *modo_apertura)
{
        FILE *archivo = fopen(nombre_achivo, modo_apertura);
    
        if(!archivo)
                return;
        
        char linea1[LARGO_MAX_LINEA];
        char linea2[LARGO_MAX_LINEA];

        char *linea_leida1 = fgets(linea1, LARGO_MAX_LINEA, archivo); 
        char *linea_leida2 = fgets(linea2, LARGO_MAX_LINEA, archivo);
        
        colaborador_t colab;
        //separo la linea
        sscanf(linea1, "%*[^=]=%[^\n]\n", colab.nombre); // el * le dice que lo saltee
        sscanf(linea2, "%*[^=]=%[^\n]\n", colab.cancion);

        while(linea_leida1 && linea_leida2){
                printf("Nombre: %s - Canción: %s\n", colab.nombre, colab.cancion);
                linea_leida1 = fgets(linea1, LARGO_MAX_LINEA, archivo); 
                linea_leida2 = fgets(linea2, LARGO_MAX_LINEA, archivo);
        
                sscanf(linea1, "%*[^=]=%[^\n]\n", colab.nombre);
                sscanf(linea2, "%*[^=]=%[^\n]\n", colab.cancion);   
        }

        fclose(archivo);
}


int main()
{

        leer_archivo("playlist.txt", MODO_LECTURA);

        return 0;
}
