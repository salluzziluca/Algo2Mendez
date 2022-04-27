#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

int elemento_es_igual_a(void *elemento1, void *elemento2)
{
	char *a = elemento1;
	char *b = elemento2;

	if(a && b && *a == *b)
		return 0;

	return -1;
}

void crear_lista_devuelve_lista_cantidad_cero_y_nodos_nulls()
{
  lista_t *lista = lista_crear();

  bool esta_vacia = lista_vacia(lista);
  pa2m_afirmar(esta_vacia == true, "La lista esta vacia");
  pa2m_afirmar(lista, "Se puede crear una lista");
  pa2m_afirmar(lista_tamanio(lista) == 0, "La cantidad de elementos es 0");
  pa2m_afirmar(lista_primero(lista) == NULL, "El nodo inicio es NULL");
  pa2m_afirmar(lista_ultimo(lista) == NULL, "El nodo fin es NULL");
  lista_destruir(lista);
}

void lista_insertar_aumenta_cantidad_Y_pone_elemento_donde_corresponde()
{ 
  lista_t *lista = NULL;
  char a = 'a';
  pa2m_afirmar(lista_insertar(lista, &a) == NULL, "No puedo insertar nada en una lista nula");
  lista = lista_crear();

  
  lista_insertar(lista, &a);
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &a, "Se puede insertar un elemento en la lista");
  pa2m_afirmar(lista->nodo_fin->siguiente == NULL, "El ultimo elemento apunta a NULL");

  char b = 'b';
  lista_insertar(lista, &b);
  pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &b, "El primer elemento apunta al segundo");

  char c = 'c';
  lista_insertar(lista, &c);
  pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento == &c, "El segundo elemento apunta al tercero");
  pa2m_afirmar(lista_tamanio(lista) == 3, "La cantidad de elementos es 3");

  char d = 'd';  
  lista_insertar_en_posicion(lista, &d, 2);
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &d, "Se puede insertar en posición correctamente");

  char e = 'e';
  lista_insertar_en_posicion(lista, &e, 0);
  pa2m_afirmar(lista_elemento_en_posicion(lista,0) == &e, "Se puede insertar en posición 0 correctamente");

  char f = 'f';
  lista_insertar_en_posicion(lista, &f, 100);
  pa2m_afirmar(lista_ultimo(lista) == &f, "Se puede insertar en posición mayor que cantidad correctamente");

  lista_insertar(lista, NULL);
  pa2m_afirmar(lista_ultimo(lista) == NULL, "Se puede insertar un elemento nulo");

  lista_destruir(lista);
}

void lista_quitar_saca_el_elemento_y_disminuye_cantidad()
{
  lista_t *lista = NULL;
  char *valor_quitado = lista_quitar(lista);
  pa2m_afirmar(valor_quitado == NULL, "No puedo quitar nada de una lista nula");
  lista = lista_crear();
	char a = 'a' , b = 'b', c = 'c', d = 'd', w = 'w';

	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &b);
	lista_insertar(lista, &w);
	
	valor_quitado = lista_quitar(lista);
  pa2m_afirmar(valor_quitado == &w, "Se puede quitar elemento correctamente");
  valor_quitado = lista_quitar_de_posicion(lista, 1);
  pa2m_afirmar(valor_quitado == &c, "Se puede quitar elemento de posición correctamente");
  valor_quitado = lista_quitar(lista);
  pa2m_afirmar(valor_quitado == &b, "Se puede quitar elemento correctamente");
  valor_quitado = lista_quitar_de_posicion(lista, 0);
  pa2m_afirmar(valor_quitado == &a, "Se puede quitar elemento de posición 0 correctamente");
  lista_destruir(lista);
}

void lista_elemento_lista_buscar_y_lista_primero_y_segundo_devuelven_elemento_correspondientes(){
	char a = 'a' , b = 'b', c = 'c', d = 'd', w = 'w';
  lista_t *lista = NULL;
  char *elemento = lista_elemento_en_posicion(lista, 0);
  pa2m_afirmar(elemento == NULL, "No puedo buscar elemento en posición en una lista nula");

  char buscado = 'c';
  char *elemento_c = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
  pa2m_afirmar(elemento_c == NULL, "No puedo buscar elemento en una lista vacia");

  void *primer_elemento = lista_primero(lista);
  pa2m_afirmar(primer_elemento == NULL, "No puedo buscar primer elemento en una lista vacia");

  void *ultimo_elemento = lista_ultimo(lista);
  pa2m_afirmar(ultimo_elemento == NULL, "No puedo buscar ultimo elemento en una lista vacia");

  lista = lista_crear();


	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &b);
	lista_insertar(lista, &w);

  elemento= lista_elemento_en_posicion(lista, 1);
  pa2m_afirmar(elemento == &c, "Se puede obtener el elemento en posición correctamente");
  elemento= lista_elemento_en_posicion(lista, 0);
  pa2m_afirmar(elemento == &a, "Se puede obtener el elemento en posición 0 correctamente");
  elemento= lista_elemento_en_posicion(lista, 37);
  pa2m_afirmar(elemento == &w, "Se puede obtener el elemento en posición mayor que cantidad correctamente");


	elemento_c = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
	pa2m_afirmar(elemento_c == &c, "Se puede buscar elemento correctamente");
  buscado = 'w';
  char *elemento_w = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
  pa2m_afirmar(elemento_w == &w, "Se puede buscar elemento final correctamente");
  buscado = 'z';
  char *elemento_z = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
  pa2m_afirmar(elemento_z == NULL, "No se puede buscar elemento inexistente");

  primer_elemento = lista_primero(lista);
  pa2m_afirmar(primer_elemento == lista_elemento_en_posicion(lista, 0), "Se puede obtener el primer elemento correctamente");
  ultimo_elemento = lista_ultimo(lista);
  pa2m_afirmar(ultimo_elemento == lista_elemento_en_posicion(lista, lista->cantidad - 1), "Se puede obtener el ultimo elemento correctamente");

  lista_destruir(lista);
}

void lista_iterador_se_crea_correctamente_itera_y_se_destruye(){  
  lista_t *lista = lista_crear();

  char a ='a';
  lista_insertar(lista, &a);

  lista_iterador_t *iterador = lista_iterador_crear(lista);
  pa2m_afirmar(iterador, "Se puede crear un iterador");
  pa2m_afirmar(iterador->corriente == lista->nodo_inicio, "El iterador se iniicializa en la primer posición de la lista");
  pa2m_afirmar(iterador->lista == lista, "El iterador apunta correctamente a la lista");

  lista_destruir(lista);
  lista_iterador_destruir(iterador);
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
  lista_insertar_aumenta_cantidad_Y_pone_elemento_donde_corresponde();

  pa2m_nuevo_grupo("Pruebas de quitados");
  lista_quitar_saca_el_elemento_y_disminuye_cantidad();

  pa2m_nuevo_grupo("Pruebas de busqueda");
  lista_elemento_lista_buscar_y_lista_primero_y_segundo_devuelven_elemento_correspondientes();

  pa2m_nuevo_grupo("Pruebas de creacion de iterador");
  lista_iterador_se_crea_correctamente_itera_y_se_destruye();
  
  /*pa2m_nuevo_grupo("Pruebas de destrucción");
  pruebas_de_destruccion_de_lista();*/

  // TODO: porbar insertar al principio y al final de una lista vacia y no vacia
  //TODO: porbar eliminar al principio y al final de una lista vacia y no vacia
  
  return pa2m_mostrar_reporte();
}
