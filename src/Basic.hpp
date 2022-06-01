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

    template<class T>
    T getMax(T x, T y) {
        if (x > y) return x;
        return y;
    }
}  // namespace Basic

struct Time{
    int week, day, hour;
    // Time(int w, int d, int h, int m = 0) :
    // week(w), day(d), hour(h), min(m) {  }
    Time(int d, int h, int w = 1) : week(w), day(d), hour(h) {  }
    Time() {
        week = 0;
        day = 0;
        hour = 0;
    }
    explicit Time(int hor) {  // 允许直接输入小时，自动转化为 Time 类型
        week = hor / (24 * 7) + 1;
        hor = hor % (24 * 7);
        day = hor / 24 + 1;
        hour = hor % 24;
    }
    int calHours() {
        return ((week - 1) * 7 + day - 1) * 24 + hour;
    }
    bool operator==(const Time& other) const {
        return week == other.week && day == other.day && hour == other.hour;
    }
    void operator = (const Time& other) {
        week = other.week;
        day = other.day;
        hour = other.hour;
    }
    void operator = (const int h) {
        int hor = h;
        week = hor / (24 * 7) + 1;
        hor = hor % (24 * 7);
        day = hor / 24 + 1;
        hour = hor % 24;
    }
    bool operator < (const Time& other) const {
        if (week != other.week) return week < other.week;
        return day == other.day ? hour < other.hour : day < other.day;
    }
    bool operator > (const Time& other) const {
        if (week != other.week) return week > other.week;
        return day == other.day ? hour > other.hour : day > other.day;
    }
};
