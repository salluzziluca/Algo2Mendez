VALGREEN_FLAGS= --error-exitcode=2 -s
VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 -s
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -n
CC = gcc

all: clean valgreen-ejemplo, clean valgrind-ejemplo, clean valgreen-pruebas, clean valgrind-pruebas, clean valgreen-interactivo, clean valgrind-interactivo


ejemplo: ejemplo.c src/*
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo 2>&1

valgreen-ejemplo: ejemplo
	valgreen $(VALGREEN_FLAGS) ./ejemplo 2>&1

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo 2>&1

valgreen-pruebas: pruebas
	valgreen $(VALGREEN_FLAGS) ./pruebas 2>&1
	
valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

valgrind-interactivo: interactivo
	valgrind $(VALGREEN_FLAGS) ./interactivo

valgreen-interactivo: interactivo
	valgreen $(VALGRIND_FLAGS) ./interactivo

interactivo: *.c *.h
	$(CC) $(CFLAGS) src/abb.c src/nodo.c mostrar_abb.c interactivo.c -o interactivo 2>&1

clean:
	rm -f ejemplo *.o pruebas 2>&1 interactivo
