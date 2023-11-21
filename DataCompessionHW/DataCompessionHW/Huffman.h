#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

struct HuffmanNode {
    char data;
    size_t frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, size_t frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

HuffmanNode* buildHuffmanTree(const std::string& data);
void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes);
std::string huffmanCompress(const std::string& input);
std::string huffmanDecompress(const std::string& input, HuffmanNode* root);

#endif // HUFFMAN_H
