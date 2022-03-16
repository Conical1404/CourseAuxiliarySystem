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
    Array(int n, T x);
    ~Array();
    T& operator[](const int &index);
    Array<T>& operator = (Array other);
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
Array<T> :: Array(int n, T x) {
    data = reinterpret_cast<T*> (malloc(n * sizeof(T)));
    maxN = n;
    for (int index = 0; index < n; index++)
        data[index] = x;
}

template<class T>
Array<T> :: ~Array() {
    free(data);
    data = NULL;
}

template<class T>
T& Array<T> :: operator[](const int &index) {
    return data[index];
}

template<class T>
Array<T>& Array<T> :: operator = (Array other) {
    data = reinterpret_cast<T*> (malloc(other.maxN * sizeof(T)));
    maxN = other.maxN;
    for (int index = 0; index < maxN; index++)
        data[index] = other[index];
    return *this;
}
