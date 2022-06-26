#include "estructuras.h"
#include "sala.h"
#include <stdlib.h>

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	return NULL;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return NULL;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	return false;
}

void sala_destruir(sala_t *sala)
{
}
