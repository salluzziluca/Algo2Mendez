#include "src/hash.h"
#include "pa2m.h"
#include <string.h>
void hash_crear_crea_e_inicializa_correctamente(){
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea el hash correctamente");
	pa2m_afirmar(hash->capacidad == 3, "Se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "Se crea el hash con cantidad 0");
	pa2m_afirmar(hash->pares != NULL, "Se crea el hash con pares disponibles");
	hash_destruir(hash);

	hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad menor a 3");
	pa2m_afirmar(hash->capacidad == 3, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "se crea el hash con cantidad 0");
	pa2m_afirmar(hash->pares != NULL, "se crea el hash con pares disponibles");
	hash_destruir(hash);

	hash = hash_crear(23);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad mayor a 3");
	pa2m_afirmar(hash->capacidad == 23, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash_cantidad(hash)== 0, "se crea el hash con cantidad 0");
	pa2m_afirmar(hash->pares != NULL, "se crea el hash con pares disponibles");
	hash_destruir(hash);
	

}

void hash_insertar_inserta_correctamente(){
	hash_t *hash = hash_crear(3);
	int numero = 1;
	pa2m_afirmar(hash_insertar(hash, "hola",&numero , NULL) != NULL, "Se inserta correctamente");
	pa2m_afirmar(strcmp(hash->pares[0].clave, "hola") == 0, "Se inserta la clave correctamente");
	pa2m_afirmar(*(int *)hash->pares[0].elemento == 1, "Se inserta el elemento correctamente");
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación");
	hash_crear_crea_e_inicializa_correctamente();
	pa2m_nuevo_grupo("Pruebas de Insercion");
	hash_insertar_inserta_correctamente();

	return pa2m_mostrar_reporte();
}
