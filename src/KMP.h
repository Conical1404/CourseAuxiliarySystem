#pragma once
#include "String.h"
#include "Vector.h"

class KMP{
 private:
    char* s;
    char* t;
    int lens, lent;
    bool exist;
    Vector<int> next;
    Vector<int> ans;
    void solve();

 public:
    KMP(String ss, String tt);
    ~KMP();
    bool isExist();
    Vector<int> getPos();
};
