# 🎮 Hanging Around - Juego de Ahorcado

¡Bienvenido a *Hanging Around*, un entretenido juego de ahorcado en terminal! Diseñado para desafiar tu memoria y vocabulario, esta aplicación te permite elegir entre distintas categorías y dificultades mientras compites por el mejor puntaje 🏆.

---

## 📌 Descripción General

Hanging Around permite a los jugadores:
- 📂 **Cargar un archivo CSV** con palabras clasificadas por categoría y dificultad.
- 🧠 **Jugar partidas** en las que se puede adivinar letra por letra o la palabra completa.
- 🥇 **Registrar y mostrar rankings** de los jugadores con mejor desempeño.
- 😵‍💫 Visualizar el clásico monito del ahorcado dibujado con caracteres ASCII.
- 🧑‍💻 Ejecutarse directamente desde la consola con una interfaz simple y clara.

---

## 🚀 ¿Cómo ejecutar el programa?

1. Abre una terminal y ve a la carpeta raíz del proyecto.
2. Compila el programa con:

```bash
gcc Hanging.c tdas/list.c tdas/map.c -Itdas -lm -o hanging_around.exe
```

3. Ejecuta el juego:

```bash
./hanging_around.exe
```

📝 Asegúrate de tener los archivos `.csv` en una carpeta llamada `data/`.

---

## 📁 Estructura esperada del CSV

> ⚠️ **Importante:** Las palabras en el archivo CSV **no deben contener espacios ni tildes** para evitar errores de lectura y evaluación. Usa solo caracteres simples y sin acentos.


Cada archivo `.csv` debe tener el siguiente formato (sin encabezados):

```
palabra,categoria,dificultad
gato,animales,facil
rinoceronte,animales,dificil
python,programacion,media
```

---

## 🎮 Menú principal

```
=== HANGING AROUND ===
1. Cargar archivo de palabras
2. Iniciar nueva partida
3. Ver ranking de jugadores
4. Salir
5. Créditos
```

---

## ⚙️ Funcionalidades destacadas

| Funcionalidad                  | Estado       | Descripción |
|-------------------------------|--------------|-------------|
| Carga de CSV dinámico         | ✅ Funcional | Lee palabras categorizadas por dificultad. |
| Juego de ahorcado             | ✅ Funcional | Muestra progreso, permite letras y palabras completas. |
| Ranking de jugadores          | ✅ Funcional | Ordenado automáticamente por puntaje total. |
| Créditos                      | ✅ Funcional | Muestra autores del proyecto. |
| Validación de errores         | ✅ Parcial   | Se detectan errores básicos en CSV y entrada de usuario. |
| Guardado de historial         | ❌ No incluye | El ranking se pierde al cerrar el programa. |

---

## ⚠️ Advertencias / Limitaciones

- Actualmente **no se guarda el ranking** en un archivo persistente. Al cerrar el programa, los datos se pierden.
- El sistema de entrada **no diferencia mayúsculas/minúsculas** en la palabra completa, pero **sí en letras individuales**.
- **Los acentos y caracteres especiales** pueden no mostrarse correctamente en sistemas que no tengan UTF-8 activo.
- Se recomienda que el nombre del CSV se ingrese **sin ruta ni extensión**, por ejemplo: `animales` buscará el archivo `data/animales.csv`.

---

## 🧑‍💻 Créditos

Desarrollado con cariño por:

- 👨‍💻 Agustín Sandoval  
- 👨‍💻 Miguel  Santibañez
- 👨‍💻 Alejandro Rivera  

🎓 Proyecto académico de la asignatura *Estructura de Datos*.

---

¡Gracias por jugar! 🕹️
