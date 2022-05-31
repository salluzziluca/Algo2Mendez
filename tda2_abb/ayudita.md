1) Llamo a abb_quitar con elemento 15
2) Como no es nullo nada, y el tamaño es >1, llama a nodo_quitar con raiz como nodo actual y 15 como elemento
3) la comparacion da 0, como tengo nodo->izquierda entro al if
4) Entro a obtener_predecesor_inorden, le paso nodo izq(9) como nodo y un puntero uxiliar para que cargue el reemplzao
5) Llamo recursivamente al obtener_predecesor con nodo 14. 
6) Como no tiene derecha, lo guardo como reemplazo y retorno el nodo izquierda (13).
7) salgo recursivamente. El nodo derecha del 9 ahora es el 13. 
8) salgo recursivamente, el nodo izquierda del nodo a eliminar es el 9, todo sigue piola
9) cambio el elemento borrado por el nuevo elemento. Se va el 15 y entra el 14. 
10) libero el nodo auxiliar (el nodo del 14 que tenia al 13 como hijo izquierdo). Lo cual esta bien porque el nodo 9 tiene al trece ya enlazado como hijo derecho. 
11) devuelvo el nodo actual ya modificado, aunque en este caso no pase nada. 

1) Llamo a abb_quitar con elemento 15
2) Como no es nullo nada, y el tamaño es >1, llama a nodo_quitar con raiz como nodo actual y 15 como elemento
3) la comparacion da 0, como tengo nodo->izquierda entro al if
4) Entro a obtener_predecesor_inorden, le paso nodo izq(6) como nodo y un puntero uxiliar para que cargue el reemplzao
5) Llamo recursivamente al obtener_predecesor con nodo 9. 
6) Como tiene derecha, Llamo recursivamente al obtener_predecesor con nodo 12. 
7) Como no tiene derecha, lo guardo como reemplazo y retorno el nodo izquierda (NULL).
8) salgo recursivamente, el nodo izquierda del nodo 9, es ahora null
9) salgo recursivamente, el nodo derecho de 6 sigue siendo 9, pero ahora este 9 tiene hijo derecha null.
10) El nodo raiz tiene como hijo al nodo 6, la modificacion sigue siendo solo en el hijo del 9.
11) Llego al nodo raiz, reemplazo el 14 por el 12, eliminmo el auxiliar y retorno en nodo-
12) nodo izquierda va a seguir siendo 6 con todas las modificaciones que arriba digo. 