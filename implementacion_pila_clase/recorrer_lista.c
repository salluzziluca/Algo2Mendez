int como_recorrer_una_lista(int argc, char *argv[]) {

	// i, O(n²)
	for (int i = 0;                //inicialización
	     i < lista_tamanio(lista); //condición de corte
	     i++){                     //próxima iteración

		char *elemento = lista_elemento_en_posicion(lista, i);
		printf("%c ", *elemento);
	}

	// Nodo, O(n)
	for (nodo_t *actual = lista->inicio; //inicialización
	     actual!=NULL;                   //condición de corte
	     actual = actual->siguiente){    //próxima iteración

		char *elemento = actual->elemento;
		printf("%c ", *elemento);
	}

	// Iterador externo, O(n)
	lista_iterador_t *it = NULL;
	for (it = lista_iterador_crear(lista);   //inicialización
	     lista_iterador_tiene_siguiente(it); //condición de corte
	     lista_iterador_avanzar(it)){        //próxima iteración

		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	}


	return 0;
}
