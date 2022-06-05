#include "DyadicArray.h"

template<class T>
DyadicArray<T> :: DyadicArray() {
    data = NULL;
}

template<class T>
DyadicArray<T> :: DyadicArray(int n, int m) {
    data = reinterpret_cast<T*> (malloc(n * m * sizeof(T)));
    maxN = n, maxM = m;
}

template<class T>
DyadicArray<T> :: DyadicArray(int n, int m, T x) {
    data = reinterpret_cast<T*> (malloc(n * m * sizeof(T)));
    maxN = n, maxM = m;
    for (int index = 0; index < n * m; index++)
        data[index] = x;
}

template<class T>
DyadicArray<T> :: ~DyadicArray() {
    free(data);
    data = NULL;
}

template<class T>
T* DyadicArray<T> :: operator[](const int &index) const {
    return data + index * maxM;
}
