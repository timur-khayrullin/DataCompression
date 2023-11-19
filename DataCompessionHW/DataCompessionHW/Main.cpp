#include <iostream>
#include <string>
#include <random>

using namespace std;

string data_geberation(int size) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string randomString;
    for (int i = 0; i < size; ++i) {
        randomString.push_back(characters[rand() % characters.size()]);
    }
    return randomString;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int size;
    cout << "Введите длину строки: " << endl;
    cin >> size;
    string generated_data = data_geberation(size);
    cout << "Получившаяся строка: " << generated_data << endl;
    return 0;
}