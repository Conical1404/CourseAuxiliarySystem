#include "FileCompresser.h"

TreeNode::TreeNode() : weight(0), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(int w) : weight(w), left(nullptr), right(nullptr) {}

TreeNode::TreeNode(unsigned char c, int w)
    : c(c), weight(w), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

HuffmanTree::HuffmanTree() {
    for (int i = 0; i < 256; i++) frequency[i] = 0;
    totalBits = 0;
}
HuffmanTree::~HuffmanTree() { delete root; }

int64_t HuffmanTree::getTotalBits() const { return totalBits; }

void HuffmanTree::clear() {
    for (int i = 0; i < 256; i++) {
        frequency[i] = 0;
        charCode[i].clear();
    }
    totalBits = 0;
    delete root;
    root = nullptr;
}

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

Vector<unsigned char> HuffmanTree::encode(const Vector<unsigned char>& text) {
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

Vector<unsigned char> HuffmanTree::decode(const Vector<unsigned char>& code) {
    Vector<unsigned char> text;
    int count = 7;
    int index = 0;
    TreeNode* cur = root;
    // printf("%d\n",code.getSize());
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

void HuffmanTree::upload(const std::string dst, const std::string src) {
    // std::locale loc = std::locale::global(std::locale(""));
    Vector<unsigned char> input;
    Vector<unsigned char> output;
    std::string filename;
    char c;
    std::ifstream inFile;
    for (int i = src.size() - 1; i >= 0; i--) {
        if (src[i] != '/') {
            filename += src[i];
        } else {
            break;
        }
    }
    std::reverse(filename.begin(), filename.end());
    inFile.open(src, std::ios::in | std::ios::binary);
    while (inFile.get(c)) {
        input.pushBack(c);
    }
    inFile.close();
    output = encode(input);
    printf("%d\n", output.getSize());
    std::string newFilePath = dst + '/' + filename + ".huffman";
    std::string recordFilePath = dst + '/' + filename + ".txt";
    std::ofstream outFile;
    outFile.open(newFilePath, std::ios::out | std::ios::binary);
    for (int i = 0; i < output.getSize(); i++) {
        outFile.put(output[i]);
    }
    outFile.close();
    outFile.open(recordFilePath, std::ios::out);
    outFile << totalBits << std::endl;
    for (int i = 0; i < 256; i++) {
        if (!charCode[i].empty())
            outFile << i << ' ' << frequency[i] << std::endl;
    }
    clear();
    // std::locale::global(loc);
}

void HuffmanTree::download(const std::string dst, const std::string src,
                           const std::string filename) {
    // std::locale loc = std::locale::global(std::locale(""));
    std::string recordPath = src + '/' + filename + ".txt";
    std::string filePath = src + '/' + filename + ".huffman";
    std::string dstPath = dst + filename;
    std::ifstream inFile;
    Vector<unsigned char> input;
    Vector<unsigned char> output;
    inFile.open(recordPath, std::ios::in);
    inFile >> totalBits;
    int i, f;
    while (inFile >> i >> f) {
        frequency[i] = f;
    }
    inFile.close();
    bulidTree(frequency);
    char c;
    inFile.open(filePath, std::ios::in | std::ios::binary);
    while (inFile.get(c)) {
        input.pushBack(c);
    }
    inFile.close();
    output = decode(input);
    std::ofstream outFile;
    outFile.open(dstPath, std::ios::out | std::ios::binary);
    for (int i = 0; i < output.getSize(); i++) {
        outFile.put(output[i]);
    }
    outFile.close();
    clear();
    // std::locale::global(loc);
}
