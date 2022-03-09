#pragma once
#include <stdlib.h>

template <class T>
class Vector {
 private:
    T *data;
    int maxLength;
    int size;
    void reNew(int newLength) {
        T *newData = reinterpret_cast<T*> (malloc(newLength * sizeof(T)));
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        free(data);
        data = newData;
        maxLength = newLength;
    }

 public:
    Vector() {
        data = reinterpret_cast<T*> (malloc(64 * sizeof(T)));
        maxLength = 64;
        size = 0;
    }
    explicit Vector(int n) {
        data = reinterpret_cast<T*> (malloc(64 * sizeof(T)));
        maxLength = 64;
        size = 0;
        for (int index = 1; index <= n; index++)
            pushBack(*(new T));
    }
    Vector(int n, T x) {
        data = reinterpret_cast<T*> (malloc(64 * sizeof(T)));
        maxLength = 64;
        size = 0;
        for (int index = 1; index <= n; index++)
            pushBack(x);
    }
    ~Vector() {
        free(data);
    }
    int getSize() {
        return size;
    }
    void pushBack(T e) {
        if (size == maxLength) reNew(maxLength << 1);
        data[size++] = e;
    }
    void popBack() {
        if (size == 0) return;
        size--;
    }
    bool isEmpty() {
        if (size == 0) return 1;
        return 0;
    }
    T &operator[](int index) {
        return data[index];
    }
};
