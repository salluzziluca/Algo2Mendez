#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

#define INORDEN 0
#define PREORDEN 1
#define POSTORDEN 2

bool funcion_iteradora(void *dato, void *aux)
{
	dato = dato;
	aux = aux;
	return true;
}

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
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El arbol se crea con nodo raiz nulo");
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
	arbol->comparador = NULL;
	abb_insertar(arbol, &elemento10);
	pa2m_afirmar(abb_quitar(arbol, &elemento10) == NULL, "Se puede llamar a quitar con comparador nulo y devuelve NULL");

	arbol->comparador = comparar_cosas;
	int *destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un único elemento correctamente");
	pa2m_afirmar(abb_vacio(arbol) == true, "el arbol está vacio");
	abb_destruir(arbol);

	arbol = abb_crear(comparar_cosas);
	abb_insertar(arbol, &elemento10);
	destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un único elemento correctamente");
	pa2m_afirmar(abb_vacio(arbol) == true, "el arbol está vacio");

	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento9);;

	destruido = abb_quitar(arbol, &elemento9);
	pa2m_afirmar(*destruido == elemento9, "Se puede quitar un elemento hoja correctamente");
	abb_insertar(arbol, &elemento9);
	destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un elemento con un hijo izquierdo correctamente");
	abb_quitar(arbol, &elemento9);
	abb_insertar(arbol, &elemento10);

	abb_insertar(arbol, &elemento11);
	destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un nodo raiz con hijo derecho correctamente");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &elemento11, "El nodo raiz es el hijo derecho del quitado");

	abb_quitar(arbol, &elemento11);
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El arbol está vacio");
	abb_insertar(arbol, &elemento10);


	abb_insertar(arbol, &elemento15);
	abb_insertar(arbol, &elemento11);
	abb_insertar(arbol, &elemento12);
	abb_insertar(arbol, &elemento13);
	abb_insertar(arbol, &elemento14);
	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento15, "el elemento 15 esta en la derecha");
	destruido = abb_quitar(arbol, &elemento15);
	pa2m_afirmar(*destruido == elemento15, "Se puede quitar un elemento con un hijo derecho correctamente");
	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento14, "El nodo eliminado fue reemplazado correctamente");
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento7);
	destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar el nodo raiz correctamente");
	pa2m_afirmar(arbol->tamanio == 7, "El tamanio se actualiza correctamente");
	pa2m_afirmar(*(int *)arbol->nodo_raiz->elemento == elemento8, "El nodo raiz se reemplaza correctamente");
	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento14, "El nodo derecho se no se modifica");
	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->elemento == elemento6, "El nodo izquierdo se no se modifica");
	destruido = abb_quitar(arbol, &elemento13);
	pa2m_afirmar(*destruido == elemento13, "Se puede quitar un elemento otro nodo hoja correctamente");
	pa2m_afirmar(abb_tamanio(arbol) == 6, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento6); 
	pa2m_afirmar(abb_tamanio(arbol) == 5, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento7);
	pa2m_afirmar(abb_tamanio(arbol) == 4, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento14);
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento12);
	pa2m_afirmar(abb_tamanio(arbol) == 2, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento11);
	pa2m_afirmar(abb_tamanio(arbol) == 1, "El tamanio se actualiza correctamente");
	abb_quitar(arbol, &elemento8);
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El tamaño es cero");
	pa2m_afirmar(abb_vacio(arbol)==true, "El arbol está vacio");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es NULL");



	
	abb_destruir(arbol);
}

void abb_elminiar_sigue_eliminando(){
	abb_t* arbol = abb_crear(comparar_cosas);

	int elemento10 = 10, elemento9 = 9, elemento11 = 11;
	int elemento8 = 8, elemento12 = 12, elemento7 = 7, elemento13 = 13, elemento6 = 6, elemento14 = 14, elemento15 = 15;
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento11);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento12);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento13);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento14);
	abb_insertar(arbol, &elemento15);

	int *destruido = abb_quitar(arbol, &elemento15);
	pa2m_afirmar(*destruido == elemento15, "Puedo borrar un nodo hoja");

	pa2m_afirmar(abb_tamanio(arbol) == 9, "La cantidad de elementos es 9");

	abb_destruir(arbol);
}

void abb_eliminar_raiz_elimina_la_raiz_correctamente()
{
	abb_t *arbol = abb_crear(comparar_cosas);
	int elemento10 = 10, elemento9 = 9, elemento11 = 11;
	int elemento8 = 8, elemento12 = 12, elemento7 = 7, elemento13 = 13, elemento6 = 6, elemento14 = 14, elemento15 = 15;
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento11);
	abb_insertar(arbol, &elemento12);
	abb_insertar(arbol, &elemento15);
	abb_insertar(arbol, &elemento14);
	abb_insertar(arbol, &elemento13);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento6);
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento10, "El nodo raiz es 10");
	int *destruido = abb_quitar(arbol, &elemento10);
	pa2m_afirmar(*destruido == elemento10, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento9, "El nodo raiz es 9");
	destruido = abb_quitar(arbol, &elemento9);
	pa2m_afirmar(*destruido == elemento9, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento8, "El nodo raiz es 8");
	destruido = abb_quitar(arbol, &elemento8);
	pa2m_afirmar(*destruido == elemento8, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento7, "El nodo raiz es 7");
	destruido = abb_quitar(arbol, &elemento7);
	pa2m_afirmar(*destruido == elemento7, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento6, "El nodo raiz es 6");
	destruido = abb_quitar(arbol, &elemento6);
	pa2m_afirmar(*destruido == elemento6, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento11, "El nodo raiz es 11");
	destruido = abb_quitar(arbol, &elemento11);
	pa2m_afirmar(*destruido == elemento11, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento12, "El nodo raiz es 12");
	destruido = abb_quitar(arbol, &elemento12);
	pa2m_afirmar(*destruido == elemento12, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento15, "El nodo raiz es 15");
	destruido = abb_quitar(arbol, &elemento15);
	pa2m_afirmar(*destruido == elemento15, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento14, "El nodo raiz es 14");
	destruido = abb_quitar(arbol, &elemento14);
	pa2m_afirmar(*destruido == elemento14, "Se puede quitar un nodo raiz correctamente");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento13, "El nodo raiz es 13");
	destruido = abb_quitar(arbol, &elemento13);
	pa2m_afirmar(*destruido == elemento13, "Se puede quitar un nodo raiz correctamente");

	pa2m_afirmar(abb_tamanio(arbol) == 0, "El arbol esta vacio");
	



	abb_destruir(arbol);
}

void abb_buscar_busca_adecuadamente_en_todo_tipo_de_arbol()
{
	int elemento1 = 1, elemento2 = 2, elemento3 = 3, elemento4 = 4;
	abb_t *arbol = NULL;
	pa2m_afirmar(abb_buscar(arbol , &elemento1)== NULL, "Buscar elemento en arbol nulo devuelve NULL");
	arbol = abb_crear(comparar_cosas);
	arbol->comparador = NULL;
	pa2m_afirmar(abb_buscar(arbol , &elemento1)== NULL, "Buscar elemento en arbol con comparador nulo devuelve NULL");
	arbol->comparador = comparar_cosas;
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

void abb_recorrer_devuelve_todos_los_elementos_recorridos()
{
	abb_t *arbol = NULL;
	int *elementos[10];
	
	
	pa2m_afirmar(abb_recorrer(arbol,INORDEN,(void**)elementos, 10) == 0, "Se puede llamar a abb_recorrer con arbol nulo y devuelve 0");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_iteradora, NULL) == 0, "Se puede llamar a abb_con_cada_elemento con arbol nulo y devuelve 0");
	
	arbol = abb_crear(comparar_cosas);
	
	pa2m_afirmar(abb_recorrer(arbol,INORDEN,(void**)elementos, 10) == 0, "Se puede llamar a abb_recorrer con arbol vacio y devuelve 0");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_iteradora, NULL) == 0, "Se puede llamar a abb_con_cada_elemento con arbol vacio y devuelve 0");

	int elemento1 = 1, elemento2 = 2, elemento3 = 3, elemento4 = 4;
	abb_insertar(arbol, &elemento1);
	pa2m_afirmar(abb_recorrer(arbol,INORDEN,(void**)elementos, 10) == 1, "Se puede llamar a abb_recorrer con 1 elemento y devuelve el tamaño correspondiente");
	
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_iteradora, NULL) == 1, "Se puede llamar a abb_con_cada_elemento con 1 elemento y devuelve el tamaño correspondiente");

	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	pa2m_afirmar(abb_recorrer(arbol,INORDEN,(void**)elementos, 10) == 4, "Se puede llamar a abb_recorrer con arbol no vacio y devuelve el tamaño correspondiente");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_iteradora, NULL) == 4, "Se puede llamar a abb_con_cada_elemento con arbol no vacio y devuelve el tamaño correspondiente");

	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, NULL) == 0, "Se puede llamar a abb_con_cada_elemento con funcion NULL y devuelve cero");

	abb_destruir(arbol);

	int *elementoss[2];
	arbol = abb_crear(comparar_cosas);

	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	size_t recorridos = abb_recorrer(arbol,INORDEN,(void**)elementoss, 2);
	pa2m_afirmar(recorridos == 2, "Puedo recorrer inorder menos elementos del total");
	recorridos = abb_recorrer(arbol,POSTORDEN,(void**)elementoss, 2);
	pa2m_afirmar(recorridos == 2, "Puedo recorrer postorden menos elementos del total");
	recorridos = abb_recorrer(arbol,PREORDEN,(void**)elementoss, 2);
	pa2m_afirmar(recorridos == 2, "Puedo recorrer preorder menos elementos del total");

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

	pa2m_nuevo_grupo("Mas Pruebas de Quitado");
	abb_elminiar_sigue_eliminando();

	pa2m_nuevo_grupo("Pruebas de quitar raiz");
	abb_eliminar_raiz_elimina_la_raiz_correctamente();

	pa2m_nuevo_grupo("Pruebas de Busqueda");
	abb_buscar_busca_adecuadamente_en_todo_tipo_de_arbol();

	pa2m_nuevo_grupo("Pruebas de tamaño");
	abb_tamanio_y_vacio_muestran_adecuadamente_el_tamanio_del_arbol();

	pa2m_nuevo_grupo("Pruebas de recorrido");
	abb_recorrer_devuelve_todos_los_elementos_recorridos();

	return pa2m_mostrar_reporte();
}
