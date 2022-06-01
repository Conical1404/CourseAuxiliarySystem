#pragma once
#include <stdlib.h>
#include <cstring>

#include "Basic.hpp"

// 已经完成测试
template <class T>
class Vector {
 private:
    T *data;
    int maxLength;
    int size;
    void reNew(int newLength) {
        T *newData = reinterpret_cast<T *>(malloc(newLength * sizeof(T)));
        memset(newData, 0, sizeof(newData));
        for (int i = 0; i < size; i++) newData[i] = data[i];
        free(data);
        data = newData;
        maxLength = newLength;
    }

 public:
    Vector() {  // 已测试
        data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
        memset(data, 0, 64 * sizeof(T));
        maxLength = 64;
        size = 0;
    }
    explicit Vector(int n) {  // 已测试
        data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
        memset(data, 0, 64 * sizeof(T));
        maxLength = 64;
        size = 0;
        for (int index = 1; index <= n; index++) pushBack(*(new T));
    }
    Vector(int n, T x) {  // 已测试
        data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
        memset(data, 0, 64 * sizeof(T));
        maxLength = 64;
        size = 0;
        for (int index = 1; index <= n; index++) pushBack(x);
    }
    Vector(const Vector<T> &other) {  // 已测试
        data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
        memset(data, 0, 64 * sizeof(T));
        maxLength = 64;
        size = 0;
        for (int index = 0; index < other.getSize(); index++)
            pushBack(other[index]);
    }
    ~Vector() {
        free(data);
        data = NULL;
    }
    int getSize() const { return size; }  // 已测试
    void pushBack(T e) {  // 已测试
        if (size == maxLength) reNew(maxLength << 1);
        data[size++] = e;
    }
    void popBack() {  // 已测试
        if (size == 0) return;
        size--;
    }
    bool isEmpty() const {  // 已测试
        if (size == 0) return 1;
        return 0;
    }
    T &operator[](const int &index) const { return data[index]; }  // 已测试
    Vector<T> &operator=(Vector<T> other) {  // 已测试
        free(data);
        data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
        memset(data, 0, 64 * sizeof(T));
        maxLength = 64;
        size = 0;
        for (int index = 0; index < other.getSize(); index++)
            pushBack(other[index]);
        return *this;
    }
    Vector<T> operator+(Vector<T> other) {   // 已测试
        Vector<T> ans = *this;
        for (int index = 0; index < other.getSize(); index++)
            ans.pushBack(other[index]);
        return ans;
    }
    void reverse() {  // 已测试
        for (int index = 0; index * 2 < size; index++) {
            Basic ::swapElement(&data[index], &data[size - index - 1]);
        }
    }
};

typedef Vector<unsigned char> ByteVector;
