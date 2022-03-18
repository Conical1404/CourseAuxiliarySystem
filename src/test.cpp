#include <stdio.h>

#include "FileCompresser.hpp"

int main() {
    Vector<unsigned char> s;
    Vector<unsigned char> w;
    Vector<unsigned char> v;
    for (int i = 1; i < 10; i++) {
        unsigned char c = 'a' + i;
        for (int j = i; j > 0; j--) {
            s.pushBack(c);
        }
    }
    HuffmanTree e;
    w = e.encode(s);
    v = e.decode(w);
    for (int i = 0; i < v.getSize(); i++) printf("%c", v[i]);
    printf("\n");
    for (int i = 0; i < s.getSize(); i++) printf("%c", s[i]);
    printf("\n");
    for (int i = 0; i < w.getSize(); i++) printf("%d ", w[i]);
    return 0;
}
