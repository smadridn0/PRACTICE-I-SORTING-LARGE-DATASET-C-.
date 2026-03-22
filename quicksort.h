#pragma once
#include <vector>
#include <string>

// Selecciona el pivote como la mediana entre arr[low], arr[mid] y arr[high],
// y lo deja al final del rango para facilitar la partición
int medianOfThree(std::vector<std::string>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    // Ordena los tres elementos para encontrar la mediana
    if (arr[low] > arr[mid])  std::swap(arr[low],  arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low],  arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid],  arr[high]);

    std::swap(arr[mid], arr[high]); // Mueve la mediana al final como pivote
    return high;
}

// Particiona el rango [low, high] en torno al pivote:
// elementos menores o iguales quedan a la izquierda, mayores a la derecha
int partition(std::vector<std::string>& arr, int low, int high) {
    int pivotIdx = medianOfThree(arr, low, high);
    const std::string& pivot = arr[pivotIdx];
    int i = low - 1;

    for (int j = low; j < high; ++j)
        if (arr[j] <= pivot) { ++i; std::swap(arr[i], arr[j]); }

    std::swap(arr[i + 1], arr[high]); // Coloca el pivote en su posición final
    return i + 1;                     // Retorna el índice del pivote
}

// Ordena el rango [low, high] recursivamente usando QuickSort
void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Particiona y obtiene la posición del pivote
        quickSort(arr, low, pi - 1);        // Ordena la mitad izquierda
        quickSort(arr, pi + 1, high);       // Ordena la mitad derecha
    }
}
