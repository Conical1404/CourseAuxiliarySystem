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

template<class T>
Array<T> :: Array() {
    data = NULL;
}

template<class T>
Array<T> :: Array(int n) {
    data = reinterpret_cast<T*> (malloc(n * sizeof(T)));
    maxN = n;
}

template<class T>
int Array<T> :: getSize() {
    return maxN;
}

template<class T>
Array<T> :: Array(int n, T x) {
    data = reinterpret_cast<T*> (malloc(n * sizeof(T)));
    maxN = n;
    for (int index = 0; index < n; index++)
        data[index] = x;
}

template<class T>
Array<T> :: ~Array() {  // 析构时有一个可疑的卡顿，怀疑出问题了
// 但是没有发现实际影响，不排除纯粹运行慢
    free(data);
    data = NULL;
    // printf("!");
}

template<class T>
T& Array<T> :: operator[](const int &index) const {
    return data[index];
}

template<class T>
Array<T>& Array<T> :: operator = (const Array &other) {
    T *newData = reinterpret_cast<T*> (malloc(other.maxN * sizeof(T)));
    maxN = other.maxN;
    for (int index = 0; index < maxN; index++)
        newData[index] = other[index];
    data = newData;
    return *this;
}

template<class T>
Array<T>::Array(const Array &other) {
    T *newData = reinterpret_cast<T*> (malloc(other.maxN * sizeof(T)));
    maxN = other.maxN;
    for (int index = 0; index < maxN; index++)
        newData[index] = other[index];
    data = newData;
}

typedef Array<unsigned char> ByteArray;
