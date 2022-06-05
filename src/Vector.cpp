#include "Vector.h"

template<class T>
void Vector<T>::reNew(int newLength) {
    T *newData = reinterpret_cast<T *>(malloc(newLength * sizeof(T)));
    memset(newData, 0, newLength * sizeof(T));
    for (int i = 0; i < size; i++) newData[i] = data[i];
    free(data);
    data = newData;
    maxLength = newLength;
}

template<class T>
Vector<T>::Vector() {  // 已测试
    data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
    memset(data, 0, 64 * sizeof(T));
    maxLength = 64;
    size = 0;
}

template<class T>
Vector<T>::Vector(int n) {  // 已测试
    data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
    memset(data, 0, 64 * sizeof(T));
    maxLength = 64;
    size = 0;
    for (int index = 1; index <= n; index++) pushBack(*(new T));
}

template<class T>
Vector<T>::Vector(int n, T x) {  // 已测试
    data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
    memset(data, 0, 64 * sizeof(T));
    maxLength = 64;
    size = 0;
    for (int index = 1; index <= n; index++) pushBack(x);
}

template<class T>
Vector<T>::Vector(const Vector<T> &other) {  // 已测试
    data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
    memset(data, 0, 64 * sizeof(T));
    maxLength = 64;
    size = 0;
    for (int index = 0; index < other.getSize(); index++)
        pushBack(other[index]);
}

template<class T>
Vector<T>::~Vector() {
    if (data)
        free(data);
    data = NULL;
}

template<class T>
int Vector<T>::getSize() const {
    return size;
}

template<class T>
void Vector<T>::pushBack(T e) {  // 已测试
    if (size == maxLength) reNew(maxLength << 1);
    data[size++] = e;
}

template<class T>
void Vector<T>::popBack() {  // 已测试
    if (size == 0) return;
    size--;
}

template<class T>
bool Vector<T>::isEmpty() const {  // 已测试
    if (size == 0) return 1;
    return 0;
}

template<class T>
T& Vector<T>::operator[](const int &index) const {
    return data[index];
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> other) {  // 已测试
    free(data);
    data = reinterpret_cast<T *>(malloc(64 * sizeof(T)));
    memset(data, 0, 64 * sizeof(T));
    maxLength = 64;
    size = 0;
    for (int index = 0; index < other.getSize(); index++)
        pushBack(other[index]);
    return *this;
}

template<class T>
Vector<T> Vector<T>::operator+(Vector<T> other) {   // 已测试
    Vector<T> ans = *this;
    for (int index = 0; index < other.getSize(); index++)
        ans.pushBack(other[index]);
    return ans;
}

template<class T>
void Vector<T>::reverse() {  // 已测试
    for (int index = 0; index * 2 < size; index++) {
        Basic ::swapElement(&data[index], &data[size - index - 1]);
    }
}

