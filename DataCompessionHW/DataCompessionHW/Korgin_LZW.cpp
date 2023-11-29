#include <iostream>
#include <unordered_map>
#include <string>

#include "KORGIN_LZW.h"

std::string KORGIN_LZW(const std::string& input_data) {
    std::unordered_map<std::string, int> encoding_map;
    std::string encoded_str;

    for (int i = 0; i <= 255; ++i) {
        std::string char_to_str = std::string(1, char(i));
        encoding_map[char_to_str] = i;
    }

    std::string current_sequence;
    for (char input_char : input_data) {
        std::string concatenated = current_sequence + input_char;
        if (encoding_map.find(concatenated) != encoding_map.end()) {
            current_sequence = concatenated;
        } else {
            encoded_str += std::to_string(encoding_map[current_sequence]) + " ";
            encoding_map[concatenated] = static_cast<int>(encoding_map.size());
            current_sequence = input_char;
        }
    }

    if (!current_sequence.empty()) {
        encoded_str += std::to_string(encoding_map[current_sequence]);
    }

    return encoded_str;
}

std::string KORGIN_LZW_Decode(const std::string& encoded_str) {
    std::unordered_map<int, std::string> decoding_map;
    std::string decoded_str;

    for (int i = 0; i <= 255; ++i) {
        std::string char_to_str = std::string(1, char(i));
        decoding_map[i] = char_to_str;
    }

    int prev_code = -1;
    std::string entry;
    std::string code;

    for (char c : encoded_str) {
        if (c != ' ') {
            code += c;
        } else {
            int current_code = std::stoi(code);
            if (decoding_map.find(current_code) != decoding_map.end()) {
                entry = decoding_map[current_code];
            } else {
                entry = decoding_map[prev_code] + decoding_map[prev_code][0];
            }
            decoded_str += entry;

            if (prev_code != -1) {
                decoding_map[decoding_map.size()] = decoding_map[prev_code] + entry[0];
            }

            prev_code = current_code;
            code = "";
        }
    }

    if (!code.empty()) {
        int current_code = std::stoi(code);
        std::string entry;
        if (decoding_map.find(current_code) != decoding_map.end()) {
            entry = decoding_map[current_code];
        } else {
            entry = decoding_map[prev_code] + decoding_map[prev_code][0];
        }
        decoded_str += entry;
    }

    return decoded_str;
}
