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
}

struct Time{
    int week, day, hour;
    Time(int w, int d, int h) : week(w), day(d), hour(h) {  }
    Time(){
        week = 0;
        day = 0;
        hour = 0;
    }
};
