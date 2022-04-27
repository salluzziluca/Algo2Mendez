#include <iostream>

void sumar_uno(int &a) {
    a++;
}

int main(int argc, char const *argv[])
{
        std::string nombre;
        int edad;
        std::cin >> nombre;
        std::cin >> edad;
        sumar_uno(edad);
        std::cout << "Hola,"<< nombre << ", tu edad en año que viene va a ser " << edad <<  "\n";

        return 0;
}
