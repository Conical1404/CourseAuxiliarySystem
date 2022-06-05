#pragma once
#include <stdlib.h>

template<class T>
class Array {
 private:
    T *data;
    int maxN;
 public:
    Array();
    explicit Array(int n);
    Array(const Array &other);
    Array(int n, T x);
    ~Array();
    T& operator[](const int &index) const;
    Array<T>& operator = (const Array &other);
    int getSize();
};

typedef Array<unsigned char> ByteArray;
