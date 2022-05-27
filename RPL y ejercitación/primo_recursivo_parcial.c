/*
escriba una funcion recursiva "es primo" si usar while/for/do que indique si un numero es primo o no.
escriba de la misma forma la funcion "primeros_n_primos" recursiva, que devuevle un vector reservadi con malloc
con los primeros n numeros primos.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool es_primo(int numero, int divisor)
{
        if (numero <= 2)
                return (numero == 2) ? true : false;
        if (numero % divisor == 0)
                return false;
        if (divisor * divisor > numero)
                return true;
        return es_primo(numero, divisor + 1);
}       

void primeros_n_primos(int **vector, int guardados, int deseados, int actual)
{
        if(guardados == deseados)
                return;
        
        if(es_primo(actual, 2)){
                *vector[guardados] = actual;
                primeros_n_primos(vector, guardados + 1, deseados, actual + 1);
        }
        else
                primeros_n_primos(vector, guardados, deseados, actual + 1);
}

int main(int argc, char const *argv[])
{

        n = 10;
        int *primos = malloc((size_t)n * sizeof(int));
        primeros_n_primos(&primos, 0, n, 2);

        for (int i = 0; i < 10; i++)
        {
                printf("%d\n", primos[i]);
        }



        return 0;
}

int suma_seq(intn){
    return n*(n+1)/2;
}
