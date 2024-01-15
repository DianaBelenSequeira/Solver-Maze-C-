# SOLVER-MAZE-C++-

## Descripcion
Este programa en C++ genera laberintos aleatorios con un codigo solucionador que utiliza un algoritmo de busqueda recursiva para encontrar un camino desde la entrada hasta la salida, recorriendo distitas rutas como posibles soluciones.  El laberinto se representa como una matriz bidimensional y proporciona una visualizacion del camino que indica la solucion desde la entrada visualmente predispuesta entre las paredes de manera aleatoria, sin cloincidir en el mismo lugar, con la  salida. 

## Características
1. Generacion aleatoria de laberitos, con parametros personalizabes para ancho y largo de paredes.
2. Uso de un algoritmo de búsqueda recursiva de un camino desde el punto de entrada hasta la salida del laberinto.
3. Visualización del laberinto y del camino de salida en la consola.
4. Estructuras de datos para el manejo del seguimiento para el camino.

## Algoritmo
El programa para la realizacion del laberinto utiliza un algoritmo de búsqueda recursiva para que sea posible encontrar un camino desde el punto de entrada, aleatoriamente colocado en alguna posicion de mis paredes,  hasta un punto de salida en el laberinto. Este algoritmo recorre recursivamente todas las direcciones posibles desde cualquier un punto, almacenando, eliminando y construyendo un camino clave para encontrar la salida y utiliza la técnica de backtracking para retroceder y deshacer los pasos previos si se encuentra con una pared, asi hasta encontrar la salida.
La recursividad en este proyecto es una función que se llama a sí misma para resolver un problema, simplifica los procesos de escribir bucles y condiciones complicadas para el rcorrido de una ruta y el backtracking se tiene  un conjunto de llamadas recursivas que manejan naturalmente estos procesos.

## Estructura

  1. `Matriz()` : genera la matriz del laberinto con paredes y pasillos. Establece las dimensiones y la densidad de paredes del laberinto.. Coloca las paredes y define los puntos de entrada y salida aleatoriamente.
  2. `Laberinto()` : recorre la matriz e imprime en la consola con los simbolos propuestos en el codigo, las paredes, camino, entrada y salida del laberinto.
  3. `Camino()` : indica la solucion encontrada del camino almacenado para el laberinto, utiliza una pila para recorrer desde la entrada hasta la salida. SEva actualizando, de acuerdo al rastreo encontrado, indicando las casillas posibles.
  4. `buscar_salida()` : implementacion de la recursividad y su logica para hallar el camino, explora todas las posibles direcciones desde su posicion actual.
  5. `esValido()` : verifica si una celda es transitable, de que la posicion  no sea una pared y este en el limite dentro del laberinto.
  7. `class Stack` : implementa una pila con operaciones básicas para manejar el camino en el laberinto, constructor para una estructura de datos como una pila (Stack).

## Bibliotecas 
1. `<iostream>` :se utiliza para l a impresion de datos en la consola, permite visualizar el laberinto y el camino encontrado a traves del objeto `cout`
2. `<ctime>` : se utiliza para la generación de los números aleatorios. La función `time(NULL)` se utiliza como semilla para la función `srand()` que inicializa el generador de números aleatorios.


## Funcionalidad de `buscar_salida`:
Para i hallando el camino dstinado como solucion al laberinto empieza  marcando la trayectoria de las coordenadas actuales (x, y) en la pila camino, pasa a verificar si la posición actual se encuentra fuera de los límites del laberinto o es la salida, devoviendo true o false, si la posición actual no es válida, si es una pared  o ya haya sido visitada, la función descarta la posición actual. Marca la posición actual como visitada asignando el valor 2 en la matriz, si alguna devuelve true, significa que se ha encontrado un camino hacia la salida, y la función también devuelve true, si ninguna dirección resulta en un camino hacia la salida, deshace el último paso usando `pop` en la pila camino y retorna false, indicando que no es una salida posibble.
De esta manera va explorando una ruta y, para cada paso, se llama a sí misma para avanzar en cada dirección diferente y posible, esta secuencia crea una estructura de árbol de deision, donde cada nodo es un paso en el laberinto, y cada rama representa una dirección posible a explorar.






























