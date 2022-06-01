// #include <bits/stdc++.h>
// #include "Calendar.hpp"
#include "String.hpp"
#include "Vector.hpp"

int main() {
    String a, b;
    a = "12";
    b = "123";
    printf("%s\n", a.data());
    printf("%s\n", b.data());
    if (a < b)
        printf("%s\n", a.data());
    else
        printf("%s\n", b.data());
    a = b;
    printf("%s\n", a.data());
    a = a + b;
    printf("%s\n", a.data());
    Vector <String> A;
    A.pushBack(a);
    A.pushBack(b);
    printf("%s\n", A[0].data());
    printf("%s\n", A[1].data());
    return 0;
}
