# Reporte Final — PRATCICE-I-SORTING-LARGE-DATASET
**QuickSort · HeapSort · Árbol Binario AVL**

Matías Cardona Acosta & Simón Madrid Noreña — Estructuras de Datos y Algoritmos 

---

## 1. Introducción

Nuestro proyecto constó de organizar un listado de 100,000 palabras usando los algoritmos de QuickSort y HeapSort, y con la estructura de árbol binario AVL. El programa carga el dataset desde `dataset.txt`, ejecuta cada enfoque de forma independiente sobre una copia del arreglo original, verifica que el resultado esté correctamente ordenado, mide el tiempo con `std::chrono::high_resolution_clock`, guarda cada resultado en un archivo de texto separado y presenta un análisis comparativo final.

---

## 2. Enfoque de Implementación

### 2.1 QuickSort — `quicksort.h`

El primer algoritmo usado, el QuickSort, consiste en primero encontrar un "pivote" dentro de la lista, calculando la media entre el valor máximo y mínimo de la lista (método "median of three"), para luego agrupar todos los valores mayores y menores al pivote juntos; luego, dentro de cada grupo de datos, se encuentran pivotes en cada uno y se repite el proceso; esto eventualmente organizaría los datos. La implementación trabaja directamente sobre un `std::vector<std::string>` sin hacer uso de `std::sort`.

#### `medianOfThree`

Calcula el índice medio entre `low` y `high`, ordena los tres elementos en sitio mediante intercambios y coloca el mediano en `arr[high]` para que sirva como pivote:
```cpp
int mid = low + (high - low) / 2;
if (arr[low] > arr[mid])  std::swap(arr[low],  arr[mid]);
if (arr[low] > arr[high]) std::swap(arr[low],  arr[high]);
if (arr[mid] > arr[high]) std::swap(arr[mid],  arr[high]);
std::swap(arr[mid], arr[high]);   
```

#### `partition`

Toma el pivote ubicado en `arr[high]` y reorganiza el subarreglo de forma que todos los elementos menores o iguales queden a su izquierda. Retorna la posición final del pivote:
```cpp
int i = low - 1;
for (int j = low; j < high; ++j)
    if (arr[j] <= pivot) { ++i; std::swap(arr[i], arr[j]); }
std::swap(arr[i + 1], arr[high]);
return i + 1;
```

#### `quickSort`

Función principal recursiva. Obtiene el índice del pivote con `partition` y se llama a sí misma sobre los subarreglos a cada lado hasta que `low >= high`:
```cpp
if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}
```

---

### 2.2 HeapSort — `heapsort.h`

El segundo algoritmo usado es el HeapSort, basado en la estructura del "heap", que es un árbol binario organizado donde los nodos hijos deben ser menores que sus padres (max heap). El algoritmo organiza los datos como si se tratara de un heap, mueve el primer elemento (nodo raíz, que es el mayor) y lo cambia por el último; luego vuelve a construir el max heap sin incluir el último elemento, repitiendo el proceso hasta que todos los datos estén organizados.

#### `heapify`

Mantiene la propiedad de max-heap en el subárbol con raíz en el índice `i`. Localiza el mayor entre el nodo y sus hijos (calculados con `2i+1` y `2i+2`), intercambia si es necesario y llama recursivamente hacia abajo:
```cpp
int largest = i;
int left = 2 * i + 1,  right = 2 * i + 2;
if (left  < n && arr[left]  > arr[largest]) largest = left;
if (right < n && arr[right] > arr[largest]) largest = right;
if (largest != i) { std::swap(arr[i], arr[largest]); heapify(arr, n, largest); }
```

#### `heapSort`

Construye el max-heap inicial (Build-Heap, O(n)) y luego extrae el máximo iterativamente:
```cpp
for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);  
for (int i = n - 1; i > 0; --i) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
}
```

---

### 2.3 Árbol Binario AVL — `avl.h`

La tercera estructura es el árbol binario de búsqueda auto-balanceado AVL. Cada nodo (`struct AVLNode`) almacena la palabra (`key`), punteros al hijo izquierdo y derecho, y su altura. La propiedad de balance garantiza que la diferencia de alturas entre los subárboles de cualquier nodo no supere 1, lo que mantiene las operaciones en O(log n) incluso en el peor caso.

#### Funciones auxiliares

- `avlHeight` — devuelve la altura de un nodo (0 si es nulo).
- `balanceFactor` — calcula la diferencia entre subárboles.
- `updateHeight` — recalcula la altura como `1 + máx(altura izquierda, altura derecha)`.

#### Rotaciones

Cuatro casos de rebalanceo mediante rotaciones simples y dobles:
```cpp
if (bf >  1 && key < node->left->key)  return rotateRight(node);              
if (bf < -1 && key > node->right->key) return rotateLeft(node);             
if (bf >  1 && key > node->left->key)
    { node->left = rotateLeft(node->left);   return rotateRight(node); }       
if (bf < -1 && key < node->right->key)
    { node->right = rotateRight(node->right); return rotateLeft(node); }       
```

#### `avlInsert` e `inorder`

`avlInsert` inserta cada palabra recursivamente ignorando duplicados y aplica la rotación correspondiente tras cada inserción. Una vez insertadas las 100,000 palabras, `inorder` recorre el árbol en orden izquierda–raíz–derecha acumulando las claves en un `std::vector<std::string>`. Finalmente `deleteTree` libera la memoria de todos los nodos.

---

## 3. Mediciones de Rendimiento

Los tiempos se midieron con `std::chrono::high_resolution_clock` (resolución de microsegundos) sobre el dataset de 100,000 palabras leídas de `dataset.txt`, compilando con `g++ -O2`. Los tiempos incluyen únicamente la fase de ordenamiento. La memoria se calcula usando `sizeof`: `sizeof(string)` = 32 bytes para los vectores y `sizeof(AVLNode)` para el árbol más el vector resultado.

| Algoritmo | Tiempo (ms) | Complejidad | Memoria usada | In-place |
|---|---|---|---|---|
| **QuickSort** | **70.22 ms** | O(n log n) promedio \| O(n²) peor caso | 3,200,000 bytes (~3.05 MB) | ✅ Sí |
| HeapSort | 144.30 ms | O(n log n) siempre (mejor / promedio / peor) | 3,200,000 bytes (~3.05 MB) | ✅ Sí |
| Árbol AVL | 148.44 ms | O(n log n) inserción + O(n) recorrido | 8,800,000 bytes (~8.39 MB) | ❌ No |

---

## 4. Archivos de Salida Generados

Al finalizar la ejecución, el programa genera automáticamente tres archivos de texto con las 100,000 palabras ordenadas alfabéticamente, uno por cada método. Cada archivo es generado por la función `saveToFile()` en `main.cpp`, que escribe cada palabra precedida de su número de posición:
```cpp
for (size_t i = 0; i < arr.size(); ++i)
    f << (i + 1) << ". " << arr[i] << "\n";
```

Formato de cada línea: `número. palabra` — por ejemplo: `1. aardvark`, `2. abacus`, `3. abandon`...

| Archivo generado | Algoritmo origen | Contenido |
|---|---|---|
| `sorted_quicksort.txt` | QuickSort | 100,000 palabras ordenadas alfabéticamente, numeradas `1. word` |
| `sorted_heapsort.txt` | HeapSort | 100,000 palabras ordenadas alfabéticamente, numeradas `1. word` |
| `sorted_avl.txt` | Árbol AVL | 100,000 palabras ordenadas alfabéticamente, numeradas `1. word` |

El programa confirma en consola la creación de cada archivo con el mensaje `"Guardado: ../sorted_X.txt (100000 palabras)"`. Los tres archivos producen resultados idénticos en contenido y orden, lo que sirve como verificación adicional de que los tres algoritmos producen la misma ordenación correcta.

---

## 5. Comparación entre Algoritmos

### 5.1 Tiempo de ejecución

QuickSort fue el más rápido con **70.22 ms**, casi el doble de rápido que HeapSort (144.30 ms) y el árbol AVL (148.44 ms). La ventaja de QuickSort se explica por su excelente localidad de caché: trabaja in-place sobre memoria contigua, por lo que los accesos son altamente predecibles para el procesador. HeapSort genera patrones de acceso no secuenciales durante `heapify` (accede a posiciones `2i+1` y `2i+2` en saltos), produciendo más fallos de caché. El AVL tiene latencia similar a HeapSort pero con mayor consumo de memoria por la asignación dinámica (`new AVLNode`) y las posibles rotaciones.

### 5.2 Complejidad algorítmica

Los tres enfoques tienen complejidad O(n log n) en el caso promedio. La diferencia crítica está en el peor caso: QuickSort puede degradarse a O(n²) si el pivote siempre cae en el extremo; Median-of-Three reduce drásticamente esta probabilidad. HeapSort y el AVL garantizan O(n log n) en todos los casos. Esto explica por qué la complejidad teórica no siempre refleja el tiempo real: la localidad de caché, el overhead de asignación dinámica y las constantes ocultas en la notación Big-O impactan significativamente el rendimiento práctico.

### 5.3 Uso de memoria

QuickSort y HeapSort comparten la misma huella (~3.05 MB), operando in-place. El árbol AVL consume ~8.39 MB, aproximadamente 2.75 veces más, por la asignación dinámica de un nodo por cada una de las 100,000 palabras más el vector resultado.

### 5.4 Ventajas y desventajas

- **QuickSort**: muy rápido en la práctica gracias a la localidad de caché, in-place, pero con peor caso O(n²) teórico.
- **HeapSort**: garantía estricta de O(n log n) en todos los casos, in-place con O(1) de memoria extra, pero más lento por patrones de acceso no secuenciales.
- **Árbol AVL**: mayor consumo de memoria y tiempo para ordenamiento por lotes, pero ofrece búsqueda e inserción incremental en O(log n), ideal si los datos llegan de forma continua.

---

## 6. Conclusiones

- **QuickSort** es el enfoque más apropiado para este problema. Con **70.22 ms** fue casi dos veces más rápido, opera in-place con ~3.05 MB y su implementación con Median-of-Three mitiga eficazmente el riesgo de degradarse a O(n²).
- **HeapSort** es la mejor alternativa cuando se necesita garantía estricta de O(n log n) en el peor caso con O(1) de memoria extra. Con **144.30 ms** sigue siendo competitivo y su comportamiento es completamente predecible.
- **Árbol AVL** resultó el de mayor consumo de memoria (~8.39 MB) con **148.44 ms**. Para ordenamiento por lotes es menos competitivo, pero sería ideal si se necesitaran búsquedas dinámicas o inserciones incrementales en tiempo real.
- Los tres métodos generan correctamente sus archivos de salida (`sorted_quicksort.txt`, `sorted_heapsort.txt`, `sorted_avl.txt`) con las 100,000 palabras numeradas y ordenadas alfabéticamente, confirmando la corrección de todas las implementaciones.

En síntesis, **QuickSort es la solución óptima para este caso de uso**, con HeapSort como alternativa robusta y el árbol AVL como opción adecuada si el contexto requiriera operaciones de búsqueda dinámica tras el ordenamiento.
