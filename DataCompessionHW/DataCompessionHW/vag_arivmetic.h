#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

struct gran_symbol {
    long double low;
    long double high;
    int value;
};

map<char, int> slovar(string str) {
    map<char, int> ans;
    for (char symbol : str) ans[symbol]++;
    return ans;
}

string arivmetic_code(string unarciv) {
    map<char, int> countsymbol = slovar(unarciv);
    map<char, int> indexsymbol;
    long double lenght = 0;
    for (auto item : countsymbol) {
        indexsymbol[item.first] = indexsymbol.size();
        lenght += item.second;
    }
    long double loww = 0;
    vector<gran_symbol> symbolinfo;
    //находим границы для каждого символа
    for (auto symvol : countsymbol) {
        gran_symbol gran_symvol;
        gran_symvol.high = (loww + symvol.second / lenght);
        gran_symvol.low = loww;
        loww = gran_symvol.high;
        gran_symvol.value = symvol.second;
        symbolinfo.push_back(gran_symvol);
    }
    long double low = 0;
    long double high = 1;
    long double range = high - low;
    string ans = "";
    //находим нижнюю и верхнюю границу искомого значения
    for (char symbol : unarciv) {
        range = high - low;
        if (low + (range * symbolinfo[indexsymbol[symbol]].high) == low + (range * symbolinfo[indexsymbol[symbol]].low)) {
            low = low * pow(10, 308);
            ans += to_string(low).substr(0, 100);
            string lows = to_string(low);
            lows.erase(lows.find(','), 7);
            lows = lows.substr(100);
            low = 0;
            for (int i = 0; i < lows.size(); i++) low += (lows[i] - '0') / pow(10, i + 1);
        }
        high = low + (range * symbolinfo[indexsymbol[symbol]].high);
        low = low + (range * symbolinfo[indexsymbol[symbol]].low);
    }
    ans += to_string(low * pow(10, 100));
    ans.erase(ans.find(','), 7);
    high = high * pow(10, 100);
    for (int i = ans.size() - 100; i < ans.size(); i++) {
        if (ans[i] != to_string(high)[i - ans.size() + 100]) {
            int p = ans[i] - '0';
            ans[i] = char(p + 1) + 48;
            ans.erase(i + 1, ans.size() - i + 1);
            break;
        }
    }
    return "0." + ans;
}


string decompress_arivmetic_code(map<char, int> symbol, string nach) {
    long double counts = 0;
    for (auto sym : symbol) counts += sym.second;
    map<int, char>indexsymbol;
    long double nachi = stold(nach);
    for (auto item : symbol) indexsymbol[indexsymbol.size()] = item.first;
    long double loww = 0;
    vector<gran_symbol> symbolinfo;
    //перебираем словарь для определения пределов
    for (auto symvol : symbol) {
        gran_symbol gran_symvol;
        gran_symvol.high = (loww + symvol.second / counts);
        gran_symvol.low = loww;
        loww = gran_symvol.high;
        gran_symvol.value = symvol.second;
        symbolinfo.push_back(gran_symvol);
    }
    string ans = "";
    vector<gran_symbol> sinfo = symbolinfo;
    //находим исходную строку
    for (int i = 0; i < counts; i++) {
        int k = 0;
        while (!(sinfo[k].low <= nachi && nachi < sinfo[k].high)) {
            k++;
        }
        ans += indexsymbol[k];
        long double loww = sinfo[k].low;
        long double range = sinfo[k].high - sinfo[k].low;
        for (int j = 0; j < sinfo.size(); j++) {
            sinfo[j].high = loww + symbol[indexsymbol[j]] * range / counts;
            sinfo[j].low = loww;
            loww = sinfo[j].high;
        }
    }
    return ans;
}
