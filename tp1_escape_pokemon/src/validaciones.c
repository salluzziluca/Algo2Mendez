#include "validaciones.h"
#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int interracion_valida(bool interaccion_valida, char *string_validez)
{
	if(interaccion_valida)
		strcpy(string_validez, "Válido");
	else
		strcpy(string_validez, "Inválido");
	return 0;
}

int validar_y_agregar_campos_interaccion(char *campo_actual, char valor_aux[MAX_NOMBRE], struct interaccion *interaccion_actual)
{
        if(campo_actual != NULL || strcmp(campo_actual, "\0") != 0)
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
        if(campo_actual!=NULL|| strcmp(campo_actual, "\0") != 0)
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