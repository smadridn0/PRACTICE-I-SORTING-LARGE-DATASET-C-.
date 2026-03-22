#pragma once
#include <string>
#include <vector>
#include <algorithm>

// Nodo del árbol AVL
struct AVLNode {
    std::string key;
    AVLNode* left;
    AVLNode* right;
    int height;

    // Inicializa como nodo hoja sin hijos
    explicit AVLNode(const std::string& k)
        : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Altura de un nodo (0 si es nulo)
inline int avlHeight(AVLNode* n)     { return n ? n->height : 0; }

// Factor de balance: altura izquierda menos derecha
inline int balanceFactor(AVLNode* n) { return n ? avlHeight(n->left) - avlHeight(n->right) : 0; }

// Recalcula la altura según los hijos
inline void updateHeight(AVLNode* n) {
    if (n) n->height = 1 + std::max(avlHeight(n->left), avlHeight(n->right));
}

// Rotación simple a la derecha (caso izquierda-izquierda)
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    y->left  = x->right;
    x->right = y;
    updateHeight(y); updateHeight(x);
    return x;
}

// Rotación simple a la izquierda (caso derecha-derecha)
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left  = x;
    updateHeight(x); updateHeight(y);
    return y;
}

// Inserta una clave y rebalancea el árbol si es necesario
AVLNode* avlInsert(AVLNode* node, const std::string& key) {
    if (!node) return new AVLNode(key);

    if      (key < node->key) node->left  = avlInsert(node->left,  key);
    else if (key > node->key) node->right = avlInsert(node->right, key);
    else return node; // Clave duplicada, no se inserta

    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf >  1 && key < node->left->key)  return rotateRight(node);           // Izq-Izq
    if (bf < -1 && key > node->right->key) return rotateLeft(node);            // Der-Der
    if (bf >  1 && key > node->left->key)  { node->left  = rotateLeft(node->left);  return rotateRight(node); } // Izq-Der
    if (bf < -1 && key < node->right->key) { node->right = rotateRight(node->right); return rotateLeft(node); } // Der-Izq

    return node;
}

// Recorrido inorden: llena 'result' con las claves en orden ascendente
void inorder(AVLNode* node, std::vector<std::string>& result) {
    if (!node) return;
    inorder(node->left,  result);
    result.push_back(node->key);
    inorder(node->right, result);
}

// Libera la memoria del árbol en postorden
void deleteTree(AVLNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
