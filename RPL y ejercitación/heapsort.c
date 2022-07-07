#include <stdbool.h>
#include <stdio.h>
int padre_de(int n)
{
    return (n-1)/2;
}
void swap(int *vector, int n, int padre)
{
    int aux = vector[n];
    vector[n] = vector[padre];
    vector[padre] = aux;
}
void sift_down(int* vector, int tope, int n){
    int hijo_izq = 2*n+1;
    int hijo_der = 2*n+2;
    if(hijo_izq >= tope)
        return;

    int hijo_mas_pesado = hijo_izq;

    if(hijo_der < tope){
        if(vector[hijo_der] > vector[hijo_izq])
            hijo_mas_pesado = hijo_der;
    }

    if(vector[n] < vector[hijo_mas_pesado]){
        swap(vector, n, hijo_mas_pesado);
        sift_down(vector, tope,  hijo_mas_pesado);
    }
}
void sift_up(int* vector, int n){
    if(n == 0)
        return;
    int padre = padre_de(n);
    if(vector[n] > vector[padre]){
        swap(vector, n, padre);
        sift_up(vector, padre);
    }
}

void heapify(int*vector,int tope, bool ascendente)
{
        int actual=tope-1;
        while(actual>=0){
            if(ascendente)
                sift_down(vector, tope, actual);
            else
                sift_up(vector,tope);
            actual --;
        }
}
int extraer_raiz(int *vector, int tope){
        if(tope == 0)
                return 0;
        int valor = vector[0];
        swap(vector,0,tope-1);
        if(tope != 0)
            sift_down(vector, tope, 0);
    return valor;

}
void heap_sort(int* vector, int tope, bool ascendente){
    heapify(vector, tope, ascendente);
    // print the array 
        for(int j=0; j<tope; j++){
            printf("%d ", vector[j]);
        }
        printf("\n");
    while (tope > 0){
        swap(vector, tope, 0);
        tope--;
        sift_down(vector, tope,  0);
    }
    for (int i = 0; i < tope; i++) {
      printf("%d ", vector[i]);
    }
        printf("\n");
}
int main(int argc, char const *argv[])
{
        int vector[] = {6,1,5,4,10,2};
        int tope = sizeof(vector)/sizeof(int);
        heap_sort(vector, tope, true);
        heap_sort(vector, tope, false);
        return 0;
}
