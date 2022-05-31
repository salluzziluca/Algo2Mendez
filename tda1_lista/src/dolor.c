#include "lista.h"
#include "lista.c"

int main(int argc, char const *argv[])
{       
        lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', w = 'w';

	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar_en_posicion(lista, &d, 100);
	lista_insertar_en_posicion(lista, &b, 1);
	lista_insertar_en_posicion(lista, &w, 3);
        bool encontrado = false;
        lista_iterador_t *it_lista = lista_iterador_crear(lista);
        bool existe_elemento_siguiente = lista_iterador_tiene_siguiente(it_lista);

    while(encontrado == false && lista_iterador_tiene_siguiente(it_lista)){
       if(lista_iterador_elemento_actual(it_lista) == NULL) 
           printf("El elemento actual es NULL\n");
        if(*(char *)lista_iterador_elemento_actual(it_lista) == 'l')
            encontrado = true;

        else if(existe_elemento_siguiente){
                lista_iterador_avanzar(it_lista);
                existe_elemento_siguiente == lista_iterador_tiene_siguiente(it_lista);
        }
    }
        return 0;
}
