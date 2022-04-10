#include "validaciones.h"
#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int validar_y_agregar_campos_interaccion(char *campo_actual, char valor_aux[MAX_NOMBRE], struct interaccion *interaccion_actual)
{
        if(campo_actual!=NULL)
        {
                strcpy(valor_aux,campo_actual);
                return 1;
        }
        else
        {
                return -1;
        }
        return 0;
}
int validar_y_agregar_campos_objeto(char *campo_actual, char valor_aux[MAX_NOMBRE], struct objeto *objeto_actual)
{
        if(campo_actual!=NULL)
        {
                strcpy(valor_aux,campo_actual);
                return 1;
        }
        else
        {
                return -1;
        }
        return 0;
}