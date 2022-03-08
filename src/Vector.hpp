#pragma once
#include <stdlib.h>

template <class T>
class Vector {
 private:
    T *data;
    int MaxLength;
    int size;
    void reNew(int NewLength) {
        T *NewData = reinterpret_cast<T*> (malloc (NewLength * sizeof(T)));
        for (int i = 0; i < size; i++)
            NewData[i] = data[i];
        free(data);
        data = NewData;
        MaxLength = NewLength;
    }

 public:
    Vector() {
        data = reinterpret_cast<T*> (malloc( 64 * sizeof(T)));
        MaxLength = 64;
        size = 0;
    }
    ~Vector() {
        free(data);
    }
    int getSize() {
        return size;
    }
    void pushBack(T e) {
        if (size == MaxLength) reNew( MaxLength << 1);
        data[size++] = e;
    }
    bool isEmpty() {
        if (size == 0) return 1;
        return 0;
    }
    T &operator[](int i) {
        return data[i];
    }
};
