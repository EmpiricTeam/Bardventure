#include "ej_modulos/Juego.h"

int main()
{
    system("cd ../../../ && ./setup.sh");
    Juego *a = Juego::getInstance();

    a->run();

    return 0;
}
