#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
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

void dibujarAhorcado(int intentos, int intentosMax) {
    int partes = 6;
    int partesMostrar = (int)round((double)(intentosMax - intentos) / intentosMax * partes);

    printf("  +---+\n");
    printf("  |   |\n");

    if (partesMostrar > 0) printf("  O   |\n");
    else printf("      |\n");

    if (partesMostrar == 0) printf("      |\n");
    else if (partesMostrar == 1) printf("  |   |\n");
    else if (partesMostrar == 2) printf(" /|   |\n");
    else if (partesMostrar >= 3) printf(" /|\\  |\n");

    if (partesMostrar <= 3) printf("      |\n");
    else if (partesMostrar == 4) printf(" /    |\n");
    else if (partesMostrar >= 5) printf(" / \\  |\n");

    printf("      |\n");
    printf("=========\n");
}

int calcularPuntaje(const char* dificultad, int errores) {
    int puntajeBase;

    if (strcmp(dificultad, "facil") == 0 || strcmp(dificultad, "Fácil") == 0)
        puntajeBase = 100;
    else if (strcmp(dificultad, "media") == 0 || strcmp(dificultad, "Media") == 0)
        puntajeBase = 200;
    else if (strcmp(dificultad, "dificil") == 0 || strcmp(dificultad, "Difícil") == 0)
        puntajeBase = 300;
    else
        puntajeBase = 200; // por defecto si la dificultad es inválida

    // Por cada error, se descuenta un 10% del puntaje base
    float descuento = errores * 0.10f * puntajeBase;
    int puntajeFinal = puntajeBase - (int)descuento;
    if (puntajeFinal < 0) puntajeFinal = 0; // nunca negativo

    return puntajeFinal;
}


void iniciarPartida(Map* mapaPalabras, Map* mapaCategorias, List* listaJugadores) {
    char nombre[50];
    printf("Ingrese su nombre: ");
    scanf("%s", nombre);

    Jugador* jugador = NULL;
    Jugador* temp = list_first(listaJugadores);
    while (temp) {
        if (strcmp(temp->nombre, nombre) == 0) {
            jugador = temp;
            break;
        }
        temp = list_next(listaJugadores);
    }

    if (!jugador) {
        jugador = malloc(sizeof(Jugador));
        jugador->nombre = strdup(nombre);
        jugador->puntajeTotal = 0;
        list_pushBack(listaJugadores, jugador);
    }

    int puntajeSesion = 0;

    for (int ronda = 1; ronda <= 3; ronda++) {
        printf("\n--- Palabra %d de 3 ---\n", ronda);

        printf("\nCategorías disponibles:\n");
        MapPair* par = map_first(mapaCategorias);
        while (par) {
            printf("- %s\n", (char*)par->key);
            par = map_next(mapaCategorias);
        }

        char categoria[50];
        printf("Seleccione una categoría: ");
        scanf("%s", categoria);

        List* listaDificultades = map_get(mapaCategorias, categoria);
        if (!listaDificultades) {
            printf("⚠️ Categoría no encontrada.\n");
            ronda--;
            continue;
        }

        printf("\nDificultades disponibles:\n");
        char* dif = list_first(listaDificultades);
        while (dif) {
            printf("- %s\n", dif);
            dif = list_next(listaDificultades);
        }

        char dificultad[50];
        printf("Seleccione una dificultad: ");
        scanf("%s", dificultad);

        int intentosMax;

        if (strcmp(dificultad, "facil") == 0 || strcmp(dificultad, "Fácil") == 0)
            intentosMax = 8;
        else if (strcmp(dificultad, "media") == 0 || strcmp(dificultad, "Media") == 0)
            intentosMax = 6;
        else if (strcmp(dificultad, "dificil") == 0 || strcmp(dificultad, "Difícil") == 0)
            intentosMax = 4;
        else {
            printf("⚠️ Dificultad no válida. Usando dificultad media.\n");
            intentosMax = 6;
        }

        int intentos = intentosMax;

        char clave[100];
        snprintf(clave, sizeof(clave), "%s-%s", categoria, dificultad);
        List* listaPalabras = map_get(mapaPalabras, clave);

        if (!listaPalabras || list_first(listaPalabras) == NULL) {
            printf("⚠️ No hay palabras para esta categoría/dificultad.\n");
            ronda--;
            continue;
        }

        int total = 0;
        Palabra* p = list_first(listaPalabras);
        while (p) {
            total++;
            p = list_next(listaPalabras);
        }

        int index = rand() % total;
        list_first(listaPalabras);
        for (int i = 0; i < index; i++) list_next(listaPalabras);
        Palabra* palabraJuego = list_current(listaPalabras);

        int largo = strlen(palabraJuego->palabra);
        int letrasAcertadas = 0;
        char letrasUsadas[50] = "";
        char estado[50];
        for (int i = 0; i < largo; i++) estado[i] = '_';
        estado[largo] = '\0';

        while (intentos > 0 && letrasAcertadas < largo) {
            printf("\nPalabra: ");
            for (int i = 0; i < largo; i++) {
                printf("%c ", estado[i]);
            }
            printf("\nIntentos restantes: %d\n", intentos);
            printf("Letras usadas: ");
            for (int i = 0; i < strlen(letrasUsadas); i++) {
                printf("%c", letrasUsadas[i]);
                if (i < strlen(letrasUsadas) - 1) printf(" - ");
            }
            printf("\n");

            dibujarAhorcado(intentos, intentosMax);

            char entrada[100];
            printf("Ingrese una letra o la palabra completa: ");
            scanf("%s", entrada);

            // Si el usuario ingresa la palabra completa y es correcta
            if (strlen(entrada) > 1) {
                if (strcasecmp(entrada, palabraJuego->palabra) == 0) {
                    for (int i = 0; i < largo; i++) {
                        estado[i] = palabraJuego->palabra[i];
                    }
                    letrasAcertadas = largo;
                    printf("¡Adivinaste la palabra completa!\n");
                    break;
                } else {
                    printf("Palabra incorrecta.\n");
                    intentos--;
                    continue;
                }
            }

            // Si el usuario ingresa solo una letra
            char letra = tolower(entrada[0]);
            if (!isalpha(letra) || strlen(entrada) != 1) {
                printf("⚠️ Debe ingresar solo una letra o la palabra completa.\n");
                continue;
            }

            if (strchr(letrasUsadas, letra)) {
                printf("⚠️ Ya usaste esa letra.\n");
                continue;
            }

            strncat(letrasUsadas, &letra, 1);

            int acierto = 0;
            for (int i = 0; i < largo; i++) {
                if (tolower(palabraJuego->palabra[i]) == letra && estado[i] == '_') {
                    estado[i] = palabraJuego->palabra[i];
                    letrasAcertadas++;
                    acierto = 1;
                }
            }

            if (!acierto) {
                intentos--;
                printf("Letra incorrecta.\n");
            } else {
                printf("¡Acierto!\n");
            }
        }

        int erroresCometidos = intentosMax - intentos;
        int puntaje = calcularPuntaje(dificultad, erroresCometidos);

        if (letrasAcertadas == largo) {
            printf("🎉 ¡Ganaste! La palabra era: %s\n", palabraJuego->palabra);
        } else {
            printf("💀 Perdiste. La palabra era: %s\n", palabraJuego->palabra);
        }

        puntajeSesion += puntaje;
        printf("Puntaje obtenido en esta palabra: %d\n", puntaje);
        printf("Puntaje acumulado en la sesión: %d\n", puntajeSesion);

        printf("Presione ENTER para continuar...");
        getchar();
        getchar();
    }

    jugador->puntajeTotal += puntajeSesion;
    printf("\n=== Fin de la partida ===\n");
    printf("Puntaje total obtenido en la sesión: %d\n", puntajeSesion);
    printf("Tu puntaje total acumulado: %d\n", jugador->puntajeTotal);
}

int compararPuntajes(const void* a, const void* b) {
    Jugador* j1 = *(Jugador**)a;
    Jugador* j2 = *(Jugador**)b;
    return j2->puntajeTotal - j1->puntajeTotal;
}

void mostrarRanking(List* listaJugadores) {
    if (list_first(listaJugadores) == NULL) {
        printf("\nNo hay jugadores registrados todavia.\n");
        return;
    }

    int cantidad = 0;
    Jugador* j = list_first(listaJugadores);
    while (j != NULL) {
        cantidad++;
        j = list_next(listaJugadores);
    }

    Jugador** arreglo = malloc(sizeof(Jugador*) * cantidad);

    j = list_first(listaJugadores);
    for (int i = 0; i < cantidad; i++) {
        arreglo[i] = j;
        j = list_next(listaJugadores);
    }

    qsort(arreglo, cantidad, sizeof(Jugador*), compararPuntajes);

    printf("\n Ranking de jugadores \n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s — %d puntos\n", i + 1, arreglo[i]->nombre, arreglo[i]->puntajeTotal);
    }

    free(arreglo);
}

void testRanking(List* listaJugadores) {
    Jugador* a = malloc(sizeof(Jugador));
    a->nombre = strdup("Agustin");
    a->puntajeTotal = 250;

    Jugador* b = malloc(sizeof(Jugador));
    b->nombre = strdup("Miguel");
    b->puntajeTotal = 320;

    Jugador* c = malloc(sizeof(Jugador));
    c->nombre = strdup("Alejandro");
    c->puntajeTotal = 180;

    list_pushBack(listaJugadores, a);
    list_pushBack(listaJugadores, b);
    list_pushBack(listaJugadores, c);

    mostrarRanking(listaJugadores);
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
                if (map_first(mapaPalabras) == NULL) {
                    printf("⚠️ Debe cargar un archivo de palabras antes de iniciar una partida.\n");
                    break;
                }
                iniciarPartida(mapaPalabras, mapaCategorias, listaJugadores);
                break;
            case 3:
                mostrarRanking(listaJugadores);
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