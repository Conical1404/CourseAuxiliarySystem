#include "Basic.h"

template<class T>
bool Less<T>::operator() (const T &lhs, const T &rhs) const {
    return lhs < rhs;
}

template<class T>
bool Greater<T>::operator() (const T &lhs, const T &rhs) const {
    return lhs > rhs;
}

template<class T>
bool LessEqual<T>::operator() (const T &lhs, const T &rhs) const {
    return lhs <= rhs;
}

template<class T>
bool GreaterEqual<T>::operator() (const T &lhs, const T &rhs) const {
    return lhs >= rhs;
}

template<class T>
void Basic::swapElement(T *x, T *y) {
    T t = *x;
    *x = *y; *y = t;
}

template<class T>
void Basic::sort(T *a, int len) {
    int i, j;
    T mid = a[(len - 1) / 2];
    i = 0;
    j = len - 1;
    do {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j) {
            swapElement(&a[i], &a[j]);
            i++; j--;
        }
    } while (i <= j);
    if (i < len - 1)
        sort(a + i, len - i);
    if (j > 0)
        sort(a, j + 1);
}

template<class T>
T Basic::getMax(T x, T y) {
    if (x > y) return x;
    return y;
}


Time::Time(int d, int h, int w = 1) : week(w), day(d), hour(h) {  }

Time::Time() {
    week = 0;
    day = 0;
    hour = 0;
}
Time::Time(int hor) {  // 允许直接输入小时，自动转化为 Time 类型
    week = hor / (24 * 7) + 1;
    hor = hor % (24 * 7);
    day = hor / 24 + 1;
    hour = hor % 24;
}

int Time::calHours() {
    return ((week - 1) * 7 + day - 1) * 24 + hour;
}

bool Time::operator==(const Time& other) const {
    return week == other.week && day == other.day && hour == other.hour;
}

void Time::operator = (const Time& other) {
    week = other.week;
    day = other.day;
    hour = other.hour;
}

void Time::operator = (const int h) {
    int hor = h;
    week = hor / (24 * 7) + 1;
    hor = hor % (24 * 7);
    day = hor / 24 + 1;
    hour = hor % 24;
}

bool Time::operator < (const Time& other) const {
    if (week != other.week) return week < other.week;
    return day == other.day ? hour < other.hour : day < other.day;
}

bool Time::operator > (const Time& other) const {
    if (week != other.week) return week > other.week;
    return day == other.day ? hour > other.hour : day > other.day;
}
