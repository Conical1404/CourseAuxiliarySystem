#pragma once
#include "src/basic.h"

template<class T>
void sort(T *a, int len) {
    int i, j;
    T mid = a[(len - 1) / 2];
    i = 0;
    j = len - 1;
    do {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j) {
            swapElement(a[i], a[j]);
            i++; j--;
        }
    } while (i <= j);
    if (i < len - 1)
        sort(a + i, len - i);
    if (j > 0)
        sort(a, j + 1);
}
