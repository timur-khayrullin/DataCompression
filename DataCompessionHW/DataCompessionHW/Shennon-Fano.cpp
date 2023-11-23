#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Shennon-Fano.h"

using namespace std;

string return_answer(string& compressor_string)
{
	map<char, int> chars;
	for (char i : compressor_string) {
		i = tolower(i);
		chars[i]++;
	}
	int length = compressor_string.length();
	vector <pair<char, double>> values = frequency_of_chars(chars, length);
	Node* root = new Node('\n', 1.0);
	Shannon_Fano_recursive(values, 0, values.size() - 1, root, "");
	FreeMemory(root, compressor_string);
	return compressor_string;
}