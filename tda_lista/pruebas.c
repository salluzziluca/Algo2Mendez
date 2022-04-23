#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

int main() {
  pa2m_nuevo_grupo("Pruebas y mas pruebas");
  //TODO: crear una prueba que me verifique la inserccion correcta de un elemento
  char a = 'a';
  lista_t *lista1 = lista_crear();
  pa2m_afirmar(lista, "se puede crear una lista");
  lista_insertar(lista, &a);
  pa2m_afirmar(lista->nodo_inicio->elemento == &a, "se puede insertar un elemento en la lista");

  return pa2m_mostrar_reporte();
}
