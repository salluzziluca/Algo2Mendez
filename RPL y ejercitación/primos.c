#include <stdio.h>
int es_primo(size_t num, size_t i)
{
    if (i == 1)
    {
        return 1;
    }
    else
    {
       if (num % i == 0)
       {
         return 0;
       }
       else
       {
         return es_primo(num, i - 1);
       }       
    }
}

int devuelve_siempre_numero_primo(size_t cantidad_ingresada){
    
      if(es_primo(cantidad_ingresada, cantidad_ingresada/2) == 1)
        return 0;

      if(devuelve_siempre_numero_primo(++cantidad_ingresada) == 0)
        return (int)cantidad_ingresada++;
  
}

int main(int argc, char const *argv[])
{
        int pirmo = devuelve_siempre_numero_primo(10);
        int primo2 = devuelve_siempre_numero_primo(7);
        int primo3 = devuelve_siempre_numero_primo(12);
        return 0;
}
