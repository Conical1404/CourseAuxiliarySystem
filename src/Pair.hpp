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
    bool operator == (const Pair<T1, T2> &other) const;
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

template <class T1, class T2>
bool Pair<T1, T2> :: operator == (const Pair<T1, T2> &other) const {
    return first == other.first && second == other.second;
}

typedef Pair<int, int> IntPair;

template <class T1, class T2>
class Spair {
 public:
    T1 first;
    T2 second;
    Spair() { }
    Spair(T1 k, T2 v): first(k), second(v) { }
    void operator = (const Spair<T1, T2> &other);
    bool operator < (const Spair<T1, T2> &other) const;
    bool operator > (const Spair<T1, T2> &other) const;
    bool operator == (const Spair<T1, T2> &other) const;
};

template <class T1, class T2>
void Spair<T1, T2> :: operator = (const Spair<T1, T2> &other) {
    first = other.first;
    second = other.second;
}

template <class T1, class T2>
bool Spair<T1, T2> :: operator < (const Spair<T1, T2> &other) const {
    return first < other.first;
}

template <class T1, class T2>
bool Spair<T1, T2> :: operator > (const Spair<T1, T2> &other) const {
    return first > other.first;
}

template <class T1, class T2>
bool Spair<T1, T2> :: operator == (const Spair<T1, T2> &other) const {
    return first == other.first;
}

typedef Spair<int, int> IntSpair;
