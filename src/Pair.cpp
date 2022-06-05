#include "Pair.h"

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
