#pragma once
#include <stdlib.h>

template<class T>
struct Less {
    bool operator() (const T &lhs, const T &rhs) const {
        return lhs < rhs;
    }
};

template<class T>
struct Greater {
    bool operator() (const T &lhs, const T &rhs) const {
        return lhs > rhs;
    }
};

template<class T>
struct LessEqual {
    bool operator() (const T &lhs, const T &rhs) const {
        return lhs <= rhs;
    }
};

template<class T>
struct GreaterEqual {
    bool operator() (const T &lhs, const T &rhs) const {
        return lhs >= rhs;
    }
};

namespace Basic {
    template<class T>
    void swapElement(T *x, T *y) {
        T t = *x;
        *x = *y; *y = t;
    }

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
}  // namespace Basic
