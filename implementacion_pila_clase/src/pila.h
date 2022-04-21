#ifndef PILA_H_
#define PILA_H_


typedef struct pila pila_t;

pila_t *pila_crear();

int pila_apilar(pila_t *pila, void *elemento);

void *pila_desapilar(pila_t *pila);

void *pila_tope(pila_t *pila);

int pila_cantidad(pila_t *pila);

void pila_destruir(pila_t *pila);

void pila_mostrar_elementos(pila_t *pila, void (*formateador)(void*));






















// Estas primitivas no son comunes en una pila

//int pila_con_cada_elemento(pila_t *pila, bool (*f)(void *, void *), void *auxiliar);


/**
 * Devuelve el primer elemento de la pila que cumple la condición
 * comparador(elemento, contexto) == 0.
 *
 * Si no existe el elemento devuelve NULL.
 */
void* pila_buscar(pila_t *pila, int (*comparador)(void*, void*), void* contexto);


#endif // PILA_H_
