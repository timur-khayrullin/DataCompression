#pragma once
#include <map>
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

void FreeMemory(Node* root, vector<bool>& answer) {
	if (root == nullptr) {
		return;
	}
	FreeMemory(root->left, answer);
	FreeMemory(root->right, answer);
	answer.insert(answer.end(), root->code.begin(), root->code.end());
	delete root;
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

vector<bool> stringToBoolVector(const std::string& str) {
	std::vector<bool> result;
	for (char c : str) {
		if (c == '0') {
			result.push_back(false);
		}
		else if (c == '1') {
			result.push_back(true);
		}
		else {
			// Handle error - unexpected character in the string
		}
	}
	return result;
}

void Shannon_Fano_recursive(vector<pair<char, double>>& vec, int l, int r, Node* root, vector<bool>& code) {
	if (l >= r) {
		root->symbol = vec[l].first;
		root->frequency = vec[l].second;
		root->code = code;
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
	leftCode.push_back(false);
	vector<bool> rightCode = code;
	rightCode.push_back(true);

	Shannon_Fano_recursive(leftValues, 0, leftValues.size() - 1, root->left, leftCode);
	Shannon_Fano_recursive(rightValues, 0, rightValues.size() - 1, root->right, rightCode);
}


string return_answer(string compressor_string)
{
	map<char, int> chars;
	for (char i : compressor_string) {
		i = tolower(i);
		chars[i]++;
	}
	vector<bool> answer;
	int length = compressor_string.length();
	vector <pair<char, double>> values = frequency_of_chars(chars, length);
	Node* root = new Node('\n', 1.0);
	vector<bool> initialCode = stringToBoolVector(compressor_string);
	Shannon_Fano_recursive(values, 0, values.size() - 1, root, initialCode);
	FreeMemory(root, initialCode); 
	// Для вывода в строку можно использовать цикл
	string answerString;
	for (bool bit : initialCode) {
		answerString += bit ? '1' : '0';
	}
	return answerString;
}