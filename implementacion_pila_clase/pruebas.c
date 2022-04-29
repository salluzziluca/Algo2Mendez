#include "src/pila.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

void crear_una_pila_me_devuelve_una_pila_de_tamanio_0_y_tope_nulo()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila!=NULL, "La pila creada es válida");
	pa2m_afirmar(pila_cantidad(pila)==0, "La pila creada tiene tamaño 0");
	pa2m_afirmar(pila_tope(pila)==NULL, "La pila creada tiene tope NULL");

	pila_destruir(pila);
}

void apilar_un_elemento_incrementa_el_tamanio_de_la_pila_y_el_tope_es_el_ultimo_elemento_apilado()
{
	pila_t *pila = pila_crear();

	int elemento1 = 10;
	int elemento2 = 50;
	int elemento3 = 40;

	pa2m_afirmar(pila_apilar(pila, &elemento1) == 0, "Puedo apilar un elemento");
	pa2m_afirmar(pila_cantidad(pila)==1, "El tamaño de la pila es 1");
	pa2m_afirmar(pila_tope(pila)==&elemento1, "El tope de la pila es el correcto");

	pa2m_afirmar(pila_apilar(pila, &elemento2) == 0, "Puedo apilar un segundo elemento");
	pa2m_afirmar(pila_cantidad(pila)==2, "El tamaño de la pila es 2");
	pa2m_afirmar(pila_tope(pila)==&elemento2, "El tope de la pila es el correcto");

	pa2m_afirmar(pila_apilar(pila, &elemento3) == 0, "Puedo apilar un tercer elemento");
	pa2m_afirmar(pila_cantidad(pila)==3, "El tamaño de la pila es 3");
	pa2m_afirmar(pila_tope(pila)==&elemento3, "El tope de la pila es el correcto");

	pila_destruir(pila);
}

void apilar_un_elemento_nulo_apila_el_elemento()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_apilar(pila, NULL) == 0, "Puedo apilar un elemento NULL");
	pa2m_afirmar(pila_cantidad(pila)==1, "El tamaño de la pila es 1");
	pa2m_afirmar(pila_tope(pila)==NULL, "El tope de la pila es NULL");

	pila_destruir(pila);
}

void apilar_en_una_pila_nula_es_un_error()
{
	int elemento = 5;
	pa2m_afirmar(pila_apilar(NULL, &elemento)!=0, "No puedo apilar nada en una pila nula");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de pila");
	crear_una_pila_me_devuelve_una_pila_de_tamanio_0_y_tope_nulo();

	pa2m_nuevo_grupo("Pruebas de apilar");
	apilar_un_elemento_incrementa_el_tamanio_de_la_pila_y_el_tope_es_el_ultimo_elemento_apilado();
	apilar_un_elemento_nulo_apila_el_elemento();
	apilar_en_una_pila_nula_es_un_error();

	return pa2m_mostrar_reporte();
}
