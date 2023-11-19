#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

string data_geberation(int size) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string Data;
    for (int i = 0; i < size; ++i) {
        Data.push_back(characters[rand() % characters.size()]);
    }
    return Data;
}

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

int main() {
    setlocale(LC_ALL, "RUS");
    int size;
    cout << "Enter the length of the string: " << endl;
    //cin >> size;
    //string generated_data = data_geberation(size);
    //cout << "The resulting string: " << generated_data << endl;

    string fileName;
    cout << "¬ведите название файла с данными" << endl;
    cin >> fileName;
    string file_data = data_reading(fileName);
    cout << "The resulting string: " << file_data << endl;
    return 0;
}