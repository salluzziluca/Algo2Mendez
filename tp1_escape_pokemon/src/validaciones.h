#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_
#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
/*
* Valida si el valor pasado es no nulo. De ser asi, lo agrega al campo correspondiente. Devuelve 1 si el campo fue agregado, -1 si no.
*   
*
*/
int validar_y_agregar_campos_interaccion(char *campo_actual, char valor_aux[MAX_NOMBRE], struct interaccion *interaccion_actual);

int validar_y_agregar_campos_objeto(char *campo_actual, char valor_aux[MAX_NOMBRE], struct objeto *objeto_actual);

#endif // VALIDACIONES_H_
