#include "src/hash.h"
#include "pa2m.h"
#include <string.h>

bool no_hace_nada(const char *clave, void *elemento, void *extra)
{
	clave = clave;
	elemento = elemento;
	extra = extra;
	return true;
}
void hash_crear_crea_e_inicializa_correctamente(){
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea el hash correctamente");
	pa2m_afirmar(hash->capacidad == 3, "Se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "Se crea el hash con cantidad 0");
	pa2m_afirmar(hash->posiciones != NULL, "Se crea el hash con posiciones disponibles");
	hash_destruir(hash);

	hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad menor a 3");
	pa2m_afirmar(hash->capacidad == 3, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "se crea el hash con cantidad 0");
	pa2m_afirmar(hash->posiciones != NULL, "se crea el hash con posiciones disponibles");
	hash_destruir(hash);

	hash = hash_crear(23);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad mayor a 3");
	pa2m_afirmar(hash->capacidad == 23, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "se crea el hash con cantidad 0");
	pa2m_afirmar(hash->posiciones != NULL, "se crea el hash con posiciones disponibles");
	hash_destruir(hash);
	

}

void hash_insertar_inserta_correctamente(){
	hash_t *hash = NULL; 
	void *anterior = NULL;
	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;
	pa2m_afirmar(hash_insertar(hash, "hola", &uno, anterior) == NULL, "No se puede insertar un par en un hash nulo");
	hash = hash_crear(32);

	pa2m_afirmar(hash_insertar(hash, "hola",&uno , &anterior) != NULL, "Se inserta correctamente");
	pa2m_afirmar(strcmp(hash->posiciones[9].par_inicio->clave , "hola") == 0, "Se inserta la clave correctamente");
	pa2m_afirmar(*(int*)hash_obtener(hash, "hola") == 1, "Se inserta el par correctamente");pa2m_afirmar(hash_cantidad(hash)== 1, "Se aumenta la cantidad correctamente");	

	pa2m_afirmar(hash_insertar(hash, "hola",&dos , &anterior) != NULL, "Se inserta correctamente");
	pa2m_afirmar(*(int*)hash_obtener(hash, "hola") == 2, "Se sobreescribio el valor correctamente");
	pa2m_afirmar(*(int*) anterior == 1, "El elemento sobrescrito es almacenado correctamente");
	pa2m_afirmar(hash_cantidad(hash)== 1, "La cantidad no aumenta porque el elemento fue sobrescrito");
	hash_quitar(hash, "hola");
	hash_insertar(hash, "hola",&dos , &anterior);
	pa2m_afirmar(*(int*)hash_obtener(hash, "hola") == 2, "Se puede agregar, eliminar y volver a agregar el mismo elemento con la misma clave");
	pa2m_afirmar(hash_insertar(hash, "papa",&dos , &anterior) != NULL, "Se puede insertar dos veces el mismo elemento con diferente clave");
	pa2m_afirmar((*(int *)hash_obtener(hash, "papa") == 2 )&& (*(int *)hash_obtener(hash, "hola") == 2), "Ambas claves tienen el mismo elemento");
	pa2m_afirmar(hash_insertar(hash, NULL,&dos , &anterior) == NULL, "No se puede insertar par con clave nula");
	pa2m_afirmar(hash_insertar(hash, "tres", &tres, &anterior) != NULL, "Se puede insertar un tercer par");
	pa2m_afirmar(hash_obtener(hash, "tres") == &tres, "Se obtiene el valor correctamente");
	pa2m_afirmar(hash_contiene(hash, "tres"), "contiene esa clave");
	pa2m_afirmar(hash_cantidad(hash)== 3, "Se aumenta la cantidad correctamente");
	pa2m_afirmar(hash_insertar(hash, "cuatro", &cuatro, &anterior) != NULL, "Se puede insertar un cuarto par");
	pa2m_afirmar(hash_obtener(hash, "cuatro") == &cuatro, "Se obtiene el valor correctamente");
	pa2m_afirmar(hash_contiene(hash, "cuatro"), "contiene esa clave");
	pa2m_afirmar(hash_cantidad(hash)== 4, "Se aumenta la cantidad correctamente");
	pa2m_afirmar(hash_insertar(hash, "cinco", &cinco, &anterior) != NULL, "Se puede insertar un quinto par");
	pa2m_afirmar(hash_obtener(hash, "cinco") == &cinco, "Se obtiene el valor correctamente");
	pa2m_afirmar(hash_contiene(hash, "cinco"), "contiene esa clave");
	pa2m_afirmar(hash_cantidad(hash)== 5, "Se aumenta la cantidad correctamente");
	pa2m_afirmar(hash_insertar(hash, "seis", &seis, &anterior) != NULL, "Se puede insertar un sexto par");
	pa2m_afirmar(hash_obtener(hash, "seis") == &seis, "Se obtiene el valor correctamente");
	pa2m_afirmar(hash_contiene(hash, "seis"), "contiene esa clave");
	pa2m_afirmar(hash_cantidad(hash)== 6, "Se aumenta la cantidad correctamente");
	pa2m_afirmar(hash_insertar(hash, "siete", &siete, &anterior) != NULL, "Se puede insertar un septimo par");
	pa2m_afirmar(hash_obtener(hash, "siete") == &siete, "Se obtiene el valor correctamente");
	pa2m_afirmar(hash_contiene(hash, "siete"), "contiene esa clave");
	pa2m_afirmar(hash_cantidad(hash)== 7, "Se aumenta la cantidad correctamente");

	hash_destruir(hash);
}
void hash_quitar_quita_correctamente(){
	hash_t *hash = NULL;
	int uno = 1;
	pa2m_afirmar(hash_quitar(hash, "hola") == NULL, "No se puede quitar un par en un hash nulo");
	hash = hash_crear(3);
	hash_insertar(hash, "hola", &uno, NULL);
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL, "No se puede quitar un par pasando una clave nula");
	pa2m_afirmar(hash_contiene(hash, "hola") == true, "El elemento existe");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad es 1");
	pa2m_afirmar(*(int*)hash_quitar(hash, "hola") == 1, "Se puede quitar el elemento");
	pa2m_afirmar(hash_contiene(hash, "hola") == false,"El elemento no se encuentra en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La cantidad es 0");

	hash_destruir(hash);
}

void hash_con_cada_clave_itera_correctamente(){
	hash_t *hash = NULL;
	pa2m_afirmar(hash_con_cada_clave(hash, no_hace_nada, NULL) == 0, "No se puede iterar un hash nulo");
	hash = hash_crear(3);
	pa2m_afirmar(hash_con_cada_clave(hash, no_hace_nada, NULL) == 0, "Pedir iterar en un hash vacio devuelve 0");
	int uno = 1, dos = 2;
	hash_insertar(hash, "hola", &uno, NULL);
	hash_insertar(hash, "chau", &dos, NULL);
	void *aux = NULL;
	pa2m_afirmar(hash_con_cada_clave(hash, no_hace_nada, aux) == 2, "El iterador funciona correctamente");
	hash_destruir(hash);
}

void hash_rehash_rehashea_correctamente(){
	hash_t *hash = hash_crear(3);
	int uno = 1, dos = 2, tres = 3 , cuatro = 4, cinco = 5, seis = 6, siete = 7;
	pa2m_afirmar(hash->capacidad == 3, "La capacidad del hash es 3");
	pa2m_afirmar(hash_insertar(hash, "hola", &uno, NULL) != NULL, "se puede insertar un primer par");
	pa2m_afirmar(hash_insertar(hash, "chau", &dos, NULL) != NULL, "se puede insertar un segundo par");
	pa2m_afirmar(hash->capacidad == 3, "La capacidad del hash es 3");
	pa2m_afirmar(hash_insertar(hash, "adios", &tres, NULL) != NULL, "se puede insertar un tercer par");
	pa2m_afirmar(hash->capacidad == 6, "La capacidad del hash es 6");
	pa2m_afirmar(hash_insertar(hash, "cuatro", &cuatro, NULL) != NULL, "se puede insertar un cuarto par");
	pa2m_afirmar(hash_insertar(hash, "cinco", &cinco, NULL) != NULL, "se puede insertar un quinto par");
	pa2m_afirmar(hash_insertar(hash, "seis", &seis, NULL) != NULL, "se puede insertar un sexto par");
	pa2m_afirmar(hash->capacidad == 12, "La capacidad del hash es 12");
	pa2m_afirmar(hash_insertar(hash, "siete", &siete, NULL) != NULL, "se puede insertar un septimo par");
	pa2m_afirmar(hash_cantidad(hash) == 7, "se insertaron 7 elementos");

	pa2m_afirmar(hash_cantidad(hash) == 7, "La cantidad es 7");

	pa2m_afirmar(hash_contiene(hash, "hola") == true, "El elemento1 existe");
	pa2m_afirmar(hash_contiene(hash, "chau") == true, "El elemento2 existe");
	pa2m_afirmar(hash_contiene(hash, "adios") == true, "El elemento3 existe");
	pa2m_afirmar(hash_contiene(hash, "cuatro") == true, "El elemento4 existe");
	pa2m_afirmar(hash_contiene(hash, "cinco") == true, "El elemento5 existe");
	pa2m_afirmar(hash_contiene(hash, "seis") == true, "El elemento6 existe");
	pa2m_afirmar(hash_contiene(hash, "siete") == true, "El elemento7 existe");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación");
	hash_crear_crea_e_inicializa_correctamente();
	pa2m_nuevo_grupo("Pruebas de Insercion");
	hash_insertar_inserta_correctamente();
	pa2m_nuevo_grupo("Pruebas de Quitado");
	hash_quitar_quita_correctamente();
	pa2m_nuevo_grupo("Pruebas de Iterador");
	hash_con_cada_clave_itera_correctamente();
	pa2m_nuevo_grupo("Pruebas de Rehash");
	hash_rehash_rehashea_correctamente();
	return pa2m_mostrar_reporte();
}
