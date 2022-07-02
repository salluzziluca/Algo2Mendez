VALGREEN_FLAGS= --error-exitcode=2 -s
VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 -s
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc

all: clean valgreen-escape_pokemon, clean valgrind-escape_pokemon, clean valgreen-pruebas, clean valgrind-pruebas, clean valgreen-interactivo, clean valgrind-interactivo


escape_pokemon: escape_pokemon.c src/*
	$(CC) $(CFLAGS) src/*.c escape_pokemon.c -o escape_pokemon 2>&1

valgreen-escape_pokemon: escape_pokemon
	valgreen $(VALGREEN_FLAGS) ./escape_pokemon ejemplo/objetos.txt ejemplo/interacciones.txt 2>&1

valgrind-escape_pokemon: escape_pokemon
	valgrind $(VALGRIND_FLAGS) ./escape_pokemon 2>&1

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
	rm -f escape_pokemon *.o pruebas 2>&1 interactivo
