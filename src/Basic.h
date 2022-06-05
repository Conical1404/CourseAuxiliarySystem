#pragma once
#include <stdlib.h>

template<class T>
struct Less {
    bool operator() (const T &lhs, const T &rhs) const;
};

template<class T>
struct Greater {
    bool operator() (const T &lhs, const T &rhs) const;
};

template<class T>
struct LessEqual {
    bool operator() (const T &lhs, const T &rhs) const;
};

template<class T>
struct GreaterEqual {
    bool operator() (const T &lhs, const T &rhs) const;
};

namespace Basic {
    template<class T>
    void swapElement(T *x, T *y);

    template<class T>
    void sort(T *a, int len);

    template<class T>
    T getMax(T x, T y);
}  // namespace Basic

struct Time {
    int week, day, hour;
    Time(int d, int h, int w = 1);
    Time();
    explicit Time(int hor);
    int calHours();
    bool operator==(const Time& other) const;
    void operator = (const Time& other);
    void operator = (const int h);
    bool operator < (const Time& other) const;
    bool operator > (const Time& other) const;
};
