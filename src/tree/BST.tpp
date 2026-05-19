#include "tree/BST.h"
#include <algorithm>
#include <queue>
#include <stdexcept>

// === Big Three + copy helper ==============================================

template <typename T>
BST<T>::BST()
    : root(nullptr), sz(0) {}

template <typename T>
BST<T>::BST(const BST& other)
    : sz(other.sz)
{
    root = copy(other.root);
}

template <typename T>
BSTNode<T>* BST<T>::copy(BSTNode<T>* node) {
    if (node == nullptr)
        return nullptr;

    BSTNode<T>* newNode = new BSTNode<T>(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
}

template <typename T>
BST<T>& BST<T>::operator=(const BST& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
        sz = other.sz;
    }
    return *this;
}

template <typename T>
BST<T>::~BST() {
    clear(root);
}

// === Insert ===============================================================

template <typename T>
void BST<T>::insert(const T& value) {
    root = insert(root, value);
    ++sz;
}

template <typename T>
BSTNode<T>* BST<T>::insert(BSTNode<T>* node, const T& value) {
    if (node == nullptr)
        return new BSTNode<T>(value);

    if (node->data > value)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    return node;
}

// === Contains =============================================================

template <typename T>
bool BST<T>::contains(const T& value) const {
    return contains(root, value);
}

template <typename T>
bool BST<T>::contains(BSTNode<T>* node, const T& value) const {
    if (node == nullptr) return false;
    if (node->data == value) return true;

    if (value < node->data)
        return contains(node->left, value);

    return contains(node->right, value);
}

// === Remove ===============================================================

template <typename T>
void BST<T>::remove(const T& value) {
    root = remove(root, value);
}

template <typename T>
BSTNode<T>* BST<T>::remove(BSTNode<T>* node, const T& value) {
    if (node == nullptr)
        return nullptr;

    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        if (node->left == nullptr) {
            BSTNode<T>* temp = node->right;
            delete node;
            --sz;
            return temp;
        }

        if (node->right == nullptr) {
            BSTNode<T>* temp = node->left;
            delete node;
            --sz;
            return temp;
        }

        BSTNode<T>* successor = minNode(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }

    return node;
}

// === Min / Max ============================================================

template <typename T>
const T& BST<T>::min() const {
    if (sz == 0)
        throw std::runtime_error("BST::min(): tree is empty");

    return minNode(root)->data;
}

template <typename T>
BSTNode<T>* BST<T>::minNode(BSTNode<T>* node) const {
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr)
        return node;

    return minNode(node->left);
}

template <typename T>
const T& BST<T>::max() const {
    if (sz == 0)
        throw std::runtime_error("BST::max(): tree is empty");

    return maxNode(root)->data;
}

template <typename T>
BSTNode<T>* BST<T>::maxNode(BSTNode<T>* node) const {
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr)
        return node;

    return maxNode(node->right);
}

// === Height ===============================================================

template <typename T>
int BST<T>::height() const {
    return height(root);
}

template <typename T>
int BST<T>::height(BSTNode<T>* node) const {
    if (node == nullptr) return 0;

    return std::max(height(node->left), height(node->right)) + 1;
}

// === Size / Empty =========================================================

template <typename T>
int BST<T>::size() const {
    return sz;
}

template <typename T>
bool BST<T>::empty() const {
    return sz == 0;
}

// === Clear ================================================================

template <typename T>
void BST<T>::clear() {
    clear(root);
    root = nullptr;
    sz = 0;
}

template <typename T>
void BST<T>::clear(BSTNode<T>* node) {
    if (node == nullptr) return;

    clear(node->left);
    clear(node->right);

    delete node;
}

// === Traversals ===========================================================

template <typename T>
void BST<T>::inorder(void (*visit)(const T&)) const {
    inorder(root, visit);
}

template <typename T>
void BST<T>::inorder(BSTNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    inorder(node->left, visit);
    visit(node->data);
    inorder(node->right, visit);
}

template <typename T>
void BST<T>::preorder(void (*visit)(const T&)) const {
    preorder(root, visit);
}

template <typename T>
void BST<T>::preorder(BSTNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    visit(node->data);
    preorder(node->left, visit);
    preorder(node->right, visit);
}

template <typename T>
void BST<T>::postorder(void (*visit)(const T&)) const {
    postorder(root, visit);
}

template <typename T>
void BST<T>::postorder(BSTNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    postorder(node->left, visit);
    postorder(node->right, visit);
    visit(node->data);
}

// === BFS (Level-Order) ====================================================

template <typename T>
void BST<T>::bfs(void (*visit)(const T&)) const {
    if (root == nullptr) return;

    std::queue<BSTNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        BSTNode<T>* cur = q.front();
        q.pop();

        visit(cur->data);

        if (cur->left != nullptr)
            q.push(cur->left);

        if (cur->right != nullptr)
            q.push(cur->right);
    }
}
