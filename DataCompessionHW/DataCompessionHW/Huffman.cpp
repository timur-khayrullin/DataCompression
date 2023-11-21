#include "huffman.h"
#include <queue>
#include <unordered_map>

using namespace std;

// Comparison function for priority_queue
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(const string& data) {
    // Count the frequency of each character
    unordered_map<char, size_t> freqMap;
    for (char ch : data) {
        freqMap[ch]++;
    }

    // Create a priority queue to store the Huffman nodes
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Create a leaf node for each character and add it to the priority queue
    for (const auto& entry : freqMap) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Function to generate Huffman codes
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to compress data using Huffman coding
string huffmanCompress(const string& input) {
    HuffmanNode* root = buildHuffmanTree(input);

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    string compressedData;
    for (char ch : input) {
        compressedData += huffmanCodes[ch];
    }

    return compressedData;
}

// Function to decompress data using Huffman coding
string huffmanDecompress(const string& input, HuffmanNode* root) {
    string decompressedData;
    HuffmanNode* current = root;

    for (char bit : input) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decompressedData += current->data;
            current = root;
        }
    }

    return decompressedData;
}
