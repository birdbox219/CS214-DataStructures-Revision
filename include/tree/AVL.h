#pragma once

template <typename T>
struct AVLNode {
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(const T& data, AVLNode<T>* left = nullptr, AVLNode<T>* right = nullptr)
        : data(data), left(left), right(right), height(1) {}
};

template <typename T>
class AVL {
private:
    AVLNode<T>* root;
    int sz;

    int getHeight(AVLNode<T>* node) const;
    int getBalance(AVLNode<T>* node) const;
    AVLNode<T>* rotateRight(AVLNode<T>* y);
    AVLNode<T>* rotateLeft(AVLNode<T>* x);
    AVLNode<T>* rebalance(AVLNode<T>* node);

    AVLNode<T>* insert(AVLNode<T>* node, const T& value);
    bool contains(AVLNode<T>* node, const T& value) const;
    AVLNode<T>* remove(AVLNode<T>* node, const T& value);
    AVLNode<T>* minNode(AVLNode<T>* node) const;
    AVLNode<T>* maxNode(AVLNode<T>* node) const;

    void clear(AVLNode<T>* node);
    AVLNode<T>* copy(AVLNode<T>* node);

    void inorder(AVLNode<T>* node, void (*visit)(const T&)) const;
    void preorder(AVLNode<T>* node, void (*visit)(const T&)) const;
    void postorder(AVLNode<T>* node, void (*visit)(const T&)) const;

public:
    AVL();
    ~AVL();
    AVL(const AVL& other);
    AVL& operator=(const AVL& other);

    void insert(const T& value);
    bool contains(const T& value) const;
    void remove(const T& value);

    const T& min() const;
    const T& max() const;

    int height() const;
    int size() const;
    bool empty() const;
    void clear();

    void inorder(void (*visit)(const T&)) const;
    void preorder(void (*visit)(const T&)) const;
    void postorder(void (*visit)(const T&)) const;
    void bfs(void (*visit)(const T&)) const;
};

#include "tree/AVL.tpp"
