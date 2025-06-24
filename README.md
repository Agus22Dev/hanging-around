# 🎮 Hanging Around — El clásico juego del ahorcado, reinventado en C 🧠

¡Bienvenido a *Hanging Around*!  
Una versión moderna, personalizable y desafiante del tradicional juego del ahorcado, construida completamente en **lenguaje C** y ejecutada en **consola**.

---

## 📌 ¿Qué hace esta aplicación?

🔤 El usuario puede:
- Cargar archivos `.csv` con palabras clasificadas por **categoría** y **dificultad**.
- Jugar partidas personalizadas, eligiendo la temática y el nivel de reto.
- Ingresar letras e ir descubriendo la palabra oculta.
- Obtener un **puntaje dinámico** según el rendimiento.
- Ver el **ranking** de jugadores durante la sesión.

Todo esto ocurre desde una **interfaz en terminal** clara, fluida y validada.

---

## 🛠️ Estructuras de datos usadas

| TDA        | Función principal                              |
|------------|------------------------------------------------|
| `Palabra`  | Representa palabra + categoría + dificultad     |
| `Jugador`  | Guarda nombre + puntaje acumulado               |
| `Map`      | Agrupa palabras por clave: `"Categoria-Dificultad"` |
| `List`     | Almacena palabras, letras usadas y jugadores    |

✔️ El sistema fue diseñado con un enfoque **modular y eficiente**, usando **mapas hash** para acceso rápido y **listas enlazadas** para flexibilidad dinámica.

---

## 📁 Formato de archivo `.csv`

Tu archivo debe tener el siguiente formato (sin encabezado):

```
jirafa,Animales,Fácil
canadá,Países,Media
teclado,Objetos,Difícil
```

---

## 🚀 ¿Cómo ejecutar el programa?

1. Asegúrate de tener un compilador C (`gcc` o similar).
2. Clona o descarga este repositorio.
3. Compila el programa:
   ```bash
   gcc Hanging.c tdas/*.c -o hanging -lm
   ```
4. Ejecuta:
   ```bash
   ./hanging
   ```

---

## 📷 Vista previa

```
[1] Cargar archivo de palabras
[2] Iniciar nueva partida
[3] Ver ranking
[4] Créditos
[5] Salir 
```
Durante el juego:
```
Categorías disponibles:
1. animales
Seleccione una categoría: 
Seleccione dificultad (facil, media, dificil):

Tamaño de la lista para 'categoria-animales': [cantidad de palabras en la dificultad]

Palabra 1 de 5
  +---+
  |   |
      |
      |
      |
      |
=========
_ _ _ _ _ _ _
Letras erradas:
Intentos restantes: 6
Ingrese una letra:
```

---

## 🧠 Lógica de puntaje

El puntaje se basa en:
- La dificultad seleccionada (Fácil, Media, Difícil).
- La cantidad de errores cometidos.

**Mientras menos falles, más puntaje obtienes.**

---

## 👥 Créditos

Desarrollado por:

- 🧠 Agustín Sandoval (Carga CSV, lógica de validación, documentación)
- 💻 Miguel Santibáñez (Diseño de estructuras, validación de letras y puntaje)
- 🎮 Alejandro Rivera (Lógica del juego, experiencia de usuario y pruebas)

---

## 📈 ¿Futuras mejoras?

- Guardado persistente del ranking 📝
- Interfaz gráfica básica en ncurses o similar 🎨
- Dificultad progresiva adaptativa 🔁

---

¡Gracias por jugar con nosotros!  
*Hanging Around* es más que un juego: es una muestra de lo que se puede lograr dominando estructuras de datos.