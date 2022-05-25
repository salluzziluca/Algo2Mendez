
#define PLANTA 'p'
#define FUEGO 'f'
#define AGUA 'a'
#define ELECTRICO 'e'

struct pokemon
{
        char nombre[MAX_NOMBRE] = '0';
        char tipo = ''
};

struct entrenado
{
        pokemones **
};


/*
* Creará un entrenador pokemon.
* Reservará toda la memoria necesaria e inicializará las variables que lo requieran.
* Devolverá la referencia al pokemon creado o NULL si no pudo crearse.
* Puede agregar parámetros si lo desea.
*/
entrenador_t* crear_entrenador(char nombre[MAX_NOMBRE], char ciudad_natal[MAX_CIUDAD]);
/*
* Intentará capturar un pokemon.
* En caso de poder, lo almacenará como pokemon actual.
* Tener en cuenta que no el entrenador no puede llevar consigo muchos pokemones, si el entrenador es de
* un tipo no suele capturar pokemones de otro tipo, los pokemones no se dejan capturar tan facilmente, etc.
* Devolverá 0 si pudo capturar el pokemon o -1 si no.
*/
int capturar_pokemon(entrenador_t* entrenador, pokemon_t pokemon);

int main(int argc, char const *argv[])
{
        /* code */
        return 0;
}
