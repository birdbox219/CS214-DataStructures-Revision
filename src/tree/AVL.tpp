#include "tree/AVL.h"
#include <algorithm>
#include <queue>
#include <stdexcept>

// === Big Three + copy ======================================================

template <typename T>
AVL<T>::AVL()
    : root(nullptr), sz(0) {}

template <typename T>
AVL<T>::AVL(const AVL& other)
    : sz(other.sz)
{
    root = copy(other.root);
}

template <typename T>
AVLNode<T>* AVL<T>::copy(AVLNode<T>* node) {
    if (node == nullptr)
        return nullptr;

    AVLNode<T>* newNode = new AVLNode<T>(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    newNode->height = std::max(getHeight(newNode->left),
                               getHeight(newNode->right)) + 1;
    return newNode;
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
        sz = other.sz;
    }
    return *this;
}

template <typename T>
AVL<T>::~AVL() {
    clear(root);
}

// === Height / Balance ======================================================

template <typename T>
int AVL<T>::getHeight(AVLNode<T>* node) const {
    return node ? node->height : 0;
}

template <typename T>
int AVL<T>::getBalance(AVLNode<T>* node) const {
    return getHeight(node->left) - getHeight(node->right);
}

// === Rotations =============================================================

template <typename T>
AVLNode<T>* AVL<T>::rotateRight(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

template <typename T>
AVLNode<T>* AVL<T>::rotateLeft(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// === Rebalance =============================================================

template <typename T>
AVLNode<T>* AVL<T>::rebalance(AVLNode<T>* node) {
    if (node == nullptr)
        return nullptr;

    node->height = std::max(getHeight(node->left),
                            getHeight(node->right)) + 1;

    int balance = getBalance(node);

    // Left-Left
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    // Left-Right
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Right
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    // Right-Left
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// === Insert ================================================================

template <typename T>
void AVL<T>::insert(const T& value) {
    root = insert(root, value);
}

template <typename T>
AVLNode<T>* AVL<T>::insert(AVLNode<T>* node, const T& value) {
    if (node == nullptr) {
        ++sz;
        return new AVLNode<T>(value);
    }

    if (value < node->data)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    return rebalance(node);
}

// === Contains ==============================================================

template <typename T>
bool AVL<T>::contains(const T& value) const {
    return contains(root, value);
}

template <typename T>
bool AVL<T>::contains(AVLNode<T>* node, const T& value) const {
    if (node == nullptr) return false;
    if (node->data == value) return true;

    if (value < node->data)
        return contains(node->left, value);

    return contains(node->right, value);
}

// === Remove ================================================================

template <typename T>
void AVL<T>::remove(const T& value) {
    root = remove(root, value);
}

template <typename T>
AVLNode<T>* AVL<T>::remove(AVLNode<T>* node, const T& value) {
    if (node == nullptr)
        return nullptr;

    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            --sz;
            return nullptr;
        }

        if (node->left == nullptr) {
            AVLNode<T>* temp = node->right;
            delete node;
            --sz;
            return temp;
        }

        if (node->right == nullptr) {
            AVLNode<T>* temp = node->left;
            delete node;
            --sz;
            return temp;
        }

        AVLNode<T>* successor = minNode(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }

    return rebalance(node);
}

// === Min / Max =============================================================

template <typename T>
const T& AVL<T>::min() const {
    if (sz == 0)
        throw std::runtime_error("AVL::min(): tree is empty");

    return minNode(root)->data;
}

template <typename T>
AVLNode<T>* AVL<T>::minNode(AVLNode<T>* node) const {
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr)
        return node;

    return minNode(node->left);
}

template <typename T>
const T& AVL<T>::max() const {
    if (sz == 0)
        throw std::runtime_error("AVL::max(): tree is empty");

    return maxNode(root)->data;
}

template <typename T>
AVLNode<T>* AVL<T>::maxNode(AVLNode<T>* node) const {
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr)
        return node;

    return maxNode(node->right);
}

// === Height (public) =======================================================

template <typename T>
int AVL<T>::height() const {
    return getHeight(root);
}

// === Size / Empty ==========================================================

template <typename T>
int AVL<T>::size() const {
    return sz;
}

template <typename T>
bool AVL<T>::empty() const {
    return sz == 0;
}

// === Clear =================================================================

template <typename T>
void AVL<T>::clear() {
    clear(root);
    root = nullptr;
    sz = 0;
}

template <typename T>
void AVL<T>::clear(AVLNode<T>* node) {
    if (node == nullptr) return;

    clear(node->left);
    clear(node->right);

    delete node;
}

// === Traversals ============================================================

template <typename T>
void AVL<T>::inorder(void (*visit)(const T&)) const {
    inorder(root, visit);
}

template <typename T>
void AVL<T>::inorder(AVLNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    inorder(node->left, visit);
    visit(node->data);
    inorder(node->right, visit);
}

template <typename T>
void AVL<T>::preorder(void (*visit)(const T&)) const {
    preorder(root, visit);
}

template <typename T>
void AVL<T>::preorder(AVLNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    visit(node->data);
    preorder(node->left, visit);
    preorder(node->right, visit);
}

template <typename T>
void AVL<T>::postorder(void (*visit)(const T&)) const {
    postorder(root, visit);
}

template <typename T>
void AVL<T>::postorder(AVLNode<T>* node, void (*visit)(const T&)) const {
    if (node == nullptr) return;

    postorder(node->left, visit);
    postorder(node->right, visit);
    visit(node->data);
}

// === BFS (Level-Order) =====================================================

template <typename T>
void AVL<T>::bfs(void (*visit)(const T&)) const {
    if (root == nullptr) return;

    std::queue<AVLNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        AVLNode<T>* cur = q.front();
        q.pop();

        visit(cur->data);

        if (cur->left != nullptr)
            q.push(cur->left);

        if (cur->right != nullptr)
            q.push(cur->right);
    }
}
