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

typedef Pair<int, int> IntPair;
