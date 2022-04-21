#include "src/pila.h"
#include <stdio.h>
#define MAX_NOMBRE 20
#include <string.h>

struct alumno {
	int padron;
	char nombre[MAX_NOMBRE];
};

void mostrar_alumno(void *_alumno)
{
	struct alumno *alumno = _alumno;
	printf("Nombre: %s, padron: %i\n", alumno->nombre, alumno->padron);
}

void mostrar_int(void *_n)
{
	int *n = _n;
	printf("%i\n", *n);
}

int comparar_nombre_alumno(void *a, void *n)
{
	struct alumno *alumno = a;
	char *nombre = n;

	return strcmp(alumno->nombre, nombre);
}

int comparar_alumnos(void *a1, void *a2)
{
	struct alumno *alumno1 = a1;
	struct alumno *alumno2 = a2;


	return strcmp(alumno1->nombre, alumno2->nombre);
}


int main(int argc, char *argv[])
{
	struct alumno alumnos[] = { { .padron = 12345, .nombre = "Lucas" },
				    { .padron = 54321, .nombre = "Noah" },
				    { .padron = 98765, .nombre = "Enrique" },
				    { .padron = 56789, .nombre = "Lisandro" },
				    { .padron = 12312, .nombre = "Omar" } };

	pila_t *pila = pila_crear();

	pila_apilar(pila, alumnos + 0);
	pila_apilar(pila, alumnos + 1);
	pila_apilar(pila, alumnos + 2);
	pila_apilar(pila, &alumnos + 3);

	//pila_mostrar_elementos(pila, &mostrar_alumno);

	//struct alumno *noah = pila_buscar(pila, comparar_nombre_alumno, "Sarasa");
	struct alumno auxiliar;
	strcpy(auxiliar.nombre, "Noah");

	struct alumno *noah = pila_buscar(pila, comparar_alumnos, &auxiliar);

	if(noah)
		mostrar_alumno(noah);
	else
		printf("No existe el alumno buscado\n");

	/* while (pila_tope(pila)) { */
	/* 	struct alumno *alumno = pila_desapilar(pila); */
	/* 	mostrar_alumno(alumno); */
	/* } */

	pila_destruir(pila);

	return 0;
}
