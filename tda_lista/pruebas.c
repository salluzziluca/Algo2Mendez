#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"
void crear_lista_devuelve_lista_cantidad_cero_y_nodos_nulls()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista != NULL, "Se puede crear una lista");
  pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos es 0");
  pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicio es NULL");
  pa2m_afirmar(lista->nodo_fin == NULL, "El nodo fin es NULL");
}

void pruebas_de_inserccion_de_objeto()
{
  char a = 'a';

  lista_t *lista = lista_crear();

  pa2m_afirmar(lista != NULL, "Se puede crear una lista");
  lista_insertar(lista, &a);
  pa2m_afirmar(lista->nodo_inicio->elemento == &a, "Se puede insertar un elemento en la lista");
  pa2m_afirmar(lista->nodo_fin->siguiente == NULL, "El ultimo elemento apunta a NULL");

  char b = 'b';

  lista_insertar(lista, &b);
  pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == &b, "El primer elemento apunta al segundo");

  char c = 'c';
  
  lista_insertar(lista, &c);
  pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento == &c, "El segundo elemento apunta al tercero");
  pa2m_afirmar(lista->cantidad == 3, "La cantidad de elementos es 3");
}

void pruebas_de_destruccion_de_lista()
{
  lista_t *lista = lista_crear();
	char a = 'a', b = 'b';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);

  lista_destruir(lista);
  pa2m_afirmar(lista == NULL, "Se destruyó la lista");
}
int main() {
  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  crear_lista_devuelve_lista_cantidad_cero_y_nodos_nulls();

  pa2m_nuevo_grupo("Pruebas de insercción");
  pruebas_de_inserccion_de_objeto();
  
  pa2m_nuevo_grupo("Pruebas de destrucción");
  pruebas_de_destruccion_de_lista();
  // TODO: porbar insertar al principio y al final de una lista vacia y no vacia
  //TODO: porbar eliminar al principio y al final de una lista vacia y no vacia
  
  return pa2m_mostrar_reporte();
}
