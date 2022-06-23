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
const char *interaccion_valida(bool interaccion_valida);


#endif // VALIDACIONES_H_
