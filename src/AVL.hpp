#pragma once

#include <iostream>
#include "Basic.h"

template <class T>
class AVL{
 private:
    int size;
    class AVLNode{
     public:
        T data;
        int size, deep;
        AVLNode* left;
        AVLNode* right;
        AVLNode() {
            size = 1;
            deep = 1;
            left = NULL;
            right = NULL;
        }
        explicit AVLNode(T dt) {
            data = dt;
            size = 1;
            deep = 1;
            left = NULL;
            right = NULL;
        }
        AVLNode(int s, int d, T dt) {
            size = s;
            deep = d;
            data = dt;
            left = NULL;
            right = NULL;
        }
        AVLNode(int s, int d, T dt, AVLNode* l, AVLNode* r) {
            size = s;
            deep = d;
            data = dt;
            left = l;
            right = r;
        }
        AVLNode(const AVLNode &other) {
            size = other.size;
            deep = other.deep;
            data = other.data;
            left = other.left;
            right = other.right;
        }
        ~AVLNode() {
            free(left);
            left = NULL;
            free(right);
            right = NULL;
        }
        int getSize(AVLNode *x) {
            if (x == NULL) return 0;
            return x->size;
        }
        int getDeep(AVLNode *x) {
            if (x == NULL) return 0;
            return x -> deep;
        }
        int getSize() {  // 注意这个重载不能判空指针
            return size;
        }
        int getDeep() {  // 注意这个重载不能判空指针
            return deep;
        }
        AVLNode* ls() {
            return left;
        }
        AVLNode* rs() {
            return right;
        }
    };
    AVLNode* root;
    void update(AVLNode *x) {
        if (x == NULL) return;
        x->size = x->getSize(x->left) + x->getSize(x->right) + 1;
        x->deep = Basic :: getMax<int>(x->getDeep(x->left),
                                        x->getDeep(x->right)) + 1;
    }
    void leftLeft(AVLNode** u) {
        AVLNode* v = (*u) -> left;
        (*u) -> left = v -> right;
        v -> right = *u;
        update(*u);
        update(v);
        *u = v;
    }
    void rightRight(AVLNode** u) {
        AVLNode* v = (*u) -> right;
        (*u) -> right = v -> left;
        v -> left = *u;
        update(*u);
        update(v);
        *u = v;
    }
    void leftRight(AVLNode** u) {
        rightRight(&((*u) -> left));
        leftLeft(u);
    }
    void rightLeft(AVLNode** u) {
        leftLeft(&((*u) -> right));
        rightRight(u);
    }

 public:
    AVL() {
        size = 0;
        root = NULL;
    }
    AVLNode** getRoot() {
        return &root;
    }
    void Free(AVLNode** u) {
        if (*u == NULL) return;
        Free(&((*u)->left));
        Free(&((*u)->right));
        free(*u);
        *u = NULL;
    }
    ~AVL() {
        Free(&root);
    }
    bool insert(AVLNode** u, T d) {
        // 调用时直接 insert(AVLname.getroot(), data) 即可
        if (*u == NULL) {
            *u = new AVLNode(d);
            return 0;
        }
        if (d == (*u)->data) return 1;  // 出现重复
        if (d < (*u)->data) {
            bool f = insert(&((*u)->left), d);
            if (f) return 1;
            update(*u);
            if ((*u)->getDeep((*u)->left) - (*u)->getDeep((*u)->right) == 2) {
                if (d < (*u)->left->data) leftLeft(u);
                else
                    leftRight(u);
            }
        } else {
            bool f = insert(&((*u)->right), d);
            if (f) return 1;
            update(*u);
            if ((*u)->getDeep((*u)->right) - (*u)->getDeep((*u)->left) == 2) {
                if (d < (*u)->right->data) rightLeft(u);
                else
                    rightRight(u);
            }
        }
        update(*u);
        return 0;
    }
    bool exist(AVLNode* u, T d) {
        if (u == NULL) {
            return 0;
        }
        if (d == u->data) return 1;
        if (d < u->data) {
            bool f = exist(u->left, d);
            if (f) return 1;
        } else {
            bool f = exist(u->right, d);
            if (f) return 1;
        }
        return 0;
    }
    T search(AVLNode* u, T d) {
        if (u == NULL) {
            return d;
        }
        if (d == u->data) return u->data;
        if (d < u->data) {
            T f = search(u->left, d);
            return f;
        } else {
            T f = search(u->right, d);
            return f;
        }
        return d;
    }
    bool Delete(AVLNode** u, T d) {
        if (*u == NULL) return 0;
        if (d < (*u)->data) {
            bool f = Delete(&((*u)->left), d);
            if (f == 0) return 0;
            update(*u);
            if ((*u)->getDeep((*u)->right) - (*u)->getDeep((*u)->left) == 2) {
                if ((*u)->getDeep((*u)->right->left) > \
                    (*u)->getDeep((*u)->right->right))
                    rightLeft(u);
                else
                    rightRight(u);
            }
        } else {
            if (d > (*u)->data) {
                bool f = Delete(&((*u)->right), d);
                if (f == 0) return 0;
                update(*u);
                if ((*u)->getDeep((*u)->left) -
                    (*u)->getDeep((*u)->right) == 2) {
                    if ((*u)->getDeep((*u)->left->right) > \
                        (*u)->getDeep((*u)->left->left))
                        leftRight(u);
                    else
                        leftLeft(u);
                }
            } else {
                if ((*u)->left == NULL || (*u)->right == NULL) {
                    if ((*u)->left) {
                        (*u) = (*u)->left;
                        return 1;
                    }
                    if ((*u)->right) {
                        *u = (*u)->right;
                        return 1;
                    }
                    *u = NULL;
                    update(*u);
                    return 1;
                } else {
                    AVLNode* v = (*u)->right;
                    while (v->left) v = v->left;
                    (*u)->data = v->data;
                    Delete(&((*u)->right), v->data);
                    update(*u);
                    if ((*u)->getDeep((*u)->left) -
                        (*u)->getDeep((*u)->right) == 2) {
                        if ((*u)->getDeep((*u)->left->right) > \
                            (*u)->getDeep((*u)->left->left))
                            leftRight(u);
                        else
                            leftLeft(u);
                    }
                }
            }
        }
        update(*u);
        return 1;
    }
    void show_AVL(AVLNode* u) {
        if (u == NULL) return;
        std::cout << u->data << " ";
        if (u->left) show_AVL(u->left);
        if (u->right) show_AVL(u->right);
    }
};
