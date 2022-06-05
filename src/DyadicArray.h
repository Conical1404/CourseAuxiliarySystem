#pragma once
#include <stdlib.h>

template<class T>
class DyadicArray {
 private:
    T *data;
    int maxN, maxM;
 public:
    DyadicArray();
    DyadicArray(int n, int m);
    DyadicArray(int n, int m, T x);
    ~DyadicArray();
    T* operator[](const int &index) const;
};
