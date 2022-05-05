#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

typedef struct cosa
{
	int clave;
	char contenido[10];
} cosa;

cosa *crear_cosa(int clave)
{
	cosa *c = (cosa *)malloc(sizeof(cosa));
	if (c)
		c->clave = clave;
	return c;
}

int comparar_cosas(void *elemento1, void *c2)
{
	cosa *cosa1 = elemento1;
	cosa *cosa2 = c2;
	return cosa1->clave - cosa2->clave;
}

void abb_crear_crea_e_inicializa_todo_correctamente()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(arbol, "El arbol se crea");
	pa2m_afirmar(arbol->nodo_raiz != NULL, "El arbol se crea con un nodo raiz");
	pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL, "El nodo raiz se inicializa con un hijo izquierdo NULL");
	pa2m_afirmar(arbol->nodo_raiz->derecha == NULL, "El nodo raiz se inicializa con un hijo derecho NULL");
	pa2m_afirmar(arbol->nodo_raiz->elemento == NULL, "El nodo raiz se inicializa con un elemento NULL");
	pa2m_afirmar(arbol->comparador == comparar_cosas, "El arbol se inicializa con un comparador correcto");
	pa2m_afirmar(arbol->tamanio == 0, "El arbol se inicializa con un tamanio 0");
	abb_destruir(arbol);
}

void abb_insertar_inserta_los_elementos_correctamente()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	int elemento1 = 1;
	abb_insertar(arbol, &elemento1);
	pa2m_afirmar(arbol->nodo_raiz->elemento == &elemento1, "Se puede cargar un primer elemento correctamente");
	abb_destruir(arbol);
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de Creacion de ABB");
	abb_crear_crea_e_inicializa_todo_correctamente();

	pa2m_nuevo_grupo("Pruebas de Insertar en ABB");
	abb_insertar_inserta_los_elementos_correctamente();

	return pa2m_mostrar_reporte();
}
