#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

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
		gran_symvol.high = (loww/pow(10,16) + symvol.second / lenght)*pow(10,16);
		gran_symvol.low = loww;
		loww = gran_symvol.high;
		gran_symvol.value = symvol.second;
		symbolinfo.push_back(gran_symvol);
	}
	long double low = 0;
	long double high = 1*pow(10,16);
	long double range = high - low;
	//находим нижнюю и верхнюю границу искомого значения
	for (char symbol : unarciv) {
		range = high - low;
		high = low + (range/pow(10,16) * symbolinfo[indexsymbol[symbol]].high);
		low = low + (range/pow(10, 16) * symbolinfo[indexsymbol[symbol]].low);
	}
	//оптимизация кода
	string ans = to_string(low * pow(10, 32));
	high = high * pow(10, 32);
	for (int i = 0; i < ans.size(); i++) {
		if (ans[i] != to_string(high)[i]) {
			int p = ans[i] - '0';
			ans[i] = char(p + 1) + 48;
			ans.erase(i + 1, ans.size() - i + 1);
			break;
		}
	}
	if (ans.find('.') != string::npos) ans.erase(ans.find('.'), 1);
	return "0."+ans;
}