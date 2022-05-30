#include <bits/stdc++.h>
#include "Calendar.hpp"
#include "String.hpp"
#include "Vector.hpp"

// using namespace std;

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
    return 0;
}
