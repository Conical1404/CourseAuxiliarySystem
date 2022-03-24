#pragma once
#include <stdio.h>
#include <string>
#include <stdint.h>

#include "Heap.hpp"
#include "Pair.hpp"
#include "Vector.hpp"

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

 public:
    HuffmanTree();
    ~HuffmanTree();
    void bulidTree(int[], int);
    Vector<unsigned char> encode(Vector<unsigned char>);
    Vector<unsigned char> decode(Vector<unsigned char>);
    int* getWeight();
    int64_t getTotalBits();
};

TreeNode::TreeNode() : weight(0), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int w) : weight(w), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(unsigned char c, int w)
    : c(c), weight(w), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

HuffmanTree::HuffmanTree() {
    for (int i = 0; i < 255; i++) frequency[i] = 0;
    totalBits = 0;
}
HuffmanTree::~HuffmanTree() { delete root; }

int* HuffmanTree::getWeight() { return frequency; }

int64_t HuffmanTree::getTotalBits() { return totalBits; }

void HuffmanTree::bulidTree(int charWeight[], int n = 256) {
    for (int i = 0; i < 256; i++) {
        if (charWeight[i] > 0) {
            TreeNode* node = new TreeNode((unsigned char)i, charWeight[i]);
            priQueue.push(node);
        }
    }
    while (priQueue.getSize() > 1) {
        TreeNode* minNode1 = priQueue.top();
        priQueue.pop();
        TreeNode* minNode2 = priQueue.top();
        priQueue.pop();
        TreeNode* mergeNode = new TreeNode(minNode1->weight + minNode2->weight);
        mergeNode->left = minNode1;
        mergeNode->right = minNode2;
        priQueue.push(mergeNode);
    }
    root = priQueue.top();
    priQueue.pop();
}

Vector<unsigned char> HuffmanTree::encode(Vector<unsigned char> text) {
    Vector<unsigned char> result;
    int bitCount = 0;
    unsigned char temp = 0;
    std::string emptyString = "";
    for (int i = 0; i < text.getSize(); i++) {
        frequency[text[i]]++;
    }
    bulidTree(frequency);
    inorder(root, emptyString);
    for (int i = 0; i < text.getSize(); i++) {
        std::string temps = charCode[text[i]];
        int length = charCode[text[i]].size();
        for (int j = 0; j < length; j++) {
            if (temps[j] == '0')
                temp = temp << 1;
            else
                temp = temp << 1 | 1;
            ++bitCount;
            ++totalBits;
            if (bitCount == 8) {
                result.pushBack(temp);
                temp = 0;
                bitCount = 0;
            }
        }
    }
    if (bitCount > 0) temp = temp << (8 - bitCount);
    result.pushBack(temp);
    printf("%d\n", totalBits);
    return result;
}

void HuffmanTree::inorder(TreeNode* root, std::string s) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        charCode[root->c] = s;
        return;
    }
    inorder(root->left, s + '0');
    inorder(root->right, s + '1');
    return;
}
Vector<unsigned char> HuffmanTree::decode(Vector<unsigned char> code) {
    Vector<unsigned char> text;
    int count = 7;
    int index = 0;
    TreeNode* cur = root;
    while (index < code.getSize() && totalBits > 0) {
        int bit = (code[index] & (1 << count)) == 0 ? 0 : 1;
        if (count == 0) {
            ++index;
            count = 8;
        }
        if (bit)
            cur = cur->right;
        else
            cur = cur->left;
        if (cur->right == cur->left) {
            text.pushBack(cur->c);
            cur = root;
        }
        --count;
        --totalBits;
    }
    return text;
}
