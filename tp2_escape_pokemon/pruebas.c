#include "pa2mm.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "src/estructura_sala.h"

#include <string.h>
#include <stdbool.h>

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	sala_t * sala = sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd");
	pa2m_afirmar(sala == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	sala = sala_crear_desde_archivos("", "chanu/int.csv");
	pa2m_afirmar( sala == NULL,
		     "No puedo crear la sala sin objetos");
	sala_t *a = sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt");
	pa2m_afirmar( a== NULL,
		     "No puedo crear la sala sin interacciones");

	sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	pa2m_afirmar(sala->cantidad_objetos == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(sala->cantidad_interacciones == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	char **cosa = sala_obtener_nombre_objetos(NULL, &cantidad);
	pa2m_afirmar( cosa == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "pokebola",  "llave", "interruptor", "cajon",
				    "cajon-abierto", "mesa", "puerta",	     "anillo" };

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

void pruebas_estructuras()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	pa2m_afirmar(sala->jugador->escapo == false, "La variable escapó se inicializa en false");
	sala_destruir(sala);
}
void sala_obtener_obtienen_vectores_correctamente(){
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	hash_destruir_todo(sala->jugador->objetos_conocidos, free);
	hash_destruir(sala->jugador->objetos_poseidos);
	sala->jugador->objetos_conocidos = sala->objetos;
	sala->jugador->objetos_poseidos = sala->objetos;
	int cantidad = 0;
	
	char **objetos =  sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres de objetos conocidos a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres de objetos conocidos a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "pokebola",  "llave", "interruptor", "cajon",
				    "cajon-abierto", "mesa", "puerta",	     "anillo" };

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objetos conocidos son los esperados");
	free(objetos);
	free(objetos2);
	
	objetos =  sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres de objetos poseidos a la sala pasando cantidad NULL");

	objetos2 = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres objetos poseidos a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados2[] = { "habitacion",    "pokebola",  "llave", "interruptor", "cajon",
				    "cajon-abierto", "mesa", "puerta",	     "anillo" };

	comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados2[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objetos poseidos son los esperados");

	free(objetos);
	free(objetos2);	
	
	free(sala->jugador);
	sala->jugador = NULL;
	sala_destruir(sala);
}
void ejecutar_interacciones_ejecuta_interacciones_correctamente()
{
	sala_t *sala = NULL;
	void *aux = NULL;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, aux) == false, "No puedo ejecutar una interacción con sala NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == false, "No puedo corroborar si una interacción es válida con sala NULL");
	sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, aux) == false, "No puedo ejecutar una mostrar_mensaje NULL");
	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == false, "No puedo agarrar un objeto que no existe o no conozco");
	
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "mesa") == false, "El objeto mesa no se encuentra en el hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "interruptor") == false, "El objeto interruptor no se encuentra en el hash de objetos conocidos");
	
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	int interacciones = sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, aux);
	pa2m_afirmar(( interacciones == 2), "Examiné la habitacion y se ejecutaron 2 interacciones");
	
	bool contiene = hash_contiene(sala->jugador->objetos_conocidos, "mesa");
	pa2m_afirmar( contiene == true, "El objeto mesa se agrego al hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "interruptor") == true, "El objeto interruptor se agrego al hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->objetos, "mesa") == false, "El objeto mesa ya no esta en el hash objetos de la sala");
	pa2m_afirmar(hash_contiene(sala->objetos, "interruptor") == false, "El objeto interruptor ya no esta en el hash objetos de la sala");
	
	interacciones = sala_ejecutar_interaccion(sala, "examinar", "mesa", "", mostrar_mensaje, aux);
	pa2m_afirmar(( interacciones == 2), "Examiné la mesa y se ejecutaron 2 interacciones");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "cajon") == true, "El objeto cajon se agrego al hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "pokebola") == true, "El objeto pokebola se agrego al hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->objetos, "cajon") == false, "El objeto cajon ya no esta en el hash objetos de la sala");
	pa2m_afirmar(hash_contiene(sala->objetos, "pokebola") == false, "El objeto mesa ya no esta en el hash objetos de la sala");
	
	pa2m_afirmar(sala_agarrar_objeto(NULL, "pokebola") == false, "No puedo agarra un objeto en sala NULL");
	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == true, "Puedo agarrar la pokebola");
	interacciones = sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", mostrar_mensaje, aux);
	pa2m_afirmar(( interacciones == 1), "Abri la pokebola y se ejecutaron 1 interacciones");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "anillo") == true, "El objeto anillo se agrego al hash de objetos conocidos");
	
	interacciones = sala_ejecutar_interaccion(sala, "usar", "llave", "cajon", mostrar_mensaje, aux);
	pa2m_afirmar(( interacciones == 2), "Usé la llave en el cajón y se ejecutaron 1 interacciones");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "cajon-abierto") == true, "El objeto cajon-abierto se agrego al hash de objetos conocidos");
	
	sala_destruir(sala);
}

void pruebas_loop_jugable()
{
	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	int interacciones = sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, NULL);
	pa2m_afirmar(( interacciones == 2), "Examiné la habitacion y se ejecutaron 2 interacciones");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "pokebola") == true, "El objeto pokebola se agrego al hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "puerta") == true, "El objeto puerta se agrego al hash de objetos conocidos");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta", "", mostrar_mensaje, NULL) == 1, "intente abrir la puerta y estaba cerrada");
	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == true, "Puedo agarrar la pokebola");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "pokebola") == false, "El objeto pokebola se ya no está en el hash de objetos conocidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_poseidos, "pokebola") == true, "El objeto pokebola se agregó al hash de objetos poseidos");
	interacciones = sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", mostrar_mensaje, NULL);
	pa2m_afirmar( interacciones== 2, "intente abrir la pokebola y estaba cerrada");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_poseidos, "pokebola") == false, "El objeto pokebola se ya no está en el hash de objetos poseidos");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "llave") == true, "El objeto llave se agrego al hash de objetos conocidos");
	pa2m_afirmar(sala_agarrar_objeto(sala, "llave") == true, "Puedo agarrar la llave");
	interacciones = sala_ejecutar_interaccion(sala, "examinar", "llave", "", mostrar_mensaje, NULL);
	pa2m_afirmar( interacciones== 0, "intente examinar la llave y no vi nada");
	interacciones = sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", mostrar_mensaje, NULL);
	pa2m_afirmar( interacciones == 1, "intente usar la llave en la puerta y no pude hacer nada");
	pa2m_afirmar(hash_contiene(sala->jugador->objetos_conocidos, "puerta-abierta") == true, "El objeto puerta-abierta se agrego al hash de objetos conocidos");
	bool contiene = hash_contiene(sala->interacciones, "puerta-abiertasalir");
	pa2m_afirmar( contiene == true, "La interaccion abrir puerta abierta existe");
	interacciones = sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", mostrar_mensaje, NULL);
	pa2m_afirmar(interacciones== 1, "intente salir de la puerta abierta y se ejecuto una interacción");
	pa2m_afirmar(sala_escape_exitoso(sala) == true, "Puedo salir de la sala");
 	sala_destruir(sala);
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();
	
	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();
	
	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();
	
	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();
	
	pa2m_nuevo_grupo("Pruebas de Estructuras");
	pruebas_estructuras();
	
	pa2m_nuevo_grupo("Pruebas de Vectores de Nombres");
	sala_obtener_obtienen_vectores_correctamente();
	
	pa2m_nuevo_grupo("Pruebas de Ejecutar Interacciones");
	ejecutar_interacciones_ejecuta_interacciones_correctamente();

	pa2m_nuevo_grupo("Pruebas de Loop Jugable");
	pruebas_loop_jugable();
	

	return pa2m_mostrar_reporte();
}
