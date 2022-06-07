#include "src/hash.h"
#include "pa2m.h"
#define MAX_CLAVE 25
int funcion_hash(char clave[MAX_CLAVE]) {
	int i;
	int suma = 0;
	for (i = 0; i < MAX_CLAVE; i++) {
		suma = suma + clave[i];
	}
	return suma;
}
void hash_crear_crea_e_inicializa_correctamente(){
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea el hash correctamente");
	pa2m_afirmar(hash->capacidad == 3, "Se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash->tamanio == 0, "Se crea el hash con tamanio 0");
	pa2m_afirmar(hash->pares != NULL, "Se crea el hash con pares disponibles");
	hash_destruir(hash);

	hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad menor a 3");
	pa2m_afirmar(hash->capacidad == 3, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash->tamanio == 0, "se crea el hash con tamanio 0");
	pa2m_afirmar(hash->pares != NULL, "se crea el hash con pares disponibles");
	hash_destruir(hash);

	hash = hash_crear(23);
	pa2m_afirmar(hash != NULL, "Se devuelve un hash valido de cuando se pide crear un hash con capacidad mayor a 3");
	pa2m_afirmar(hash->capacidad == 23, "se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash->tamanio == 0, "se crea el hash con tamanio 0");
	pa2m_afirmar(hash->pares != NULL, "se crea el hash con pares disponibles");
	hash_destruir(hash);
	

}

 
void funcion_hash_funciona_correctamente(){
	pa2m_afirmar(funcion_hash("hola") == 5, "funcion_hash funciona correctamente");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación");
	hash_crear_crea_e_inicializa_correctamente();
	pa2m_nuevo_grupo("Prueba de funcion hash");
	funcion_hash_funciona_correctamente();

	return pa2m_mostrar_reporte();
}
