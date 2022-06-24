#ifndef ESTRUCTURA_SALA_H
#define ESTRUCTURA_SALA_H

struct sala {
	struct objeto **objetos;
	int cantidad_objetos;
	struct interaccion **interacciones;
	int cantidad_interacciones;
};
#endif // ESTRUCTURA_SALA_H