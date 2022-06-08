#include "src/hash.h"
#include "pa2m.h"
#include <string.h>
void hash_insertar_inserta_correctamente(){
	hash_t *hash = hash_crear(3);
	int numero = 1;
	hash_insertar(hash, "hola", &numero, NULL);
	pa2m_afirmar(hash->pares[0].par_inicio->elemento == &numero, "hash_insertar_inserta_correctamente");
	pa2m_afirmar(hash_obtener(hash, "hola") == &numero, "el elemento se encuentra en el hash");
	pa2m_afirmar(hash_contiene(hash, "hola"), "el elemento se encuentra en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 1, "el hash tiene un elemento");
	pa2m_afirmar(*(int*)hash_quitar(hash, "hola") == numero, "el elemento se encuentra en el hash");
	bool esta = hash_contiene(hash, "hola");
	pa2m_afirmar(esta==false, "el elemento no se encuentra en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, "el hash no tiene elementos");
	hash_destruir(hash);
	

}
int main()
{
	pa2m_nuevo_grupo("Pruebas de Insercion");
	hash_insertar_inserta_correctamente();
	

	return pa2m_mostrar_reporte();
}
