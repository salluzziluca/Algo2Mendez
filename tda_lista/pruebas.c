#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

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

int main() {
  pa2m_nuevo_grupo("Pruebas de insercción");
  pruebas_de_inserccion_de_objeto();
  
  return pa2m_mostrar_reporte();
}
