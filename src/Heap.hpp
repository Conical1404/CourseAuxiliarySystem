#pragma once
#include <stdlib.h>
#include "Vector.hpp"

template <class T>
class Heap {
 private:
    Vector<T> data;
    int size;

    void swap(int x, int y) {
        T t = data[x];
        data[x] = data[y];
        data[y] = t;
    }

 public:
    Heap() {
        size = 0;
        data.pushBack(*(new T));
    }

    void push(T x) {
        size++;
        data.pushBack(x);
        int i = size;
        while (i > 1 && data[i] > data[i>>1]) {
            swap(i, i >> 1);
            i = i >> 1;
        }
    }

    T top() {
        return data[1];
    }

    bool isEmpty() {
        if (size == 0) return 1;
        return 0;
    }

    int getSize() {
        return size;
    }

    void pop() {
        if (size == 0) return;
        data[1] = data[size];
        size--;
        int i = 1, j;
        if ((i << 1) > size) return;
        if (((i << 1) | 1) > size || data[i << 1] > data[(i << 1) | 1])
            j = i << 1;
        else
            j = (i << 1) | 1;
        while (j <= size && data[i] < data[j]) {
            swap(i, j);
            i = j;
            if ((i << 1) > size) return;
            if (((i << 1) | 1) > size || data[i << 1] > data[(i << 1) | 1])
                j = i << 1, printf("?%d\n", (i << 1) | 1 > size);
            else
                j = (i << 1) | 1;
        }
    }
};
