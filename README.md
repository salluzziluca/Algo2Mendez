# Algo2Mendez
Inside this repo there are (from now) two projects.
### Escape Pokemón (Pokemon Scape)
An small project that wanted to reinforce memory managment and file parsing concepts. it can be compiled using the following command: `gcc escape_pokemon.c  src/*.c -std=c99 -Wall -Wconversion -Wtype-limits -g -Werror -o  escape_pokemon` and runed using `./escape_pokemon ejemplo/objetos.txt ejemplo/interacciones.txt`. 
### TDA1 List, queue and stack
A project whose objective was to help the student implement their firsts ADTs (abstract data types): list, queues and stacks. Furthermore, it had a testing framework that the student had to use, making tests and using them to, well, *test* their own code.
The ADTs tests can be runed using the command `gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 src/*.c pruebas.c -o pruebas 2>&1` followed by `./pruebas 2>&1`. 
Feel free to ask whatever you want

### TDA2 Binary Search Tree
In this proyect, the student had to develop and implement a BST. The goal of this assignment was to make the student used to this data structre as well as making they familiarize with recursivity. An interactive version of the tree can be compiled with  `gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 src/abb.c src/nodo.c mostrar_abb.c interactivo.c -o interactivo 2>&1` and runned using `valgrind--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 -s ./interactivo` or just by using the makefile `make valgrind-interactivo`.
(you can also compile and run whitout the flags as the program does not has any mayor bug or mem leak)
