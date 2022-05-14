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

int comparar_cosas(void *elemento1, void *elemento2s)
{
	cosa *cosa1 = elemento1;
	cosa *cosa2 = elemento2s;
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
	int elemento2 = 2;
	abb_insertar(arbol, &elemento2);
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == &elemento2, "Se puede cargar un segundo elemento correctamente");
	int elemento3 = 3;
	abb_insertar(arbol, &elemento3);
	pa2m_afirmar(arbol->nodo_raiz->derecha->derecha->elemento == &elemento3, "Se puede cargar un tercer elemento correctamente");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos es 3");
	int elemento4 = -1;
	abb_insertar(arbol, &elemento4);
	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == &elemento4, "Se puede cargar un cuarto elemento correctamente");
	pa2m_afirmar(abb_tamanio(arbol) == 4, "La cantidad de elementos es 4");
	pa2m_afirmar(abb_buscar(arbol, &elemento4) == &elemento4, "Funciona");
	abb_destruir(arbol);
}

void abb_quitar_quita_los_elementos_correctamente()
{
	int elemento10 = 10, elemento9 = 9, elemento11 = 11;
	int elemento8 = 8, elemento12 = 12, elemento7 = 7, elemento13 = 13, elemento6 = 6, elemento14 = 14, elemento15 = 15;
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_quitar(arbol, &elemento10) == NULL, "Se puede llamar a abb_quitar en arbol nulo y devuelve NULL");

	arbol = abb_crear(comparar_cosas);
	abb_insertar(arbol, &elemento10);
	int *destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un único elemento correctamente");
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento11);
	destruido = abb_quitar(arbol, &elemento9);
	pa2m_afirmar(*destruido == elemento9, "Se puede quitar un elemento hoja correctamente");

	abb_insertar(arbol, &elemento14);
	abb_insertar(arbol, &elemento12);
	abb_insertar(arbol, &elemento15);
	abb_insertar(arbol, &elemento11);
	abb_insertar(arbol, &elemento13);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento7);

	destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(arbol->tamanio == 11, "El tamanio se actualiza correctamente");
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar el nodo raiz correctamente");
	
	abb_destruir(arbol);
}

void abb_buscar_busca_adecuadamente_en_todo_tipo_de_arbol()
{
	int elemento1 = 1, elemento2 = 2, elemento3 = 3, elemento4 = 4;
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_buscar(arbol , &elemento1)== NULL, "Buscar elemento en arbol nulo devuelve NULL");
	arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(abb_buscar(arbol, &elemento1) == NULL, "Se puede buscar elemento en arbol vacio y devuelve NULL");
	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	pa2m_afirmar(abb_buscar(arbol, &elemento4) == &elemento4, "Se puede encontrar elemento en arbol no vacio " );
	abb_destruir(arbol);
}

void abb_tamanio_y_vacio_muestran_adecuadamente_el_tamanio_del_arbol(){
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_vacio(arbol)== true, "se puede llamar a abb vacio en arbol nulo y devuelve true");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Se puede llamar a abb_tamanio con arbol nulo y devuelve 0");
	arbol = abb_crear(comparar_cosas);
	pa2m_afirmar(abb_vacio(arbol)== true, "se puede llamar a abb vacio en arbol vacio y devuelve true");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Se puede llamar a abb_tamanio con arbol vacio y devuelve 0");
	int elemento1 = 1, elemento2 = 2, elemento3 = 3, elemento4 = 4;
	abb_insertar(arbol, &elemento1);
	pa2m_afirmar(abb_vacio(arbol)== false, "se puede llamar a abb vacio en arbol no vacio y devuelve false");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "Se puede llamar a abb_tamanio con arbol no vacio y devuelve el tamaño correspondiente");
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_destruir(arbol);

	
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de Creacion de ABB");
	abb_crear_crea_e_inicializa_todo_correctamente();

	pa2m_nuevo_grupo("Pruebas de Inserccion");
	abb_insertar_inserta_los_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de Quitado");
	abb_quitar_quita_los_elementos_correctamente();

	pa2m_nuevo_grupo("Pruebas de Busqueda");
	abb_buscar_busca_adecuadamente_en_todo_tipo_de_arbol();

	pa2m_nuevo_grupo("Pruebas de tamaño");
	abb_tamanio_y_vacio_muestran_adecuadamente_el_tamanio_del_arbol();

	return pa2m_mostrar_reporte();
}
