#pragma once

template <typename T>
struct BSTNode {
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(const T& data, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr)
        : data(data), left(left), right(right) {}
};

template <typename T>
class BST {
private:
    BSTNode<T>* root;
    int sz;

    BSTNode<T>* insert(BSTNode<T>* node, const T& value);
    bool contains(BSTNode<T>* node, const T& value) const;
    BSTNode<T>* remove(BSTNode<T>* node, const T& value);
    BSTNode<T>* minNode(BSTNode<T>* node) const;
    BSTNode<T>* maxNode(BSTNode<T>* node) const;
    int height(BSTNode<T>* node) const;
    void clear(BSTNode<T>* node);
    BSTNode<T>* copy(BSTNode<T>* node);
    void inorder(BSTNode<T>* node, void (*visit)(const T&)) const;
    void preorder(BSTNode<T>* node, void (*visit)(const T&)) const;
    void postorder(BSTNode<T>* node, void (*visit)(const T&)) const;

public:
    BST();
    ~BST();
    BST(const BST& other);
    BST& operator=(const BST& other);

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

#include "tree/BST.tpp"
