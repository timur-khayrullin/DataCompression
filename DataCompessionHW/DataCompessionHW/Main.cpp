#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <functional>
#include <chrono>
#include "Huffman.h"
#include "Korgin_LZW.h"
#include "vag_arivmetic.h"
#include "Shennon-Fano.h"
#include <sstream>

using namespace std;
template <typename T>
T InputValue(T min, T max) {
    T x;
    while (!(cin >> x) || x > max || x < min) {
        cout << "Try again:" << endl;
        cerr << x << std::endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return x;
}

struct compress_output {
    string name_method;
    float time;
    string result;
    float ratio;
    string decoded_str;

};

//A function for creating a string containing random elements
string data_generation() {
    int size;
    cout << "Enter the length of the string: " << endl;
    cin >> size;
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::mt19937 gen(std::random_device{}());

    std::string randomString;
    randomString.reserve(size);

    for (int i = 0; i < size; ++i) {
        randomString.push_back(characters[gen() % characters.size()]);
    }
    return randomString;
}

//A function for reading data from a file and writing this data to a string
string data_reading() {
    string fileName;
    cout << "Enter the name of the data file: " << endl;
    cin >> fileName;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return  " ";
    }
    string Data;
    getline(file, Data,'\0');
    return Data;
}

//An example function instead of a compression algorithm
string example_func(string InputData) {
    cout << "I am working that is input:" << InputData << endl;
    return InputData;
}

//A function for calculate a ratio for LZW
float compession_ratio_LZW(double& start, string result) {
    istringstream iss(result);
    std::string element;
    int count = 0;
    while (iss >> element) {
        count++;
    }
    return  (start / count);
}

//A function for calculate a ratio for Shennon-Fano and Huffman
float compression_ratio_binary(double& start, double& final) {
    return (start * 8 / (final));
}

//A function for running compression algorithms that accepts the source data, name and the algorithm
void run(string Method_name, function<string(string)> method, const string& InputData, int ratio, compress_output& data) {
    double start_weight = InputData.size();
    auto start = chrono::system_clock::now();
    string result = method(InputData);
    auto stop = chrono::system_clock::now();
    double final_weight = result.size();
    float time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    data.name_method = Method_name;
    data.time = time;
    data.ratio = (ratio == 1 ? compression_ratio_binary(start_weight, final_weight) : compession_ratio_LZW(start_weight,result));
    data.result = result;
}
void cout_compress_data(compress_output& data) {
    cout << "Method name: " << data.name_method << endl;
    cout << "Time: " << data.time << "mcs" << endl;
    cout << "Compression ratio: " << data.ratio << endl;
    //cout << "Result: " << data.result << endl;
}


int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Create a random string or to read from file?" << endl;
    string generated_data = InputValue(1, 2) == 1 ? data_generation() : data_reading();
    cout << "Input string: " << generated_data << "\n" << endl;
    //Huffman method
    compress_output data_Huffman;
    run("Huffman method", huffmanCompress, generated_data,1, data_Huffman);
    cout_compress_data(data_Huffman);
    HuffmanNode* huffmanTree = buildHuffmanTree(generated_data);
    data_Huffman.decoded_str = huffmanDecompress(data_Huffman.result, huffmanTree);
    cout << "Decompressed Huffman data: " << data_Huffman.decoded_str << "\n\n\n" << endl;
    //Lempel-Ziva_welcha
    compress_output data_LZW;
    run("Lempel-Ziva-Welcha", KORGIN_LZW, generated_data,0, data_LZW);
    cout_compress_data(data_LZW);
    data_LZW.decoded_str = KORGIN_LZW_Decode(data_LZW.result);
    cout << "Decompressed LZW data: " << data_LZW.decoded_str << "\n\n\n" << endl;
    //Shennon-Fano
    compress_output data_Shennon_Fano;
    run("Shennon-fano", return_answer, generated_data,1, data_Shennon_Fano);
    cout_compress_data(data_Shennon_Fano);
    data_Shennon_Fano.decoded_str = DecodeString(generated_data);
    cout << "Decompressed Shennon-Fano data: " << data_Shennon_Fano.decoded_str << "\n\n" << endl;
    //Arifmetic code
    //compress_output data_arifmetic;
    //run("Arifmetic code", arivmetic_code, generated_data, 1, data_arifmetic);
    //cout_compress_data(data_arifmetic);
    //data_arifmetic.decoded_str = decompress_arivmetic_code(slovar(generated_data), arivmetic_code(generated_data));
    //cout << "Decompressed arifmetic data: " << data_arifmetic.decoded_str << "\n\n\n" << endl;
    return 0;
}