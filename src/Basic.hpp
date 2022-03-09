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
