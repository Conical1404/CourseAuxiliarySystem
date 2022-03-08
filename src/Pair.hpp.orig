
#pragma once
#include <stdlib.h>

using namespace std;

template <class T1, class T2>
class Pair{
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v): key(k), value(v) {};
    T1 first();
    T2 second();
    void operator = ( Pair<T1,T2> & p);
};

template <class T1, class T2>
T1 Pair<T1,T2> :: first(){
     return key;
}

template <class T1, class T2>
T2 Pair<T1,T2> :: second(){
    return value;
}

template <class T1, class T2>
void Pair<T1,T2> :: operator = ( Pair<T1,T2> & p) {
    key=p.key;
    value=p.value;
}