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
};

template<class T>
RBTNode<T>::RBTNode() {
    color = RBTColor::BLACK;
    parent = NULL;
    left = NULL;
    right = NULL;
}

template<class T>
RBTNode<T>::RBTNode(T value, RBTColor c, RBTNode<T> *p,
                    RBTNode<T> *l, RBTNode<T> *r) {
    data = value;
    color = c;
    parent = p;
    left = l;
    right = r;
}

template<class T>
RBTree<T>::RBTree() {
    root = NULL;
}

template<class T>
RBTree<T>::~RBTree() {
}

template<class T>
void RBTree<T>::leftRotate(RBTNode<T> *x) {
    RBTNode<T> *y = x -> right;
    x -> right = y -> left;
    if (y -> left)
        y -> left -> parent = x;
    y -> left = x;
    y -> parent = x -> parent;
    if (x -> parent) {
        if (x -> parent -> left == x)
            x -> parent -> left = y;
        else
            x -> parent -> right = y;
        x -> parent = y;
    } else {
        root = y;
        x -> parent = y;
    }
}

template<class T>
void RBTree<T>::rightRotate(RBTNode<T> *x) {
    RBTNode<T> *y = x -> left;
    x -> left = y -> right;
    if (y -> right)
        y -> right -> parent = x;
    y -> right = x;
    y -> parent = x -> parent;
    if (x -> parent) {
        if (x -> parent -> left == x)
            x -> parent -> left = y;
        else
            x -> parent -> right = y;
        x -> parent = y;
    } else {
        root = y;
        x -> parent = y;
    }
}

template<class T>
bool RBTree<T>::find(T key) {
    RBTNode<T> *u = root;
    while (u) {
        if (key == u -> data)
            return true;
        if (key < u -> data)
            u = u -> left;
        else
            u = u -> right;
    }
    return false;
}

template<class T>
void RBTree<T>::insert(T data) {
    RBTNode<T> *node = NULL;
    if (!(node = new RBTNode<T>(data, RBTColor::BLACK, NULL, NULL, NULL)))
        return;
    RBTNode<T> *v = NULL;
    RBTNode<T> *u = root;
    while (u) {
        v = u;
        if (node -> data < u -> data)
            u = u -> left;
        else
            u = u -> right;
    }
    if (v) {
        node -> parent = v;
        if (node -> data < v -> data)
            v -> left = node;
        else
            v ->  right = node;
    } else {
        node -> parent = v;
        root = node;
    }
    node -> color = RBTColor::RED;
    insertFixUp(node);
}

template<class T>
void RBTree<T>::insertFixUp(RBTNode<T> *node) {
    RBTNode<T> *parent;
    RBTNode<T> *grandParent;
    while ((parent = node -> parent) && parent -> color == RBTColor::RED) {
        grandParent = parent -> parent;
        if (parent == grandParent -> left) {
            RBTNode<T> *uncle = grandParent -> right;
            if (uncle && uncle -> color == RBTColor::RED) {
                uncle -> color = RBTColor::BLACK;
                parent -> color = RBTColor::BLACK;
                grandParent -> color = RBTColor::RED;
                node = grandParent;
                continue;
            }

            if (parent -> right == node) {
                RBTNode<T> *tmp;
                leftRotate(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent -> color = RBTColor::BLACK;
            grandParent -> color = RBTColor::RED;
            rightRotate(grandParent);
        } else {
            RBTNode<T> *uncle = grandParent -> left;
            if (uncle && uncle -> color == RBTColor::RED) {
                uncle -> color = RBTColor::BLACK;
                parent -> color = RBTColor::BLACK;
                grandParent -> color = RBTColor::RED;
                node = grandParent;
                continue;
            }

            if (parent -> left == node) {
                RBTNode<T> *tmp;
                rightRotate(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent -> color = RBTColor::BLACK;
            grandParent -> color = RBTColor::RED;
            leftRotate(grandParent);
        }
    }
    root -> color = RBTColor::BLACK;
}

template<class T>
void RBTree<T>::print(RBTNode<T> *x) {
    if (!x)
        return;
    print(x -> left);
    std::cout << x -> data << ' ';
    print(x -> right);
}

template<class T>
void RBTree<T>::print() {
    print(root);
}
