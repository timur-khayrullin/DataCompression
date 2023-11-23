#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Node {
	char symbol;
	double frequency;
	string code;
	Node* left;
	Node* right;

	Node(char s, double f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
};


void FreeMemory(Node* root, string& answer) {
	if (root == nullptr) {
		return;
	}
	FreeMemory(root->left, answer);
	FreeMemory(root->right, answer);
	answer += root->code;
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

void Shannon_Fano_recursive(vector <pair<char, double>> vec, int l, int r, Node * root, const string & code) {
	if (l >= r) {
		root->symbol = vec[l].first;
		root->frequency = vec[l].second;
		root->code = code;
		cout << "Символ   " << root->symbol << "   Код   " << root->code << '\n';
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
	root->left = new Node('\0', 0.0);
	root->right = new Node('\0', 0.0);

	Shannon_Fano_recursive(vec, l, mid - 1, root->left, code + "0");
	Shannon_Fano_recursive(vec, mid, r1, root->right, code + "1");
	return;
}

