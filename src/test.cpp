#include <bits/stdc++.h>

#include "rbtree.hpp"

// using namespace std;

RBTree<int> A;

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        A.insert(x);
    }
    A.print();
    for (int op, x; q--; ) {
        cin >> op;
        if (op == 0) {
            cin >> x;
            A.insert(x);
        } else if (op == 1) {
            cin >> x;
            cout << (A.find(x) ? "Yes" : "No") << endl;
        } else {
            cout << "Current Rbtree: ";
            A.print();
            cout << endl;
        }
    }
}
