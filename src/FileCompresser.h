#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Heap.h"
#include "Pair.h"
#include "Vector.h"

class TreeNode {
 public:
    unsigned char c;
    int weight;
    TreeNode* left;
    TreeNode* right;
    TreeNode();
    explicit TreeNode(int);
    TreeNode(unsigned char, int);
    ~TreeNode();
};

struct NodeCompare {
    bool operator()(TreeNode* lhs, TreeNode* rhs) const {
        return lhs->weight > rhs->weight;
    }
};

class HuffmanTree {
 private:
    int64_t totalBits;
    int frequency[256];
    TreeNode* root;
    Heap<TreeNode*, NodeCompare> priQueue;
    std::string charCode[256];
    void inorder(TreeNode*, std::string);
    Vector<unsigned char> encode(const Vector<unsigned char>&);
    Vector<unsigned char> decode(const Vector<unsigned char>&);
    void bulidTree(int[], int);
    int64_t getTotalBits() const;
    void clear();

 public:
    HuffmanTree();
    ~HuffmanTree();
    void upload(const std::string, const std::string);
    void download(const std::string, const std::string, const std::string);
};
