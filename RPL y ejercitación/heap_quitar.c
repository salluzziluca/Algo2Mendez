    int hijo_izq = 2*n+1;
    int hijo_der = 2*n+2;
    if(hijo_izq >= tope)
        return;

    int hijo_mas_pesado = hijo_izq;

    if(hijo_der < tope){
        if(vector[hijo_der] > vector[hijo_izq])
            hijo_mas_pesado = hijo_der
    }

    if(vector[n] < vector[hijo_mas_pesado])
        sift_down(heap, hijo_mas_pesado);