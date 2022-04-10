#include "validaciones.h"
#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char *interaccion_valida(bool interaccion)
{
	if(interaccion)
                return "Válido";
        return "Inválido";
}