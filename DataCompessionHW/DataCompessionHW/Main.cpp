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
void compession_ratio_LZW(double& start, string result) {
    istringstream iss(result);
    std::string element;
    int count = 0;
    while (iss >> element) {
        count++;
    }
    cout << "compression ratio:" << start / count << "\n\n" << endl;
}

//A function for calculate a ratio for Shennon-Fano and Huffman
void compression_ratio_binary(double& start, double& final) {
    cout << "compression ratio: " << start*8 / (final) << "\n\n" << endl;
}

//A function for running compression algorithms that accepts the source data, name and the algorithm
void run(string Method_name, function<string(string)> method, const string& InputData, int ratio) {
    double start_weight = InputData.size();
    auto start = chrono::system_clock::now();
    string result = method(InputData);
    auto stop = chrono::system_clock::now();
    double final_weight = result.size();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << "Method name: : " << Method_name << endl;
    cout << "Time:" << time << "mcs" << endl;
    ratio == 1 ? compression_ratio_binary(start_weight, final_weight) : compession_ratio_LZW(start_weight,result);
    //cout << "Result: " << result << "\n\n" << endl;
}


int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Create a random string or to read from file?" << endl;
    string generated_data = InputValue(1, 2) == 1 ? data_generation() : data_reading();
    //cout << generated_data << endl;
    run("Huffman method", huffmanCompress, generated_data,1);
    //run("Arifmetic code", arivmetic_code, generated_data);
    run("Lempel-Ziva_Welcha", KORGIN_LZW, generated_data,0);
    run("Shennon-fano", return_answer, generated_data,1);

    //run("Timurincky method", example_func, generated_data);
    return 0;
}