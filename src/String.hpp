#pragma once
#include <stdlib.h>

using namespace std;

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
    String(const String& v);
    ~String();
    int getSize() const;
    void pushBack(char c);
    char* data() const;
    String& operator = (const String &other);
<<<<<<< HEAD
    String operator + (String other);
    bool operator < (String other);
=======
    String& operator = (char *str);
    String operator + (const String &other);
    bool operator < (const String &other);
>>>>>>> 628528162ce61e1964baf79716672df8b539b32f
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

String :: String(const String &v) {
    // head = new StringNode;
    // tail = head;
    // size = 0;
    char *str = v.data();
    head = new StringNode;
    tail = head; size = 0;
    for (int index = 0; index < v.getSize(); index++)
        pushBack(str[index]);
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

int String :: getSize() const {
    return size;
}

void String :: pushBack(char c) {
    tail -> c = c;
    tail -> next = new StringNode;
    tail = tail -> next;
    ++size;
}

char* String :: data() const {
    char* str = reinterpret_cast<char*> (malloc((size + 1) * sizeof(char)));
    int index = 0;
    for (auto iter = head; iter != tail; iter = iter -> next)
        str[index++] = iter -> c;
    str[index] = 0;
    return str;
}

String& String :: operator = (const String &other) {
<<<<<<< HEAD
=======
    char *str = other.data();
>>>>>>> 628528162ce61e1964baf79716672df8b539b32f
    auto iter = head;
    while (iter != tail) {
        auto tmp = iter -> next;
        free(iter), iter = tmp;
    }
    free(tail);
    head = new StringNode;
    tail = head; size = 0;
    for (int index = 0; index < other.getSize(); index++)
        pushBack(str[index]);
    return *this;
}

String& String :: operator = (char *str) {
    auto iter = head;
    while (iter != tail) {
        auto tmp = iter -> next;
        free(iter), iter = tmp;
    }
    free(tail);
    head = new StringNode;
    tail = head; size = 0;
    while ((*str) != 0)
        pushBack(*(str++));
    return *this;
}

String String :: operator + (const String &other) {
    String ans = *this;
    char *str = other.data();
    for (int index = 0; index < other.getSize(); index++)
        ans.pushBack(str[index]);
    return ans;
}

bool String :: operator < (const String &other) {
    char* str1 = data();
    char* str2 = other.data();
    int n = size;
    int m = other.getSize();
    for (int index = 0; index < n && index < m; index++)
        if (str1[index] ^ str2[index])
            return str1[index] < str2[index];
    return n < m;
}
