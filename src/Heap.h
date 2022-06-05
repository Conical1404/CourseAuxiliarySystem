#pragma once

#include <stdlib.h>
#include "Basic.h"
#include "Vector.h"

template <class T, typename F = Less<T> >
class Heap {
 private:
    Vector<T> data;
    int size;
    void swap(int x, int y);

 public:
    Heap() ;
    void push(T x);
    T top() const;
    bool isEmpty() const;
    int getSize() const;
    void pop();
};
