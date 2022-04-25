#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"
void crear_lista_devuelve_lista_cantidad_cero_y_nodos_nulls()
{
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista, "Se puede crear una lista");
  pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos es 0");
  pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicio es NULL");
  pa2m_afirmar(lista->nodo_fin == NULL, "El nodo fin es NULL");
  lista_destruir(lista);
}

void pruebas_de_inserccion_de_objeto()
{ 
  char a = 'a';

  lista_t *lista = lista_crear();

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

  char d = 'd';  
  lista_insertar_en_posicion(lista, &d, 2);
  pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento == &d, "Se puede insertar en posición correctamente");

  char e = 'e';
  lista_insertar_en_posicion(lista, &e, 0);
  pa2m_afirmar(lista->nodo_inicio->elemento == &e, "Se puede insertar en posición 0 correctamente");

  char f = 'f';
  lista_insertar_en_posicion(lista, &f, 100);
  pa2m_afirmar(lista->nodo_fin->elemento == &f, "Se puede insertar en posición mayor que cantidad correctamente");

  lista_destruir(lista);
}

void pruebas_de_quitado()
{
  lista_t *lista = lista_crear();
	char a = 'a' , b = 'b', c = 'c', d = 'd', w = 'w';

	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &b);
	lista_insertar(lista, &w);
	
	char *valor_quitado = lista_quitar(lista);
  pa2m_afirmar(valor_quitado == &w, "Se puede quitar elemento correctamente");
  char* segundo_valor_quitado = lista_quitar_de_posicion(lista, 1);
  pa2m_afirmar(segundo_valor_quitado == &c, "Se puede quitar elemento de posición correctamente");
  char* tercer_valor_quitado = lista_quitar(lista);
  pa2m_afirmar(tercer_valor_quitado == &b, "Se puede quitar elemento correctamente");
  lista_destruir(lista);
}

void pruebas_de_busqueda(){

  lista_t *lista = lista_crear();
	char a = 'a' , b = 'b', c = 'c', d = 'd', w = 'w';

	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &b);
	lista_insertar(lista, &w);

 char *elemento1= lista_elemento_en_posicion(lista, 1);
  pa2m_afirmar(elemento1 == &c, "Se puede obtener el elemento en posición correctamente");

}

//TODO: Fijarme de implementar correctamente una prueba de destruir todo
/*int destructor(void *elemento)
{
  free(elemento);
  return 0;
}

void pruebas_de_destruccion_de_lista()
{
  lista_t *lista = lista_crear();

  lista_insertar(lista, malloc(sizeof(char)));
	lista_insertar(lista, malloc(sizeof(char)));

  lista_destruir_todo(lista, destructor);
  pa2m_afirmar(lista == NULL, "Se destruyó la lista");
}*/ 

int main() {
  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  crear_lista_devuelve_lista_cantidad_cero_y_nodos_nulls();

  pa2m_nuevo_grupo("Pruebas de insercción");
  pruebas_de_inserccion_de_objeto();

  pa2m_nuevo_grupo("Pruebas de quitados");
  pruebas_de_quitado();

  pa2m_nuevo_grupo("Pruebas de busqueda");
  pruebas_de_busqueda();
  
  /*pa2m_nuevo_grupo("Pruebas de destrucción");
  pruebas_de_destruccion_de_lista();*/

  // TODO: porbar insertar al principio y al final de una lista vacia y no vacia
  //TODO: porbar eliminar al principio y al final de una lista vacia y no vacia
  
  return pa2m_mostrar_reporte();
}
