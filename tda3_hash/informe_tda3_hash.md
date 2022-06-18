![](https://i.imgur.com/P0aqOMI.jpg)

# **TDA N°3 —  Tabla Hash** 
---
##### [7541/9515] Algoritmos y Programación II
---
###### Primer cuatrimestre de 2023
---

|  Alumno: | Salluzzi, Luca |
| ----------- | ----------- |
| Número de padrón: | 108088 |
| Email: | lsalluzzi@fi.uba.ar |


## 1. Introducción
En este trabajo se buscaba afianzar en el alumno los conocimientos sobre tablas hash. Para esto, se le pidió implementar una tabla hash abierta con primitivas otorgadas por la cátedra.

## 2. Teoría, tipos de tablas hash

Un hash es una implementación de un TDA diccionario. Este está compuesto por unas tabla hash en la cual se asginan elementos segun su clave. Para encontrar su posicion en la tabla, se pasa la clave por una función hash la cual devuelve un numero. Al aplicar la funcion modulo entre ese numero obtenido y la capacidad de nuestra tabla obtenemos la posicion a la que asignaremos el elemento.
Si dos elementos terminan asignados a la misma posición, se genera una colision, la forma de resolverla depende del tipo de hash a utilizar.

### Hash abierto
En un hash abierto, los elementos se guardan fuera de la estructura original (vease, por ejemplo, en una lista). Las colisiones se resuelven concatenando los elementos que se encuentran en la misma posición dentro de otra estructura. De esta forma, nos ahorramos el tener que reasignarlos a una nueva posición. 
El tipo de direccionamiento de este hash es cerrado, ya que siempre que la posicion que se le asigne al elemento en su primer hasheo, se mantendra siempre y no variará. 
Su complejidad en el peor caso es O(n), ya que puede terminar degenerandose a lista si no se lo rehashea al alcanzar una cantidad especifica de elementos.
Sus complejidades son:
| crear | Destruir | Agregar un elemento| Quitar un elemento| Buscar un elemento|
| ----- | -------- | ------- | ---------------- | ----------- |
| O(1)  | O(n)     | O(1)    | O(n)            | O(n)       |
A la hora de agregar, simplemente se hashea la clave para buscar la posicion y luego se carga el par <clave;valor> a la ultima posición de la lista correspondiente. Siempre el proceso es el mismo ya que, utilizando el puntero al ultimo par, no es necesario recorrer todos los elementos de la lista.
Luego, para quitar o buscar, la justificación es la misma, ya que, en el peor caso, debemos recorrer los elemenos de la lista de la posición correspondiente hasta encontrar el par buscado o el par a eliminar (pudiendose este encontrarse al final).
Finalmente, a la hora de destruir el hash, dependemos de la cantidad de elementos en el mismo, por lo que la complejidad será O(n).

### Hash cerrado
Un hash cerrado siempre guarda sus elemento dentro de su estructura original. A la hora de resolver colisiones, se buscan nuevas posiciones libres a las que asignar los elementos colisionados. DE esta forma, siempre vamos a tener un tamaño de tabla mayor o igual al numero de claves, jamas menor. Es por esta forma de reasignar colisiones que este es un hash de direccionamiento abierto.
Para buscar nuevas posiciones libres a la hora de redireccionar las colisiones, se pueden utilizar diferentes metodos:
- Probing lineal: Se trata de buscar el proximo espacio libre inmediato
- Probing cuadratico: Busca el espacio libre inmediato, de no encontrarlo, busca la proxima posicion libre tomando en cuenta estadisticamente la posicion actual y la posicion a la que se quiere llegar.
- Hash doble: aplicar por segunda vez la misma funcion hash buscando que nos devuelva una posicion no ocupada. Esto puede llevar, en hashes ya muy cargados, a volver a colisionar y tener que repetir el proceso hasta encontrar una posicion libre. 

Sus complejidades son:
| crear | Destruir | Agregar un elemento| Quitar un elemento| Buscar un elemento|
| ----- | -------- | ------- | ---------------- | ----------- |
| O(1)  | O(1)     | O(n)    | O(n)            | O(n)       |
En un hash cerrado en el peor escenario, para agregar deberiamos recorrer todo el hash. Suponiendo que la posicion dada por la función hash sea la primera y la unica posicion libre la última.
Luego, a la hora de quitar y buscar, al igual que en el hash abierto, vamos a tener que recorrer todo el hash hasta encontrarlo (tomando siempre el peor caso).
## 3. Detalles de implementación


Explicación de como se implemento el trabajo pedido, esta sección es para que puedas explicar de forma un poco mas detallada como se implemento o como planteaste el trabajo y los detalles al respecto. Estos detalles pueden ser alguna justificación de porque implementaste lo pedido de la forma que lo hiciste, con que linea se compilo el trabajo, como ejecutarlo, algún supuesto que hayas hecho, etc. (La idea no es que se explique utilizando código pero si lo ves necesario podes hacerlo.)

Primero que nada, el Trabajo Practico se puede implementar con las lineas `gcc escape_pokemon.c  src/*.c -std=c99 -Wall -Wconversion -Wtype-limits -g -Werror -o  escape_pokemon`. Digo puede porque los flags son completamente opcionales a la hora de correrlo. 

Dicho esto, yo tome una implementacion que buscaba modularizar correctamente sin volverse uno loco intentando hacer las cosas mas chicas de lo realmente posible. Me concentre sobre todo en (intentar) no tener ninguna funcion demasiado larga o dificil de leer. Es por esto que a veces se pueden encontrar diferentes llamados o declaraciones separados por espacios aunque la [guia de estilo](https://programmerclick.com/article/47731811610/)  no lo recomendara necesariamente.

--- 
Primero y principal: se aloca memoria para la sala y se inicializa (mediante `calloc`) todo en cero. Si bien esto es un poco redundante (es la primer linea de la funcion) es importantisimo aclararlo porque de esta estabilidad inicial dependen el resto de los procesos. Sin esa memoria "core" en el heap (porque todo despues se asigna a la sala) no hay donde luego "poner" los diferentes valores. Dicho esto...

### Lectura de Archivos
Empecé por la lectura de archivos (ya dentro de `sala_crear_desde_archivos`) mediante una funcion que abre uno pasado por parametro y verifica que no sea nulo (de lo contrario retorna -1, error) para luego leerlo linea por linea y, segun se le aclare en la firma de la funcion inicializar y "llenar" un vector dinamico de objetos o de interacciones (respectivamente). 
Me parecio una buena implementacion la modularizacion de esta funcion (`cargar_a_memoria`) ya que queda visualmente demostrado en el codigo que con ambos archivos realizamos el mismo accionar. Y que si bien luego los campos a rellenar son distinto comparten (aunque sea conceptualmente) una gran parte del proceso.

#### Lectura de lineas
En esta parte del proceso ya se pueden empezar a notar las diferencias puntuales entre objetos e interacciones, es por eso que decidi programar sus funciones por separado. La diferencia de campos era significativa y me hubiese visto envuelto en una madeja de `ifs` que iba a oscurecer mas que aclarar.  
En ambas funciones se inicializan los diferentes vectores (o caracteres) en valores basicos para evitar manejo de basura, se verifica que el string recibido no sea ni nulo ni vacio(de ser asi se libera la memoria y se retorna `NULL`) y se parsea la linea. 
En caso de error en el parseo, sscanf ==no== nos devolvera un entero con la cantidad de valores leidos que le pedimos (si tenia que "dividir" el string en 3, nos deberia devolver 3 si todo salio bien). Asi que si estas condiciones no se verifican como verdaderas, retornamos `NULL`, no sin antes liberar la memoria pedida.
Si el proceso se ejecutó correctamente, se copian los valores de las variables auxiliares a los campos definitivos de los objetos o interacciones segun corresponda. Sin embargo, en ambos casos tenemos valores que no son strings. 

##### Excepciones
- En objetos tenemos un booleano, por lo que hay que hacer una comparacion extra entre strings y ahi asignarle el valor correspondiente a su campo (ya que asignarle el string "true" o "false" sería incorrecto.)
- En interacciones tenemos un enum, el cual requiere de un switch en este caso para su correcta carga al campo.
 ---
Mientras la linea leida siga siendo valida (no sea `NULL` o `FEOF`) se seguiran cargado elementos a los vectores correspondientes. Y una vez que se llegue al final del archivo, se cierra el mismo y se retorna `0` (no  hubo error).

 ##### Corroboración
 Finalmente, el programa verifica que las cantidades de ambos vectores no sea nula. Si al menos una lo es, se destruye la sala (con todos sus componentes) y se devuelve `NULL`. De lo contrario, se devuelve una sala ya inicializada

### Creación del vector de nombres de objetos e impresion por pantalla.
Una vez que esta la sala creada y (verificada), se crea un vector dinamico que contiene solamente el nombre de los objetos ya cargados originalmente en la sala. Este vector no se encuentra dentro de sala pero está ligado a `sala->objetos`. 
A la funcion que lo crea se le pasa por parametro un puntero a la sala ya llena y otro puntero a una cantidad particular que se ha de "llenar". 
Se verifican que ninguno de los valores pasados por parametro sean nulos y se procede a alocar la memoria (si por casualidad la `*sala` recibida es nula pero la `*cantidad` recibida no, se asigna una cantidad de -1, mostrando asi que no se pudo crear el vector).
Luego de haber alocado y verificado la memoria (mismo comportamiento con cantidad si hay error), se le asignan los diferentes nombres de objetos en las posiciones del vector dinámico y si la cantidad no es nula, se le asigna el valor de `sala->cantidad_objetos` ya registrada en el `struct sala`. Se devuelve el vector con los nombres cargados
Mediante el uso de este nuevo vector, se imprimen con un simple for los nombres de los objetos disponibles en la sala


### Validacion  e impresion de interacciones
Finalmente, se verifica mediante el uso de `sala_es_interaccion_valida` (la cual recibe como string los diferentes campos posibles de una interaccion y los compara con los registros de una sala ya creada) que las interacciones pedidas sean validas o invalidas y se imprime por pantalla el nombre de la interaccion seguida de su validez. En este caso, para no crear 4 variables mas y de alguna forma floodear el main, el contenido del string que se imprimirá por pantalla se verifica directamente en el printf. 
```c
printf("examinar la habitacion: %s\n", interaccion_valida(es_examinar_habitacion_valida));
```

### Liberación de memoria
Por ultimo, se destruye la sala. Agradeciendole a nuestra computadora por toda la memoria que nos prestó (como nos enseñaron en el colegio). Primero se liberan las diferentes posiciones de los vectores de elementos, luego el priopio vector y por ultimo la estructura misma de la sala.

## 4. Detalles de Funciones en particular

1. `agregar_objeto_a_vector`

    la funcion
    ```c
    agregar_objeto_a_vector(struct objeto ***objetos, int *cantidad_objetos, struct objeto *objeto_actual)
    ```
    
	Recibe por parametro un puntero a un vector de punteros, una cantidad y un objeto que se quiere agregar a ese vector. Crea un bloque de memoria auxiliar con el tamaño del vector de punteros que se le pasa + el tamaño de un  `struct objeto*` (le suma una espacio mas al vector para el nuevo elemento). Verifica que l bloque creado no sea nulo, que la memoria estpe correctamente asignada y luego le dice a `struct objeto **objetos` que apunte al mismo lugar donde está apuntando el bloque auxiliar (esto se hace para que, si la memoria no se carga correctamente en el realloc, no se pierda lo que ya habia en el vector importante y principal.).
	Por ultimo, carga el objeto actual en la posicion correspondiente segun cantidad_objetos y suma uno a cantidad. Devuelve 0, exitoso.

2. `sala_destruir()`

	Destruye la sala creada y alocada en memoria. La destruye de a partes, primero los vectores dinamicos y luego la estructura de la sala en si. No destruye el vector `nombre_objetos` porque este depende exclusivamente de  `sala->objetos`. No retorna nada porque es un ==**procedimiento==

## 5. Diagramas


En esta sección van los diagramas que realizas para poder acompañar los detalles de implementación y de funciones que escribiste mas arriba. Trata de que sean lo mas claros posibles, podes hacer mas de un diagrama para una sola función, por ejemplo podes tener un diagrama por cada paso que realiza la función en vez de tener un solo diagrama (que a lo mejor termina siendo poco claro) con toda la información metida junta.


1. Diagrama1

    ![[WhatsApp Image 2022-04-10 at 11.54.57 PM.jpeg]]

Una muestra de como se manejan el stack y el heap. Un puntero en el stack apunta a una memoria en el heap. Una variable cantidad_nombres creada en el stack tiene un puntero en el heap (creado despues) que apunta a cantidad_objetos. De esta forma se le modifica el valor a cantidad_nombres

2. ![[WhatsApp Image 2022-04-10 at 11.54.56 PM.jpeg]]


    Se tiene un archivo, de ese se lee una lina que mediante objeto_crear_desde_string se transforma luego en un struct objeto que es cargado a un vector. A ese vector se accede mediante un puntero en sala