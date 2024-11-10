#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <cctype>
#include "Bitmap.cpp"
#include "BinTree.cpp"
using namespace std;

// λͼ�� Bitmap����ǰ������

class HuffCode {
public:
    unordered_map<char, Bitmap> huffmanCodes;  // �ַ����� Huffman �����ӳ��
    unordered_map<char, int> frequencies;      // �ַ���Ƶ��

public:
    // ��ȡ Huffman ����ӳ��
    unordered_map<char, Bitmap> getHuffmanCodes() const {
        return huffmanCodes;
    }

    // ��ȡĳ���ַ��� Huffman ����
    Bitmap getHuffmanCode(char ch) const {
        auto it = huffmanCodes.find(ch);
        if (it != huffmanCodes.end()) {
            return it->second;
        }
        return Bitmap(0);  // Ĭ�Ϸ��ؿյ�λͼ
    }

    // ����ĳ���ַ��� Huffman ����
    void setHuffmanCode(char ch, const Bitmap& code) {
        huffmanCodes[ch] = code;
    }

    // ����ĳ���ַ���Ƶ��
    void setFrequency(char ch, int freq) {
        frequencies[ch] = freq;
    }

    // ������е� Huffman ���벢����Ƶ����Ϣ
    void display() const {
        for (const auto& entry : huffmanCodes) {
            // ����ַ��� Huffman �����Ƶ��
            cout << "��ĸ" << entry.first 
                 << " �Ĺ����������� " << entry.second.bits2string(entry.second.size())
                 << " �����ֵĴ����� " << frequencies.at(entry.first) << endl;
        }
    }
};

struct HuffNode {
    char ch;              // �ַ�
    int freq;             // Ƶ��
    HuffNode* left;       // ���ӽڵ�
    HuffNode* right;      // ���ӽڵ�

    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // ��Ƶ��Ϊ���ݵ����ȼ��ȽϺ���
    bool operator>(const HuffNode& other) const {
        return freq > other.freq;
    }
};

void generateHuffmanCodes(HuffNode* node, const string& code, HuffCode& huffCode);

void buildHuffmanTree(const string& text, HuffCode& huffCode, unordered_map<char, int>& freqMap) {
    // ͳ���ַ�Ƶ�ʣ�ֻ������ĸ�ַ�
    for (char ch : text) {
        if (isalpha(ch)) {  // ֻͳ����ĸ
            ch = tolower(ch);  // ����ĸת��ΪСд
            freqMap[ch]++;
        }
    }

    // �������ȶ��У���С�ѣ������ڹ��� Huffman ��
    priority_queue<HuffNode, vector<HuffNode>, greater<HuffNode>> minHeap;

    // �������ַ������ǵ�Ƶ�ʲ������ȶ���
    for (const auto& entry : freqMap) {
        minHeap.push(HuffNode(entry.first, entry.second));
        huffCode.setFrequency(entry.first, entry.second);  // �����ַ���Ƶ��
    }

    // ���� Huffman ��
    while (minHeap.size() > 1) {
        // ȡ��Ƶ����С�������ڵ�
        HuffNode* left = new HuffNode(minHeap.top()); minHeap.pop();
        HuffNode* right = new HuffNode(minHeap.top()); minHeap.pop();

        // �����½ڵ㣬�ϲ�������С�Ľڵ�
        HuffNode* parent = new HuffNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // ���½ڵ�������
        minHeap.push(*parent);
    }

    // ���ʣ�µĽڵ��� Huffman ���ĸ��ڵ�
    HuffNode* root = new HuffNode(minHeap.top()); minHeap.pop();

    // �ݹ����� Huffman ����
    generateHuffmanCodes(root, "", huffCode);
}

// �ݹ����� Huffman ����
void generateHuffmanCodes(HuffNode* node, const string& code, HuffCode& huffCode) {
    if (!node) return;

    if (node->ch != '\0') {  // Ҷ�ӽڵ�
        Bitmap bitmap;
        bitmap.fromBinaryString(code);  // �������ַ���ת��Ϊλͼ
        huffCode.setHuffmanCode(node->ch, bitmap);
    }

    // �ݹ��������������������ı���
    generateHuffmanCodes(node->left, code + "0", huffCode);
    generateHuffmanCodes(node->right, code + "1", huffCode);
}

// ���뺯��
string encode(const string& text, const HuffCode& huffCode) {
    string encodedStr;
    for (char ch : text) {
        Bitmap code = huffCode.getHuffmanCode(ch);
        encodedStr += code.bits2string(code.size());
    }
    return encodedStr;
}

// ���뺯��
string decode(const string& encodedStr, HuffNode* root) {
    string decodedStr;
    HuffNode* currentNode = root;
    
    for (char bit : encodedStr) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else if (bit == '1') {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {  // Ҷ�ӽڵ�
            decodedStr += currentNode->ch;
            currentNode = root;  // ���ص����ڵ�
        }
    }

    return decodedStr;
}

int main() {
    // ���ļ��ж�ȡ�ı�
    ifstream inputFile("i have a dream.txt");  // �����ļ���Ϊ input.txt
    if (!inputFile) {
        cerr << "�޷����ļ�!" << endl;
        return 1;
    }

    string text;
    string line;

    // ��ȡ�ļ�����
    while (getline(inputFile, line)) {
        text += line + " ";  // ��ÿһ�мӵ� text ��
    }

    inputFile.close();  // �ر��ļ�

    // ���ı�ת��ΪСд������������ĸ
    for (char& c : text) {
        c = tolower(c);  // ��������ĸתΪСд
    }

    // ���� Huffman �������
    HuffCode huffCode;

    // ���ڴ洢�ַ��Ĵ�Ƶ
    unordered_map<char, int> freqMap;

    // �����ı����� Huffman ������
    buildHuffmanTree(text, huffCode, freqMap);

    // ��������ַ��� Huffman ���벢����Ƶ��
    cout << "������ÿ����ĸ�Ĺ���������ͳ��ִ���" << endl;
    huffCode.display();

    // �� "dream" �� "people" ���б���
    string word1 = "dream";
    string word2 = "people";

    string encodedDream = encode(word1, huffCode);
    string encodedPeople = encode(word2, huffCode);

    cout << "\ndream�Ĺ����������� " << encodedDream << endl;
    cout << "people�Ĺ����������� " << encodedPeople << endl;

    return 0;
}

