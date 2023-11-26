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

string arivmetic_code(string unarciv) {
    map<char, int> countsymbol;
    map<char, int> indexsymbol;
    long double lenght = 0;
    //находим количество встречаемых символов
    for (char symbol : unarciv) {
        countsymbol[symbol]++;
        lenght++;
    }
    for (auto item : countsymbol) indexsymbol[item.first] = indexsymbol.size();
    long double loww = 0;
    vector<gran_symbol> symbolinfo;
    //находим границы для каждого символа
    for (auto symvol : countsymbol) {
        gran_symbol gran_symvol;
        gran_symvol.high = (loww + symvol.second / lenght) ;
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
            ans += to_string(low).substr(0,100);
            string lows = to_string(low);
            lows.erase(lows.find(','), 7);
            lows = lows.substr(100);
            low = 0;
            for (int i = 0; i < lows.size(); i++) low += (lows[i] - '0') / pow(10, i + 1);
        }
        high = low + (range * symbolinfo[indexsymbol[symbol]].high);
        low = low + (range * symbolinfo[indexsymbol[symbol]].low);
    }
    ans += to_string(low*pow(10,100));
    ans.erase(ans.find(','), 7);
    high = high * pow(10, 100);
    high = high * pow(10, 100);
    for (int i = ans.size()-100; i < ans.size(); i++) {
        if (ans[i] != to_string(high)[i-ans.size()+100]) {
            int p = ans[i] - '0';
            ans[i] = char(p + 1) + 48;
            ans.erase(i + 1, ans.size() - i + 1);
            break;
        }
    }
    return "0." + ans;
}
