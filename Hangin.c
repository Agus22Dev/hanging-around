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

// ==== FUNCIONES AUXILIARES ====

int is_equal_string(void* key1, void* key2) {
    return strcmp((char*)key1, (char*)key2) == 0;
}


Palabra* crearPalabra(char* palabra, char* categoria, char* dificultad) {
    Palabra* p = malloc(sizeof(Palabra));
    p->palabra = strdup(palabra);
    p->categoria = strdup(categoria);
    p->dificultad = strdup(dificultad);
    return p;
}

void agregarDificultad(Map* mapaCategorias, char* categoria, char* dificultad) {
    List* listaDificultades = map_get(mapaCategorias, categoria);
    if (listaDificultades == NULL) {
        listaDificultades = list_create();
        map_insert(mapaCategorias, strdup(categoria), listaDificultades);
    }

    char* existente = list_first(listaDificultades);
    while (existente != NULL) {
        if (strcmp(existente, dificultad) == 0) return;
        existente = list_next(listaDificultades);
    }

    list_pushBack(listaDificultades, strdup(dificultad));
}

// ==== FUNCIONES PRINCIPALES ====

void cargarArchivo(Map* mapaPalabras, Map* mapaCategorias) {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo CSV: ");
    scanf("%s", nombreArchivo);

    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }

    char linea[256];
    int contador = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        contador++;
        linea[strcspn(linea, "\n")] = '\0';

        char* palabra = strtok(linea, ",");
        char* categoria = strtok(NULL, ",");
        char* dificultad = strtok(NULL, ",");

        if (!palabra || !categoria || !dificultad) {
            printf("Linea %d mal formateada. Se omitira.\n", contador);
            continue;
        }

        char clave[128];
        snprintf(clave, sizeof(clave), "%s-%s", categoria, dificultad);

        List* lista = map_get(mapaPalabras, clave);
        if (lista == NULL) {
            lista = list_create();
            map_insert(mapaPalabras, strdup(clave), lista);
        }

        Palabra* nueva = crearPalabra(palabra, categoria, dificultad);
        list_pushBack(lista, nueva);
        agregarDificultad(mapaCategorias, categoria, dificultad);
    }

    fclose(archivo);
    printf("Archivo cargado correctamente.\n");
}


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