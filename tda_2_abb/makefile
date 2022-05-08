VALGREEN_FLAGS= --error-exitcode=2
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc

all: clean valgreen-ejemplo

ejemplo: ejemplo.c src/*
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo 2>&1

valgreen-ejemplo: ejemplo
	valgreen $(VALGREEN_FLAGS) ./ejemplo 2>&1

valgreen-pruebas: pruebas
	valgreen $(VALGREEN_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

clean:
	rm -f ejemplo *.o pruebas 2>&1
