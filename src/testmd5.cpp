#include <stdio.h>
#include <string.h>
#include "MD5.hpp"
#include "Array.hpp"
#include "Vector.hpp"

int main() {
    char s[233];
    scanf("%s", s);
    int n = strlen(s);
    ByteVector S;
    for (int i = 0; i < n; i++)
        S.pushBack(s[i]);
    ByteArray T = MD5 :: calculateMD5Code(S);
    for (int i = 0; i < T.getSize(); i++)
        printf("%.2X", T[i]);
    return 0;
}
