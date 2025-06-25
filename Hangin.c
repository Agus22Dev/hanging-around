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
    printf("Ingrese el nombre del archivo CSV (ej: data/animales.csv): ");
    scanf("%s", nombreArchivo);

    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("❌ No se pudo abrir el archivo.\n");
        return;
    }

    char linea[200];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = 0;
        char* token = strtok(linea, ",");
        if (!token) continue;

        char* palabra = token;
        char* categoria = strtok(NULL, ",");
        char* dificultad = strtok(NULL, ",");

        if (!palabra || !categoria || !dificultad) continue;

        Palabra* nueva = crearPalabra(palabra, categoria, dificultad);

        char clave[100];
        snprintf(clave, sizeof(clave), "%s-%s", categoria, dificultad);

        List* lista = map_get(mapaPalabras, clave);
        if (!lista) {
            lista = list_create();
            map_insert(mapaPalabras, strdup(clave), lista);
        }
        list_pushBack(lista, nueva);
        agregarDificultad(mapaCategorias, categoria, dificultad);
    }

    fclose(archivo);
    printf("✅ Archivo cargado correctamente.\n");
}

void iniciarPartida(Map* mapaPalabras, Map* mapaCategorias, List* listaJugadores) {
    char nombre[50];
    printf("\nIngrese su nombre: ");
    scanf("%s", nombre);

    // Crear o recuperar jugador
    Jugador* jugador = NULL;
    Jugador* temp = list_first(listaJugadores);
    while (temp != NULL) {
        if (strcmp(temp->nombre, nombre) == 0) {
            jugador = temp;
            break;
        }
        temp = list_next(listaJugadores);
    }

    if (jugador == NULL) {
        jugador = malloc(sizeof(Jugador));
        jugador->nombre = strdup(nombre);
        jugador->puntajeTotal = 0;
        list_pushBack(listaJugadores, jugador);
    }

    // Mostrar categorías
    printf("\nCategorias disponibles:\n");
    void* it = map_first(mapaCategorias);
    while (it != NULL) {
        printf("- %s\n", map_key(mapaCategorias));
        it = map_next(mapaCategorias);
    }

    char categoria[50];
    printf("Seleccione una categoria: ");
    scanf("%s", categoria);

    List* listaDificultades = map_get(mapaCategorias, categoria);
    if (listaDificultades == NULL) {
        printf("Categoria no encontrada.\n");
        return;
    }

    // Mostrar dificultades
    printf("\nDificultades disponibles:\n");
    char* d = list_first(listaDificultades);
    while (d != NULL) {
        printf("- %s\n", d);
        d = list_next(listaDificultades);
    }

    char dificultad[50];
    printf("Seleccione una dificultad: ");
    scanf("%s", dificultad);

    // Buscar lista de palabras
    char clave[100];
    snprintf(clave, sizeof(clave), "%s-%s", categoria, dificultad);

    List* listaPalabras = map_get(mapaPalabras, clave);
    if (listaPalabras == NULL || list_first(listaPalabras) == NULL) {
        printf("No hay palabras para esta combinacion.\n");
        return;
    }

    // Elegir palabra aleatoria
    int total = 0;
    Palabra* p = list_first(listaPalabras);
    while (p != NULL) {
        total++;
        p = list_next(listaPalabras);
    }

    int index = rand() % total;
    list_first(listaPalabras);
    for (int i = 0; i < index; i++) list_next(listaPalabras);
    Palabra* palabraJuego = list_current(listaPalabras);

    // Iniciar juego del ahorcado
    int intentos = 6;
    int largo = strlen(palabraJuego->palabra);
    int letrasAcertadas = 0;
    char letrasUsadas[50] = "";
    char estado[50];
    for (int i = 0; i < largo; i++) estado[i] = '_';
    estado[largo] = '\0';

    printf("\nComienza el juego. Palabra de %d letras.\n", largo);
    while (intentos > 0 && letrasAcertadas < largo) {
        printf("Palabra: %s\n", estado);
        printf("Intentos restantes: %d\n", intentos);
        printf("Letras usadas: %s\n", letrasUsadas);

        char letra;
        printf("Ingrese una letra: ");
        scanf(" %c", &letra);

        if (strchr(letrasUsadas, letra)) {
            printf("Ya usaste esa letra.\n");
            continue;
        }

        strncat(letrasUsadas, &letra, 1);

        int acierto = 0;
        for (int i = 0; i < largo; i++) {
            if (palabraJuego->palabra[i] == letra && estado[i] == '_') {
                estado[i] = letra;
                letrasAcertadas++;
                acierto = 1;
            }
        }

        if (!acierto) {
            intentos--;
            printf("Letra incorrecta.\n");
        } else {
            printf("Acierto!\n");
        }
    }

 // añadir puntajes miguel
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
    Map* mapaPalabras = map_create(is_equal_string);
    Map* mapaCategorias = map_create(is_equal_string);
    List* listaJugadores = list_create();
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                cargarArchivo(mapaPalabras, mapaCategorias);
                break;
            case 2:
                iniciarPartida(mapaPalabras, mapaCategorias, listaJugadores);
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