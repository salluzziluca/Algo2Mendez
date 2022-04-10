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
* Valida si el resultado de la comparacion entre input y registro de interacciones 
* es correcto. De ser verdadero, se modiifica un string con el resultado de la     * comparacion. 
* Este string sera luego utilizado para imprimir por pantalla las interacciones
* validas.
*/
int interracion_valida(bool interaccion_valida, char *string_validez);

/*
* Valida si el valor pasado es no nulo. De ser asi, lo agrega al campo correspondiente del estruct interacción. Devuelve 1 si el campo fue agregado, -1 si no.
*   
*
*/
int validar_y_agregar_campos_interaccion(char valor_aux[MAX_NOMBRE], char *campo_actual, struct interaccion *interaccion_actual);

/*
* Valida si el valor pasado es no nulo. De ser asi, lo agrega al campo correspondiente del struct objeto. Devuelve 1 si el campo fue agregado, -1 si no.
*   
*
*/
int validar_y_agregar_campos_objeto(char valor_aux[MAX_NOMBRE], char *campo_actual, struct objeto *objeto_actual);

#endif // VALIDACIONES_H_
