#pragma once
#include <map>
#include <unordered_map>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	char symbol;
	double frequency;
	vector<bool> code;
	Node* left;
	Node* right;

	Node(char s, double f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
};

void FreeMemory(Node* root) {
	if (root == nullptr) {
		return;
	}
	FreeMemory(root->left);
	FreeMemory(root->right);
	delete root;
}

char TakeKey(const unordered_map<char, string>& decoder, const string& binary) {
	for (const auto& pair : decoder) {
		if (pair.second == binary) {
			return pair.first;
		}
	}
	return '\0'; // В случае отсутствия значения
}

bool CheckValue(unordered_map<char, string> decoder, string binary) {
	for (auto pair : decoder) {
		if (pair.second == binary) {
			return true;
		}
	}
	return false;
}

// Декодируем бинарную строку опять же с помощью словаря
string DecodeBinary(const unordered_map<char, string>& data, const string answerString) {
	string decodering, check;
	for (int r = 0; r < answerString.length(); r++) {
		check += answerString[r];
		if (CheckValue(data, check)) {
			decodering += TakeKey(data, check);
			check.erase();
		}
	}
	return decodering;
}

bool sort_by_frequency(const pair<char, double> a, const pair<char, double> b) {
	return a.second < b.second;
}

vector <pair<char, double>> frequency_of_chars(const map<char, int> chars, int length) {
	vector <pair<char, double>> values;
	for (auto value : chars) {
		values.push_back(make_pair(value.first, static_cast<double>(value.second) / length));
	}
	sort(values.begin(), values.end(), sort_by_frequency);
	return values;
}

string boolVectorToString(const vector<bool>& boolVector) {
	string result;
	for (bool bit : boolVector) {
		result += bit ? '1' : '0';
	}
	return result;
}

void Shannon_Fano_recursive(vector<pair<char, double>>& vec, int l, int r, Node* root, vector<bool>& code, unordered_map<char, string>& data) {
	if (l >= r) {
		root->symbol = vec[l].first;
		root->frequency = vec[l].second;
		root->code = code;
		string convertation = boolVectorToString(code);
		data.insert({ root->symbol, convertation });
		return;
	}
	double sum_left = 0.0;
	double sum_right = 1.0;
	int mid = l;
	int r1 = r;
	while (sum_right >= sum_left && r >= mid) {
		sum_left += vec[mid].second;
		sum_right -= vec[r].second;
		++mid;
		--r;
	}
	vector<pair<char, double>> leftValues(vec.begin(), vec.begin() + mid);
	vector<pair<char, double>> rightValues(vec.begin() + mid, vec.begin() + r1 + 1);

	root->left = new Node('\0', 0.0);
	root->right = new Node('\0', 0.0);

	vector<bool> leftCode = code;
	leftCode.push_back(true);
	vector<bool> rightCode = code;
	rightCode.push_back(false);

	Shannon_Fano_recursive(leftValues, 0, leftValues.size() - 1, root->left, leftCode, data);
	Shannon_Fano_recursive(rightValues, 0, rightValues.size() - 1, root->right, rightCode, data);
}


string return_answer(string compressor_string)
{
	map<char, int> chars;
	for (char i : compressor_string) {
		if (chars.find(i) != chars.end()) {
			chars[i]++;
		}
		else {
			chars[i] = 1;
		}
	}
	int length = compressor_string.length();
	vector <pair<char, double>> values = frequency_of_chars(chars, length);
	Node* root = new Node('\n', 1.0);
	// создаём словарь, чтобы хранить там символы и бинарные строки к ним
	unordered_map<char, string> data;
	vector<bool> initialCode;
	Shannon_Fano_recursive(values, 0, values.size() - 1, root, initialCode, data);
	// Используем словарь для воспроизведения результата 
	string answerString;
	for (char letter : compressor_string) {
		answerString += data[letter];
	}
	FreeMemory(root);
	//Если хотите декодировать
	//string decodering = DecodeBinary(data, answerString);
	return answerString;
}