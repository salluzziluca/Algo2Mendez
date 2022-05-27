/*Escriba de forma recursiva (sin utilizar for, while, do, etc) una función que dados dos strings (const char*), cuenta la cantidad de veces que el segundo string aparece dentro del primero. No está permitido strlen. Puede definir funciones auxiliares. Puede hacer las suposiciones que necesite respecto del problema.

Ejemplo: contar_coincidencias("mago pago gago", "ago") => 3
*/

void contar_coincidencias(const char *cadena, const char *subcadena, int *contador, int *posicion_cadena, int *posicion_subcadena)

{
        
        if(subcadena == '\0')
                contador++;

        if(*cadena == '\0')
                return;
        if(*cadena == *subcadena)
                contar_coincidencias(cadena + 1, subcadena + 1, contador);
        else
                contar_coincidencias(cadena + 1, subcadena, contador);
        return;
}

(const char *cadena, const char *subcadena, int *contador, int *posicion_cadena, int *posicion_subcadena){

        if(subcadena[posicion_subcadena] == '\0')
                contador++;

}


int main(int argc, char const *argv[])
{
        int contador = 0;
        contar_coincidencias("mago pago gago", "ago", &contador);
        return 0;
}
