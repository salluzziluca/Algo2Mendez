#include "stdio.h"
void invertidor_de_poema(char* poema){
    if(*poema == 0)
        return;
        
        poema = invertidor_de_poema(poema+1);
        printf("%c", *poema);

}
int main(int argc, char const *argv[])
{
        char* poema = "odnum aloH";
        invertidor_de_poema(poema);
        // imprimir poema
        printf("%s\n", poema);
        return 0;
}
