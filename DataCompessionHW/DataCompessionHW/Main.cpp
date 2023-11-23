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
//A function for creating a string containing random elements
string data_generation(int size) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    //for (int i = 0; i < size; ++i) {
    //    Data.push_back(characters[rand() % characters.size()]);
   // }
    static std::mt19937 gen(std::random_device{}());

    std::string randomString;
    randomString.reserve(size);

    for (int i = 0; i < size; ++i) {
        randomString.push_back(characters[gen() % characters.size()]);
    }
    return randomString;
}
//A function for reading data from a file and writing this data to a string
string data_reading(string fileName) {
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
//A function for running compression algorithms that accepts the source data and the algorithm
void run(string Method_name, function<string(string)> method, const string& InputData) {
    double start_weight = InputData.size();
    auto start = chrono::system_clock::now();
    string result = method(InputData);
    auto stop = chrono::system_clock::now();
    double final_weight = result.size();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    cout << "Method name: : " << Method_name << endl;
    cout << "Time:" << time << "mcs" << endl;
    cout << "compression ratio: " << start_weight*8 / (final_weight*4) << endl;
    cout << final_weight << endl;
    cout << "Result: " << result << "\n\n" << endl;
}


int main() {
    setlocale(LC_ALL, "RUS");
    int size;
    cout << "Enter the length of the string: " << endl;
    cin >> size;
    string generated_data = data_generation(size);
    //cout << "Input: " << generated_data << endl;
    //run("Huffman method", huffmanCompress, generated_data);
    run("Arifmetic code", arivmetic_code, generated_data);
    //run("Lempel-Ziva_Welcha", KORGIN_LZW, generated_data);
    //run("Shennon-fano", return_answer, generated_data);

    //cout << KORGIN_LZW_Decode(KORGIN_LZW(generated_data)) << endl;;
    /*run("Timurincky method", example_func, generated_data);
    cout << "Enter the name of the data file: " << endl;
    cin >> fileName;
    string file_data = data_reading(fileName);
    std::istringstream iss(result);  // Создаем поток из строки
    std::string element;
    int count = 0;
    while (iss >> element) {
        count++;
    }
    cout << "compression ratio:---------------------- " << start_weight / count << endl;
    */
    return 0;
}