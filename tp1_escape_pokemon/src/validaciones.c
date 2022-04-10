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

int validar_y_agregar_campos_interaccion(char valor_aux[MAX_NOMBRE], char *campo_actual, struct interaccion *interaccion_actual, char campo[MAX_NOMBRE])
{
        if(strcmp(campo, "objeto_parametro")== 0|| strcmp(campo, "accion_objeto")== 0){
                if(valor_aux != NULL && strcmp(valor_aux, "_") != 0){
                        strcpy(campo_actual,valor_aux);
                        return 1;
                }
                else if(valor_aux != NULL){
                        strcpy(campo_actual,"");
                        return 1;
        }
        else
        {
                return -1;
        }
        }
        else{
                if(valor_aux != NULL && strcmp(valor_aux, "") != 0)
                {
                        strcpy(campo_actual,valor_aux);
                        return 1;
                }
                else
                {
                        return -1;
                }
        }
        return 0;
}

/*int validar_y_agregar_campos_interaccion(char valor_aux[MAX_NOMBRE], char *campo_actual, struct interaccion *interaccion_actual)
{
        if(valor_aux != NULL && strcmp(valor_aux, "") != 0)
        {
                strcpy(campo_actual,valor_aux);
                return 1;
        }
        else
        {
                return -1;
        }
        return 0;
}*/
int validar_y_agregar_campos_objeto(char valor_aux[MAX_NOMBRE], char *campo_actual, struct objeto *objeto_actual)
{
        if(valor_aux!=NULL && strcmp(valor_aux, "") != 0)
        {
                strcpy(campo_actual,valor_aux);
                return 1;
        }
        else
        {
                return -1;
        }
        return 0;
}