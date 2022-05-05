#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

typedef struct cosa {
	int clave;
	char contenido[10];
} cosa;

int comparar_cosas(void *c1, void *c2)
{
	cosa *cosa1 = c1;
	cosa *cosa2 = c2;
	return cosa1->clave - cosa2->clave;
}
pa2m_nuevo_grupo("Pruebas de Creación de ABB"){
	abb_t *abb = abb_crear(comparar_cosas);
	pa2m_afirmar(abb, "El arbol se crea");
	pa2m_afirmar(abb->nodo_raiz != NULL, "El arbol se crea con un nodo raiz");
	pa2m_afirmar(abb->nodo_raiz->izquierda == NULL, "El nodo raiz se inicializa con un hijo izquierdo NULL");
	pa2m_afirmar(abb->nodo_raiz->derecha == NULL, "El nodo raiz se inicializa con un hijo derecho NULL");
	pa2m_afirmar(abb->nodo_raiz->elemento == NULL, "El nodo raiz se inicializa con un elemento NULL");
	pa2m_afirmar(abb->comparador == comparar_cosas, "El arbol se inicializa con un comparador correcto");
	pa2m_afirmar(abb->tamanio == 0, "El arbol se inicializa con un tamanio 0");
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de Creacion de ABB");
  
	return pa2m_mostrar_reporte();
}
