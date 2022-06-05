#pragma once

#include <stdlib.h>
#include <cstdio>

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
    void debug();
    String& operator = (const String &other);
    String& operator = (char *str);
    String operator + (const String &other);
    bool operator < (const String &other) const;
    bool operator == (const String &other) const;
    bool operator > (const String &other) const;
};
