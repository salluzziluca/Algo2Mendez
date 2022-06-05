#include "src/hash.h"
#include "pa2m.h"

void hash_crear_crea_e_inicializa_correctamente(){
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea el hash correctamente");
	pa2m_afirmar(hash->capacidad == 3, "Se crea el hash con la capacidad correcta");
	pa2m_afirmar(hash->tamanio == 0, "Se crea el hash con tamanio 0");
	pa2m_afirmar(hash->pares != NULL, "Se crea el hash con pares disponibles");



	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Creación");
	hash_crear_crea_e_inicializa_correctamente();

	return pa2m_mostrar_reporte();
}
