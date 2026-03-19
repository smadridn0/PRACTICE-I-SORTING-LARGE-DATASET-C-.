#include <bits/stdc++.h>
#include "quicksort.h"
#include "heapsort.h"
#include "avl.h"

using namespace std;
using namespace std::chrono;

vector<string> loadDataset(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: cannot open '" << filename << "'\n";
        exit(1);
    }
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            if (word.back() == '\r') word.pop_back();
            words.push_back(word);
        }
    }
    return words;
}

bool isSorted(const vector<string>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}

void printMemory(const string& label, size_t elements,
                 size_t bytesPerElem, size_t extraBytes) {
    size_t total = elements * bytesPerElem + extraBytes;
    cout << "  Memory  : " << total << " bytes  (~"
         << fixed << setprecision(2) << total / 1024.0 / 1024.0
         << " MB)   [" << label << "]\n";
}

void saveToFile(const vector<string>& arr, const string& filename) {
    ofstream f(filename);
    if (!f.is_open()) {
        cerr << "Error: cannot create " << filename << "\n";
        return;
    }
    for (size_t i = 0; i < arr.size(); ++i)
        f << (i + 1) << ". " << arr[i] << "\n";
    cout << "  Saved   : " << filename << "  (" << arr.size() << " words)\n";
}

int main() {
    const size_t STR_SIZE = sizeof(string);

    cout << "=========================================\n"
         << "  Practice I: Sorting Analysis  \n"
         << "=========================================\n";

    vector<string> original = loadDataset("../dataset.txt");
    cout << "  Dataset : " << original.size() << " words  (read from dataset.txt)\n\n";

    double qsMs = 0, hsMs = 0, avlMs = 0;

    cout << "-----------------------------------------\n"
         << "  1. QuickSort\n"
         << "-----------------------------------------\n";

    vector<string> qsArr = original;

    auto t1 = high_resolution_clock::now();
    quickSort(qsArr, 0, (int)qsArr.size() - 1);
    auto t2 = high_resolution_clock::now();

    qsMs = duration_cast<microseconds>(t2 - t1).count() / 1000.0;
    cout << "  Sorted  : " << (isSorted(qsArr) ? "YES v" : "NO x") << "\n";
    cout << "  Time    : " << fixed << setprecision(3) << qsMs << " ms\n";
    cout << "  Big-O   : O(n log n) average  |  O(n^2) worst case\n";
    printMemory("vector in-place", qsArr.size(), STR_SIZE, 0);
    saveToFile(qsArr, "../sorted_quicksort.txt");
    cout << "\n";

    cout << "-----------------------------------------\n"
         << "  2. HeapSort\n"
         << "-----------------------------------------\n";

    vector<string> hsArr = original;

    auto t3 = high_resolution_clock::now();
    heapSort(hsArr);
    auto t4 = high_resolution_clock::now();

    hsMs = duration_cast<microseconds>(t4 - t3).count() / 1000.0;
    cout << "  Sorted  : " << (isSorted(hsArr) ? "YES v" : "NO x") << "\n";
    cout << "  Time    : " << fixed << setprecision(3) << hsMs << " ms\n";
    cout << "  Big-O   : O(n log n) always (best / average / worst)\n";
    printMemory("binary heap in-place", hsArr.size(), STR_SIZE, 0);
    saveToFile(hsArr, "../sorted_heapsort.txt");
    cout << "\n";

    cout << "-----------------------------------------\n"
         << "  3. AVL Tree\n"
         << "-----------------------------------------\n";

    AVLNode* root = nullptr;
    vector<string> avlResult;
    avlResult.reserve(original.size());

    auto t5 = high_resolution_clock::now();
    for (const string& w : original)
        root = avlInsert(root, w);
    inorder(root, avlResult);
    auto t6 = high_resolution_clock::now();

    avlMs = duration_cast<microseconds>(t6 - t5).count() / 1000.0;
    cout << "  Sorted  : " << (isSorted(avlResult) ? "YES v" : "NO x") << "\n";
    cout << "  Time    : " << fixed << setprecision(3) << avlMs << " ms\n";
    cout << "  Big-O   : O(n log n) insertion  +  O(n) traversal\n";
    printMemory("AVL nodes + result vector",
                avlResult.size(), sizeof(AVLNode),
                avlResult.size() * STR_SIZE);
    saveToFile(avlResult, "../sorted_avl.txt");
    cout << "\n";
    deleteTree(root);

    cout << "=========================================\n"
         << "  COMPARATIVE ANALYSIS\n"
         << "=========================================\n";

    cout << left
         << setw(12) << "Algorithm"
         << setw(12) << "Time(ms)"
         << setw(34) << "Big-O"
         << "In-place\n";
    cout << string(70, '-') << "\n";
    cout << setw(12) << "QuickSort"
         << setw(12) << fixed << setprecision(2) << qsMs
         << setw(34) << "O(n log n) avg / O(n^2) worst" << "Yes\n";
    cout << setw(12) << "HeapSort"
         << setw(12) << hsMs
         << setw(34) << "O(n log n) always"             << "Yes\n";
    cout << setw(12) << "AVL Tree"
         << setw(12) << avlMs
         << setw(34) << "O(n log n) + O(n) traversal"   << "No\n";
    cout << "\n";

    double best = qsMs;
    string winner = "QuickSort";
    if (hsMs  < best) { best = hsMs;  winner = "HeapSort"; }
    if (avlMs < best) { best = avlMs; winner = "AVL Tree"; }
    cout << "  Fastest : " << winner << "  (" << fixed << setprecision(2) << best << " ms)\n\n";

    return 0;
}