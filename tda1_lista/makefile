VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc

all: 64

64:
	$(CC) $(CFLAGS) src/*.c pruebas_chanutron-x86_64.o -o pruebas_chanutron
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron 2>&1

32:
	$(CC) $(CFLAGS) src/*.c pruebas_chanutron-x86.o -o pruebas_chanutron
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron 2>&1

ejemplo: ejemplo.c src/*
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo 2>&1

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

clean:
	rm -f ejemplo *.o pruebas 2>&1
