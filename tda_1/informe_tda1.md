    
![](https://i.imgur.com/P0aqOMI.jpg)

# **TDA Lista** 


## [7541/9515] Algoritmos y Programación II


### Primer cuatrimestre de 2022

|  Alumno: | SALLUZZI, Luca |
| ----------- | ----------- |
| Número de padrón: | 108088 |
| Email: | lsalluzzi@fi.uba.ar |


#### 1. Introducción

En este trabajo se buscaba afianzar el manejo y el desarrollo de tres Tipos de Datos Abstractos: lista, pila y cola. Se debía tener una clara vision del funcionamiento de cada uno, sus restricciones y posibles implementaciones, asi como de sus primitivas y el grado de complejidad algorítmica de las mismas. 

#### 2. Teoría
1. TDA Pila con nodos enlazados
	1. Una pila con nodos (simplemente) enlazados, tenemos una pila que apunta al nodo final, al nodo inicial, una cantidad y un tope. A medida que vamos agregando elementos, enlazamos el nodo anterior con el nuevo agregado, vamos incrementando la cantidad y modificando, debidamente, cual es el nodo inicio, ya que cada vez que agregamos uno el primer nodo (el que deberá desapilarse primero) se modifica. Si en algun momento la cantidad se vuelve igual al tope, en vez de quedarnos con una pila "llena" y no poder agregar más, aumentamos la memoria asignada (mediante un realloc) y continuamos agregando (esto tomando como supuesto que no hacemos un realloc en cada adición).
		Luego, para desapilar elementos, buscamos el elemento que esté en primera posición y se lo damos al usuario, reorganizando la pila del tal manera que el nodo que antes estaba segundo pase a ser el nodo inicial.
		Otras primitivas son: crear, la cual crea la lista, inicializando nodo_inicio y nodo_fin como nulos, cantidad y tope como 0. Cantidad, que devuelve la cantidad. Y está vacia, que se fija si la cantidad es mayor a 0. 
	1. La complejidad algorítmica de sus primitivas son O(1) (menos destruir, que depende de la cantidad de elementos). Crea varia segun la cantidad, y push y pop, tomando "la parte superior" de la pila como el nodo_inicio, son siempre O(1) porque no hay que recorrer el TDA entero.
| crear | Destruir | Encolar | Desencolar |
| ----- | -------- | ------- | ---------- |
| O(1)  | O(n)     | O(1)    | O(1)       |

2. TDA Cola Circular con vectores estáticos
	1. En una cola circular, la cantidad siempre va a estar siguiendo al tope. Si el tope (cantidad maxima de el vector) es 9, y hay 4 elementos cargados (cantidad = 4), siempre va a haber 5 espacios libres, no importa que estos sean "al inicio" de la cola, porque el inicio y el final se combinan, por la circularidad. Al tener un vector estático, si llegamos al punto en el que cantidad == tope, no hay nada mas que hacer, no podes encolar mas elementos a no ser que desencolemos otros antes.
		En una cola, por otro lado, se encola por atras y se desencola siempre por adelante, por lo que al agregar un elemento quitarlo tendremos siempre O(1), ya que podemos acceder a las posiciones adyacentes al elemento actual sin problema al estar trabajando con un vector. Otras primitivas son: tope, cantidad, destruir o crear.
	1. En cuanto a complejidad algorítimica tenemos que
| crear | Destruir | Encolar | Desencolar |
| ----- | -------- | ------- | ---------- |
| O(1)  | O(n)     | O(1)    | O(1)       |

3. TDA Lista con nodos enlazados
	1. Una lista con nodos enlazados es similar a la pila con nodos enlazados, pero con mas primitivas. Tal y como vimos arriba, Agregar y quitar por nodo_inicio es siempre O(1), pero el problema llega cuando queremos relizar otras adiciones o disminuciones en posiciones que no son el principio de la lista. Ahi es cuando debemos iterar por el resto de la lista hasta llegar al nodo anterior al que queremos quitar o agregar. De esta forma, podemos realizar correctamente las asignaciones tanto si borramos como si agregamos. 
        Al borrar en posición, por ejemplo, debemos conocer el nodo anterior, el cual apunta al que queremos borrar. Liberariamos el nodo a borrar para luego conectar el nodo anterior al nodo siguiente. Al agregar en posicion, debemos tambien conocer ese nodo anterior, lo hariamos apuntar al nodo que estamos agregando y este nodo que estamos agregando apuntaria al nodo siguiente del anterior. 
	2. Complejidad Algorítmica
| crear | Destruir | Agregar | Quitar |Agregar en posicion | Quitar en posicion |
| ----- | -------- | ------- | ------- | ---------------- | ---------------- |
| O(1)  | O(n)     | O(1)    | O(1)    | O(n)             | O(n)            |
#### 3. Detalles de implementación


En mi implementación prioricé la legibilidad a el ahorro de lineas, hay funciones (sobre todo las mas simples), que se podrian hacer en una sola linea con un return, pero preferi crear variables que permitieran entender mejor el paso a paso del código.
Empecé haciendo las diferentes primitivas de la lista. Implementando desde lo mas simple a lo mas complejo. Primero creando y destruyendo la lista (con sus respectivas pruebas), para pasar luego a la adición y la sutracción de elementos (tomando en cuenta casos especiales como cantidad igual a 0). De ahí pasé a la adición y la eliminación de elementos en posiciones, iterando adecuadamente y tomando tambien en cuenta casos particulares como cantidad mayor a cero, posicion igual a cero o posición mayor a cantidad. Para esto modularicé el llenado de nodos, ya que era algo repetitivo y que, si bien modularizarlo no hace la gran diferencia, en mi opinión mejora la legibilidad del codigo.



1. Detalles de alguna función

    Algún detalle importante sobre alguna función. La idea no es que expliques todas las funciones, es para que expliques mas en detalle las funciones mas importantes del trabajo (como por ejemplo, como funciona el insertar en una posición especifica en una lista) y como funcionan, porque están implementadas de cierta forma, etc.

2. Detalle de otra función

    Algún detalle de otra función.

#### 4. Diagramas


En esta sección van los diagramas que realizas para poder acompañar los detalles de implementación y de funciones que escribiste mas arriba. Trata de que sean lo mas claros posibles, podes hacer mas de un diagrama para una sola función, por ejemplo podes tener un diagrama por cada paso que realiza la función en vez de tener un solo diagrama (que a lo mejor termina siendo poco claro) con toda la información metida junta.


1. Diagrama1

    ![Diagrama1](https://i.imgur.com/KvYn8UD.png)

    Explicacion del diagrama1, en caso de ser necesaria.

2. Diagrama2

    ![Diagrama2](https://i.imgur.com/nhqXNr6.png)

    Explicacion del diagrama2, en caso de ser necesaria.