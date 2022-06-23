#include <stdio.h>
#include "pa2mm.h"
#include "primos.c"

#define INORDEN 0
#define PREORDEN 1
#define POSTORDEN 2

int main(int argc, char const *argv[])
{
	pa2m_afirmar(devuelve_siempre_numero_primo(11) == 0,"Funciona bien con primos" );
	return 0;
}
