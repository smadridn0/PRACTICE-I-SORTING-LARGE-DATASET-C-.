#pragma once
#include <vector>
#include <string>

// Mantiene la propiedad de max-heap desde el nodo i hacia abajo
void heapify(std::vector<std::string>& arr, int n, int i) {
    int largest = i;        // Asume que el nodo actual es el mayor
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    // Comprueba si algún hijo supera al nodo actual
    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    // Si el mayor no es el nodo actual, intercambia y continúa bajando
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Ordena el vector de cadenas en orden ascendente usando heap sort
void heapSort(std::vector<std::string>& arr) {
    int n = (int)arr.size();

    // Construye el max-heap desde el último nodo interno hacia la raíz
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    // Extrae el mayor elemento (raíz) y reordena el heap repetidamente
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]); // Mueve la raíz al final del arreglo
        heapify(arr, i, 0);        // Restaura el heap sobre el rango reducido
    }
}
