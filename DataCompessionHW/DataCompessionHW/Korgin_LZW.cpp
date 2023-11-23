#include <iostream>
#include <unordered_map>
#include "KORGIN_LZW.h"
std::unordered_map<std::string, int> encoding_map;
std::unordered_map<int, std::string> decoding_map;

std::string KORGIN_LZW(const std::string& input_data) {
    std::string encoded_str;

    for (int i = 0; i <= 255; ++i) {
        std::string char_to_str = std::string(1, char(i));
        encoding_map[char_to_str] = i;
        decoding_map[i] = char_to_str;
    }

    std::string current_sequence;
    for (char input_char : input_data) {
        std::string next_char = std::string(1, input_char);
        std::string concatenated = current_sequence + next_char;
        if (encoding_map.find(concatenated) != encoding_map.end()) {
            current_sequence = concatenated;
        } else {
            encoded_str += std::to_string(encoding_map[current_sequence]) + " ";
            encoding_map[concatenated] = static_cast<int>(encoding_map.size());
            decoding_map[static_cast<int>(decoding_map.size())] = concatenated;
            current_sequence = next_char;
        }
    }

    if (!current_sequence.empty()) {
        encoded_str += std::to_string(encoding_map[current_sequence]);
    }

    return encoded_str;
}

std::string KORGIN_LZW_Decode(const std::string& encoded_str) {
    std::string decoded_str;

    for (int i = 0; i <= 255; ++i) {
        std::string char_to_str = std::string(1, char(i));
        decoding_map[i] = char_to_str;
    }

    std::string output;
    int code;
    std::string current_sequence;

    for (char c : encoded_str) {
        if (c != ' ') {
            output += c;
        } else {
            code = std::stoi(output);
            if (decoding_map.find(code) == decoding_map.end()) {
                current_sequence = decoding_map[std::stoi(output.substr(0, output.size() - 1))];
                current_sequence += current_sequence[0];
            } else {
                current_sequence = decoding_map[code];
            }
            decoded_str += current_sequence;

            if (decoding_map.size() < 4096) {
                decoding_map[static_cast<int>(decoding_map.size())] = decoding_map[std::stoi(output.substr(0, output.size() - 1))] + current_sequence[0];
            }

            output = "";
        }
    }

    return decoded_str;
}
