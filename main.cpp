#include "maze.h"

int main() {
    Nodo** matrix = crearMatriz();
    crearLaberinto(matrix);
    char** dibujo=generarLaberinto(matrix);
    imprimirLaberinto(dibujo);
    InicioFin(matrix, dibujo);
    return 0;
}
