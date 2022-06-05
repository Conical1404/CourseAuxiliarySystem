#include "Heap.h"

template <class T, typename F>
void Heap<T, F>::swap(int x, int y) {
    Basic :: swapElement(&data[x], &data[y]);
}
template <class T, typename F>
Heap<T, F>::Heap() {
    size = 0;
    data.pushBack(*(new T));
}

template <class T, typename F>
void Heap<T, F>::push(T x) {
    size++;
    data.pushBack(x);
    int i = size;
    while (i > 1 && F()(data[i >> 1], data[i])) {
        swap(i, i >> 1);
        i = i >> 1;
    }
}

template <class T, typename F>
T Heap<T, F>::top() const {
    return data[1];
}

template <class T, typename F>
bool Heap<T, F>::isEmpty() const {
    if (size == 0) return 1;
    return 0;
}

template <class T, typename F>
int Heap<T, F>::getSize() const {
    return size;
}

template <class T, typename F>
void Heap<T, F>::pop() {
    if (size == 0) return;
    data[1] = data[size];
    data.popBack();
    size--;
    int i = 1, j;
    if ((i << 1) > size) return;
    if (((i << 1) | 1) > size || F()(data[(i << 1) | 1], data[i << 1]))
        j = i << 1;
    else
        j = (i << 1) | 1;
    while (j <= size && F()(data[i], data[j])) {
        swap(i, j);
        i = j;
        if ((i << 1) > size) return;
        if (((i << 1) | 1) > size || F()(data[(i << 1) | 1], data[i << 1]))
            j = i << 1;
        else
            j = (i << 1) | 1;
    }
}
