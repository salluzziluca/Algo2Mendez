#include "src/hash.h"
#include "pa2m.h"
#include <string.h>
void hash_insertar_inserta_correctamente(){
	hash_t *hash = hash_crear(3);
	int numero = 1;
	hash_insertar(hash, "hola", &numero, NULL);
	pa2m_afirmar(hash->pares[0].par_inicio->elemento == &numero, "hash_insertar_inserta_correctamente");
	hash_destruir(hash);
	

}
int main()
{
	pa2m_nuevo_grupo("Pruebas de Insercion");
	hash_insertar_inserta_correctamente();
	

	return pa2m_mostrar_reporte();
}
