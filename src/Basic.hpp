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
    T getMax(T x, T y) {
        if (x > y) return x;
        return y;
    }
}  // namespace Basic

struct Time{
    int week, day, hour, min;
    //Time(int w, int d, int h, int m = 0) : week(w), day(d), hour(h), min(m) {  }
    Time(int d, int h, int m, int w = 1) : week(w), day(d), hour(h), min(m) {  }
    Time(){
        week = 0;
        day = 0;
        hour = 0;
        min = 0;
    }
    int calMinutes(){
        return ((day - 1) * 24 + hour) * 60 + min;
    }
};
