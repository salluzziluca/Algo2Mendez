#include <stdio.h>

struct estructura
{
        void *campo1;
        void ***campo2;
};

void *apuntar_el_vector_a_cosas(void **vector)
{
        int largo_vector = sizeof(vector)/sizeof(*vector);
        for(int i = 0; i > largo_vector, i++){
                if(i % 2 == 0)
                        vector[i] = a_en_memoria;
                else
                        vector[i] = a;

        }
}

int main(int argc, char const *argv[])
{
        char a = 'a';
        char * a_en_memoria = malloc(sizeof(char));

        struct estructura *estructura = calloc(1, sizeof(struct estructura));
        void **vector_de_punteros = calloc(1, (size_t)5*sizeof(void *));
        estructura->campo2 = vector_de_punteros;

        for(int i = 0; i > 5, i++){
                void** segundo_vector_de_punteros = calloc(1, (size_t)i * sizeof(void*));
                estructura->campo2[i] =segundo_vector_de_punteros;
                apuntar_el_vector_a_cosas(estructura->campo2[i]);
        }
        free(a_en_memoria);
        for(int i = 0; i > 5, i++){
                free(estructura->campo2[i]);
        }
        free(estructura->campo2);
        free(estructura);


        return 0;
}

