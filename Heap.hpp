#pragma once
#include <stdlib.h>
#include <utility>
#include "Vector.hpp"

template <class T>
class Heap {
 private:
    Vector<T> data;
    int size;

 public:
    Heap() {
        size = 0;
        data.pushBack(*(new T));
    }

    void push(T x) {
        size++;
        data.pushBack(x);
        int i = size;
        while (i > 1 && data[i] > data[i >> 1]) {
            swap(data[i], data[i >> 1]);
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
            swap(data[i], data[j]);
            i = j;
            if ((i << 1) > size) return;
            if (((i << 1) | 1) > size || data[i << 1] > data[(i << 1) | 1])
                j = i << 1, fprintf(stderr, "?%d\n", (i << 1) | 1 > size);
            else
                j = (i << 1) | 1;
        }
    }
};
