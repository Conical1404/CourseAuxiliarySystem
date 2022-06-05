#pragma once
#include <stdlib.h>
#include <cstring>

#include "Basic.h"

// 已经完成测试
template <class T>
class Vector {
 private:
    T *data;
    int maxLength;
    int size;
    void reNew(int newLength);

 public:
    Vector();
    explicit Vector(int n);
    Vector(int n, T x);
    Vector(const Vector<T> &other);
    ~Vector();
    int getSize() const;
    void pushBack(T e);
    void popBack();
    bool isEmpty() const;
    T& operator[](const int &index) const;
    Vector<T>& operator=(Vector<T> other);
    Vector<T> operator+(Vector<T> other);
    void reverse();
};

typedef Vector<unsigned char> ByteVector;
