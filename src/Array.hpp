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
