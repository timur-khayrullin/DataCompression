#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, int> table_c;
unordered_map<int, string> table_d;

string first_input_char, next_input_char, translation, char_to_str, output_str, encoded_str;
vector<int> output_code;

int code = 256;
int count = 256;

string Korgin_LZW(string input_data)
{
    //        Encoding

    for (int i = 0; i <= 255; i++) {
        char_to_str = "";
        char_to_str += char(i);
        table_c[char_to_str] = i;
    }

    first_input_char = "";
    next_input_char = "";
    encoded_str = "";

    first_input_char += input_data[0];
    
    //        Character combination
    for (int i = 0; i < input_data.length(); i++) {
        if (i != input_data.length() - 1)
            next_input_char += input_data[i + 1];
        if (table_c.find(first_input_char + next_input_char) != table_c.end()) {
            first_input_char += next_input_char;
        }
        else {
            //output_code.push_back(table_c[first_input_char]);
            encoded_str += to_string(table_c[first_input_char]);
            table_c[first_input_char + next_input_char] = code;
            code++;
            first_input_char = next_input_char;
        }
        next_input_char = "";
    }
    
    encoded_str += to_string(table_c[first_input_char]);
    return encoded_str;
}
