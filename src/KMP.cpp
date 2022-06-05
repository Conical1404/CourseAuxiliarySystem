#include "KMP.h"

void KMP::solve() {
    int j = 0;
    for (int i = 1; i <= lens; i++) {
        while (j && s[i - 1] != t[j]) j = next[j];
        if (j < lent && s[i - 1] == t[j]) j++;
        if (j == lent) {
            ans.pushBack(i - lent);
            j = next[j];
            exist = 1;
        }
    }
}

KMP::KMP(String ss, String tt)  {  // 用 t 匹配 s
    s = ss.data();
    t = tt.data();
    lens = ss.getSize();
    lent = tt.getSize();
    int j = 0;
    next.pushBack(0);
    for (int i = 1; i <= lent; i++) next.pushBack(0);
    for (int i = 2; i <= lent; i++) {
        while ( j && t[j] != t[i-1]) j = next[j];
        if (t[j] == t[i-1]) j++;
        next[i] = j;
    }
    exist = 0;
    solve();
}

KMP::~KMP() { }

bool KMP::isExist()  {
    return exist;
}

Vector<int> KMP::getPos()  {
    return ans;
}
