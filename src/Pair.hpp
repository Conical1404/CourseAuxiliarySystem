#pragma once
#include <stdlib.h>

template <class T1, class T2>
class Pair {
 public:
    T1 first;
    T2 second;
    Pair() { }
    Pair(T1 k, T2 v): first(k), second(v) { }
    void operator = (const Pair<T1, T2> &other);
    bool operator < (const Pair<T1, T2> &other) const;
    bool operator > (const Pair<T1, T2> &other) const;
};

template <class T1, class T2>
void Pair<T1, T2> :: operator = (const Pair<T1, T2> &other) {
    first = other.first;
    second = other.second;
}

template <class T1, class T2>
bool Pair<T1, T2> :: operator < (const Pair<T1, T2> &other) const {
    return first == other.first ? second < other.second : first < other.first;
}

template <class T1, class T2>
bool Pair<T1, T2> :: operator > (const Pair<T1, T2> &other) const {
    return first == other.first ? second > other.second : first > other.first;
}
