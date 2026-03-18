#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct AVLNode {
    std::string key;
    AVLNode* left;
    AVLNode* right;
    int height;
    explicit AVLNode(const std::string& k)
        : key(k), left(nullptr), right(nullptr), height(1) {}
};

inline int avlHeight(AVLNode* n)     { return n ? n->height : 0; }
inline int balanceFactor(AVLNode* n) { return n ? avlHeight(n->left) - avlHeight(n->right) : 0; }
inline void updateHeight(AVLNode* n) {
    if (n) n->height = 1 + std::max(avlHeight(n->left), avlHeight(n->right));
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    y->left  = x->right;
    x->right = y;
    updateHeight(y); updateHeight(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left  = x;
    updateHeight(x); updateHeight(y);
    return y;
}


AVLNode* avlInsert(AVLNode* node, const std::string& key) {
    if (!node) return new AVLNode(key);
    if      (key < node->key) node->left  = avlInsert(node->left,  key);
    else if (key > node->key) node->right = avlInsert(node->right, key);
    else return node; 

    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf >  1 && key < node->left->key)  return rotateRight(node);          
    if (bf < -1 && key > node->right->key) return rotateLeft(node);           
    if (bf >  1 && key > node->left->key)  { node->left  = rotateLeft(node->left);  return rotateRight(node); } 
    if (bf < -1 && key < node->right->key) { node->right = rotateRight(node->right); return rotateLeft(node); } 
    return node;
}


void inorder(AVLNode* node, std::vector<std::string>& result) {
    if (!node) return;
    inorder(node->left,  result);
    result.push_back(node->key);
    inorder(node->right, result);
}

void deleteTree(AVLNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
