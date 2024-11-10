#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <cctype>
#include "Bitmap.cpp"
#include "BinTree.cpp"
using namespace std;

// 位图类 Bitmap（如前所述）

class HuffCode {
public:
    unordered_map<char, Bitmap> huffmanCodes;  // 字符与其 Huffman 编码的映射
    unordered_map<char, int> frequencies;      // 字符的频率

public:
    // 获取 Huffman 编码映射
    unordered_map<char, Bitmap> getHuffmanCodes() const {
        return huffmanCodes;
    }

    // 获取某个字符的 Huffman 编码
    Bitmap getHuffmanCode(char ch) const {
        auto it = huffmanCodes.find(ch);
        if (it != huffmanCodes.end()) {
            return it->second;
        }
        return Bitmap(0);  // 默认返回空的位图
    }

    // 设置某个字符的 Huffman 编码
    void setHuffmanCode(char ch, const Bitmap& code) {
        huffmanCodes[ch] = code;
    }

    // 设置某个字符的频率
    void setFrequency(char ch, int freq) {
        frequencies[ch] = freq;
    }

    // 输出所有的 Huffman 编码并附带频率信息
    void display() const {
        for (const auto& entry : huffmanCodes) {
            // 输出字符的 Huffman 编码和频率
            cout << "字母" << entry.first 
                 << " 的哈夫曼编码是 " << entry.second.bits2string(entry.second.size())
                 << " 它出现的次数是 " << frequencies.at(entry.first) << endl;
        }
    }
};

struct HuffNode {
    char ch;              // 字符
    int freq;             // 频率
    HuffNode* left;       // 左子节点
    HuffNode* right;      // 右子节点

    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // 以频率为依据的优先级比较函数
    bool operator>(const HuffNode& other) const {
        return freq > other.freq;
    }
};

void generateHuffmanCodes(HuffNode* node, const string& code, HuffCode& huffCode);

void buildHuffmanTree(const string& text, HuffCode& huffCode, unordered_map<char, int>& freqMap) {
    // 统计字符频率，只考虑字母字符
    for (char ch : text) {
        if (isalpha(ch)) {  // 只统计字母
            ch = tolower(ch);  // 将字母转换为小写
            freqMap[ch]++;
        }
    }

    // 创建优先队列（最小堆），用于构建 Huffman 树
    priority_queue<HuffNode, vector<HuffNode>, greater<HuffNode>> minHeap;

    // 将所有字符和它们的频率插入优先队列
    for (const auto& entry : freqMap) {
        minHeap.push(HuffNode(entry.first, entry.second));
        huffCode.setFrequency(entry.first, entry.second);  // 设置字符的频率
    }

    // 构建 Huffman 树
    while (minHeap.size() > 1) {
        // 取出频率最小的两个节点
        HuffNode* left = new HuffNode(minHeap.top()); minHeap.pop();
        HuffNode* right = new HuffNode(minHeap.top()); minHeap.pop();

        // 创建新节点，合并两个最小的节点
        HuffNode* parent = new HuffNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // 将新节点插入队列
        minHeap.push(*parent);
    }

    // 最后剩下的节点是 Huffman 树的根节点
    HuffNode* root = new HuffNode(minHeap.top()); minHeap.pop();

    // 递归生成 Huffman 编码
    generateHuffmanCodes(root, "", huffCode);
}

// 递归生成 Huffman 编码
void generateHuffmanCodes(HuffNode* node, const string& code, HuffCode& huffCode) {
    if (!node) return;

    if (node->ch != '\0') {  // 叶子节点
        Bitmap bitmap;
        bitmap.fromBinaryString(code);  // 将编码字符串转换为位图
        huffCode.setHuffmanCode(node->ch, bitmap);
    }

    // 递归生成左子树和右子树的编码
    generateHuffmanCodes(node->left, code + "0", huffCode);
    generateHuffmanCodes(node->right, code + "1", huffCode);
}

// 编码函数
string encode(const string& text, const HuffCode& huffCode) {
    string encodedStr;
    for (char ch : text) {
        Bitmap code = huffCode.getHuffmanCode(ch);
        encodedStr += code.bits2string(code.size());
    }
    return encodedStr;
}

// 解码函数
string decode(const string& encodedStr, HuffNode* root) {
    string decodedStr;
    HuffNode* currentNode = root;
    
    for (char bit : encodedStr) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else if (bit == '1') {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {  // 叶子节点
            decodedStr += currentNode->ch;
            currentNode = root;  // 返回到根节点
        }
    }

    return decodedStr;
}

int main() {
    // 从文件中读取文本
    ifstream inputFile("i have a dream.txt");  // 假设文件名为 input.txt
    if (!inputFile) {
        cerr << "无法打开文件!" << endl;
        return 1;
    }

    string text;
    string line;

    // 读取文件内容
    while (getline(inputFile, line)) {
        text += line + " ";  // 将每一行加到 text 中
    }

    inputFile.close();  // 关闭文件

    // 将文本转换为小写，并仅保留字母
    for (char& c : text) {
        c = tolower(c);  // 将所有字母转为小写
    }

    // 创建 Huffman 编码对象
    HuffCode huffCode;

    // 用于存储字符的词频
    unordered_map<char, int> freqMap;

    // 根据文本构建 Huffman 编码树
    buildHuffmanTree(text, huffCode, freqMap);

    // 输出所有字符的 Huffman 编码并附带频率
    cout << "以下是每个字母的哈夫曼编码和出现次数" << endl;
    huffCode.display();

    // 对 "dream" 和 "people" 进行编码
    string word1 = "dream";
    string word2 = "people";

    string encodedDream = encode(word1, huffCode);
    string encodedPeople = encode(word2, huffCode);

    cout << "\ndream的哈夫曼编码是 " << encodedDream << endl;
    cout << "people的哈夫曼编码是 " << encodedPeople << endl;

    return 0;
}

