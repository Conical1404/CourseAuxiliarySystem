#pragma once

#include <iostream>
#include "Basic.h"

template <class T>
class AVL {
 private:
    int size;
    class AVLNode {
     public:
        T data;
        int size, deep;
        AVLNode* left;
        AVLNode* right;
        AVLNode();
        explicit AVLNode(T dt);
        AVLNode(int s, int d, T dt);
        AVLNode(int s, int d, T dt, AVLNode* l, AVLNode* r);
        AVLNode(const AVLNode &other);
        ~AVLNode();
        int getSize(AVLNode *x);
        int getDeep(AVLNode *x);
        int getSize();
        int getDeep();
        AVLNode* ls();
        AVLNode* rs();
    };
    AVLNode* root;
    void update(AVLNode *x);
    void leftLeft(AVLNode** u);
    void rightRight(AVLNode** u);
    void leftRight(AVLNode** u);
    void rightLeft(AVLNode** u);

 public:
    AVL();
    ~AVL();
    AVLNode** getRoot();
    void Free(AVLNode** u);
    bool insert(AVLNode** u, T d);
    bool exist(AVLNode* u, T d);
    T search(AVLNode* u, T d);
    bool Delete(AVLNode** u, T d);
    void show_AVL(AVLNode* u);
};
