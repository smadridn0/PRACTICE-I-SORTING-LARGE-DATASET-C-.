#include <bits/stdc++.h>
#include "quicksort.h"
#include "heapsort.h"
#include "avl.h"

using namespace std;
using namespace std::chrono;

// Lee líneas de un archivo de texto y las retorna como vector de strings
vector<string> loadDataset(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir '" << filename << "'\n";
        exit(1);
    }
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            if (word.back() == '\r') word.pop_back(); // Elimina '\r' en archivos Windows
            words.push_back(word);
        }
    }
    return words;
}

// Verifica que el vector esté ordenado de forma ascendente
bool isSorted(const vector<string>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

// Calcula e imprime el uso estimado de memoria del algoritmo
void printMemory(const string& label, size_t elements,
                 size_t bytesPerElem, size_t extraBytes) {
    size_t total = elements * bytesPerElem + extraBytes;
    cout << "  Memoria : " << total << " bytes  (~"
         << fixed << setprecision(2) << total / 1024.0 / 1024.0
         << " MB)   [" << label << "]\n";
}

// Guarda el vector ordenado en un archivo, numerando cada línea
void saveToFile(const vector<string>& arr, const string& filename) {
    ofstream f(filename);
    if (!f.is_open()) {
        cerr << "Error: no se pudo crear " << filename << "\n";
        return;
    }
    for (size_t i = 0; i < arr.size(); ++i)
        f << (i + 1) << ". " << arr[i] << "\n";
    cout << "  Guardado: " << filename << "  (" << arr.size() << " palabras)\n";
}

int main() {
    const size_t STR_SIZE = sizeof(string);

    cout << "=========================================\n"
         << "  Practica I: Analisis de Ordenamiento  \n"
         << "=========================================\n";

    // Carga el dataset original desde archivo
    vector<string> original = loadDataset("../dataset.txt");
    cout << "  Dataset : " << original.size() << " palabras  (leidas de dataset.txt)\n\n";

    double qsMs = 0, hsMs = 0, avlMs = 0; // Tiempos de cada algoritmo en milisegundos

    // ─── 1. QuickSort ───────────────────────────────────────────
    cout << "-----------------------------------------\n"
         << "  1. QuickSort\n"
         << "-----------------------------------------\n";

    vector<string> qsArr = original;

    auto t1 = high_resolution_clock::now();
    quickSort(qsArr, 0, (int)qsArr.size() - 1);
    auto t2 = high_resolution_clock::now();

    qsMs = duration_cast<microseconds>(t2 - t1).count() / 1000.0;
    cout << "  Ordenado: " << (isSorted(qsArr) ? "SI  v" : "NO  x") << "\n";
    cout << "  Tiempo  : " << fixed << setprecision(3) << qsMs << " ms\n";
    cout << "  Big-O   : O(n log n) promedio  |  O(n^2) peor caso\n";
    printMemory("vector en sitio", qsArr.size(), STR_SIZE, 0);
    saveToFile(qsArr, "../sorted_quicksort.txt");
    cout << "\n";

    // ─── 2. HeapSort ────────────────────────────────────────────
    cout << "-----------------------------------------\n"
         << "  2. HeapSort\n"
         << "-----------------------------------------\n";

    vector<string> hsArr = original;

    auto t3 = high_resolution_clock::now();
    heapSort(hsArr);
    auto t4 = high_resolution_clock::now();

    hsMs = duration_cast<microseconds>(t4 - t3).count() / 1000.0;
    cout << "  Ordenado: " << (isSorted(hsArr) ? "SI  v" : "NO  x") << "\n";
    cout << "  Tiempo  : " << fixed << setprecision(3) << hsMs << " ms\n";
    cout << "  Big-O   : O(n log n) siempre (mejor / promedio / peor)\n";
    printMemory("monticulo binario en sitio", hsArr.size(), STR_SIZE, 0);
    saveToFile(hsArr, "../sorted_heapsort.txt");
    cout << "\n";

    // ─── 3. Árbol AVL ───────────────────────────────────────────
    cout << "-----------------------------------------\n"
         << "  3. AVL tree \n"
         << "-----------------------------------------\n";

    AVLNode* root = nullptr;
    vector<string> avlResult;
    avlResult.reserve(original.size());

    auto t5 = high_resolution_clock::now();
    for (const string& w : original)
        root = avlInsert(root, w); // Inserta cada palabra en el árbol
    inorder(root, avlResult);      // Extrae las claves ordenadas
    auto t6 = high_resolution_clock::now();

    avlMs = duration_cast<microseconds>(t6 - t5).count() / 1000.0;
    cout << "  Ordenado: " << (isSorted(avlResult) ? "SI  v" : "NO  x") << "\n";
    cout << "  Tiempo  : " << fixed << setprecision(3) << avlMs << " ms\n";
    cout << "  Big-O   : O(n log n) insercion  +  O(n) recorrido\n";
    printMemory("nodos AVL + vector resultado",
                avlResult.size(), sizeof(AVLNode),
                avlResult.size() * STR_SIZE);
    saveToFile(avlResult, "../sorted_avl.txt");
    cout << "\n";
    deleteTree(root); // Libera la memoria del árbol

    // ─── Tabla comparativa ──────────────────────────────────────
    cout << "=========================================\n"
         << "  ANALISIS COMPARATIVO\n"
         << "=========================================\n";

    cout << left
         << setw(12) << "Algoritmo"
         << setw(12) << "Tiempo(ms)"
         << setw(34) << "Big-O"
         << "En sitio\n";
    cout << string(70, '-') << "\n";
    cout << setw(12) << "QuickSort"
         << setw(12) << fixed << setprecision(2) << qsMs
         << setw(34) << "O(n log n) prom / O(n^2) peor" << "Si\n";
    cout << setw(12) << "HeapSort"
         << setw(12) << hsMs
         << setw(34) << "O(n log n) siempre"            << "Si\n";
    cout << setw(12) << "Arbol AVL"
         << setw(12) << avlMs
         << setw(34) << "O(n log n) + O(n) recorrido"   << "No\n";
    cout << "\n";

    // Determina el algoritmo más rápido comparando los tres tiempos
    double best = qsMs;
    string winner = "QuickSort";
    if (hsMs  < best) { best = hsMs;  winner = "HeapSort"; }
    if (avlMs < best) { best = avlMs; winner = "Arbol AVL"; }
    cout << "  Mas rapido: " << winner << "  (" << fixed << setprecision(2) << best << " ms)\n\n";

    return 0;
}
