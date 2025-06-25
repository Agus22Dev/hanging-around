#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdas/map.h"
#include "tdas/list.h"
#include <windows.h>

// Estructuras base
typedef struct {
    char* palabra;
    char* categoria;
    char* dificultad;
} Palabra;

typedef struct {
    char* nombre;
    int puntajeTotal;
} Jugador;

void mostrarMenu() {
    printf("\n=== HANGING AROUND ===\n");
    printf("1. Cargar archivo de palabras\n");
    printf("2. Iniciar nueva partida\n");
    printf("3. Ver ranking de jugadores\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

//chato

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("AQUI VA FUNCION");
                break;
            case 2:
                printf("AQUI VA FUNCION");
                break;
            case 3:
                printf("AQUI VA FUNCION");
                break;
            case 4:
                printf("Gracias por jugar Hanging Around. Hasta la proxima!\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 4);

    return 0;
}