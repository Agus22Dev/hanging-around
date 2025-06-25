
================================================================================
                                HANGING AROUND
================================================================================

Descripción general:
--------------------
"Hanging Around" es un juego de ahorcado desarrollado en C, que permite a los 
usuarios jugar partidas adivinando palabras de distintas categorías y niveles 
de dificultad. El sistema soporta múltiples jugadores, ranking de puntajes y 
carga dinámica de archivos de palabras.

Estructura del proyecto:
------------------------
- Hangin.c           --> Archivo principal con la lógica del juego.
- tdas/              --> Carpeta con implementaciones de estructuras de datos:
    - map.h/.c       --> Mapa (diccionario clave-valor)
    - list.h/.c      --> Lista enlazada
    - stack.h        --> Pila (basada en lista)
    - queue.h        --> Cola (basada en lista)
    - set.h          --> Conjunto (basado en mapa)
    - heap.h/.c      --> Heap (cola de prioridad)
    - multimap.h     --> Multimapa
    - extra.h/.c     --> Funciones auxiliares (leer CSV, utilidades)
- data/              --> Archivos CSV con palabras por categoría:
    - animales.csv, comida.csv, deportes.csv, etc.

Cómo jugar:
-----------
1. Al iniciar el programa, se muestra un menú principal con opciones para:
    - Cargar archivo de palabras (por ejemplo: animales, comida, etc.)
    - Iniciar una nueva partida
    - Ver ranking de jugadores
    - Salir
    - Créditos

2. Para jugar, primero debes cargar un archivo de palabras desde la opción 1.
   El archivo debe estar en la carpeta "data" y tener formato CSV:
   palabra,categoria,dificultad

3. Al iniciar una partida, el jugador ingresa su nombre y juega 3 rondas,
   eligiendo categoría y dificultad en cada una. El sistema selecciona una
   palabra aleatoria y el jugador debe adivinarla letra por letra o completa.

4. El puntaje depende de la dificultad y los errores cometidos. Al finalizar,
   el puntaje se suma al ranking general.

Estructuras principales:
------------------------
- Palabra: Guarda la palabra, su categoría y dificultad.
- Jugador: Guarda el nombre y puntaje total.
- Mapas y listas: Para organizar palabras por categoría/dificultad y jugadores.

Archivos de palabras:
---------------------
- Los archivos CSV deben estar limpios, sin tildes ni espacios en las palabras.
- Ejemplo de línea: perro,animales,facil

Compilación y ejecución:
------------------------
- Compila con: gcc Hangin.c tdas/*.c -o hanging-around
- Ejecuta con: ./hanging-around

Autores:
--------
- Agustin
- Miguel
- Alejandro

¡Gracias por jugar Hanging