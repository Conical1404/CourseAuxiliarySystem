#pragma once
#include <stdlib.h>

class String {
 private:
    struct StringNode {
        char c;
        StringNode* next;
        StringNode();
        explicit StringNode(char x);
        ~StringNode();
    };
    int size;
    StringNode *head, *tail;
 public:
    String();
    explicit String(char* x);
    ~String();
    int getSize();
    void pushBack(char c);
    char* data();
    String& operator = (String other);
    String operator + (String other);
    bool operator < (String other);
};

String :: StringNode :: StringNode() {
    c = 0;
    next = NULL;
}

String :: StringNode :: StringNode(char x) {
    c = x;
    next = NULL;
}

String :: StringNode :: ~StringNode() { }

String :: String() {
    head = new StringNode;
    tail = head;
    size = 0;
}

String :: ~String() {
    auto iter = head;
    while (iter != tail) {
        auto tmp = iter -> next;
        free(iter), iter = tmp;
    }
    free(tail);
    head = tail = NULL;
}

int String :: getSize() {
    return size;
}

void String :: pushBack(char c) {
    tail -> c = c;
    tail -> next = new StringNode;
    tail = tail -> next;
    ++size;
}

char* String :: data() {
    char* str = reinterpret_cast<char*> (malloc(size * sizeof(char)));
    int index = 0;
    for (auto iter = head; iter != tail; iter = iter -> next)
        str[index++] = iter -> c;
    return str;
}

String& String :: operator = (String other) {
    auto iter = head;
    while (iter != tail) {
        auto tmp = iter -> next;
        free(iter), iter = tmp;
    }
    free(tail);
    head = new StringNode;
    tail = head; size = 0;
    char *str = other.data();
    for (int index = 0; index < other.getSize(); index++)
        pushBack(str[index]);
    return *this;
}

String String :: operator + (String other) {
    String ans = *this;
    char *str = other.data();
    for (int index = 0; index < other.getSize(); index++)
        ans.pushBack(str[index]);
    return ans;
}

bool String :: operator < (String other) {
    char* str1 = data();
    char* str2 = other.data();
    int n = size;
    int m = other.getSize();
    for (int index = 0; index < n && index < m; index++)
        if (str1[index] ^ str2[index])
            return str1[index] < str2[index];
    return n < m;
}
