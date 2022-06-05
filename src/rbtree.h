#pragma once

enum RBTColor {RED, BLACK};

template<class T>
struct RBTNode {
    T data;
    RBTColor color;
    RBTNode *parent;
    RBTNode *left, *right;
    RBTNode();
    RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r);
};

template <class T>
struct RBTree {
 private:
    RBTNode<T> *root;
    void leftRotate(RBTNode<T> *x);
    void rightRotate(RBTNode<T> *x);
    void insertFixUp(RBTNode<T> *x);
    void print(RBTNode<T> *x);

 public:
    RBTree();
    ~RBTree();

    void print();
    void insert(T data);
    bool find(T key);
    T search(T key);
};
