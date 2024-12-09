//
// Created by nicola on 09/12/24.
//
#include "utils.h"

void riddle9_1(string file_name) {
    ifstream is(file_name);
    char tmpC;
    vector<uint8_t> free_space{};
    map<uint8_t, uint8_t> files{};
    int i = 0, id = 0;
    while (is.good() and (tmpC = is.get()) != EOF) {
        if (tmpC == '\n') continue;
        if (i % 2 == 0) {
            files[id] = tmpC - 48;
            id++;
        } else {
            free_space.push_back(tmpC - 48);
        }
        i++;
    }
    vector<char> sequence{};
    for (int j = 0; j < files.size(); ++j) {
        for (int k = 0; k < files[j]; ++k)
            sequence.push_back(j + 48);
        for (int k = 0; k < free_space[j]; ++k)
            sequence.push_back('.');
    }

    for (const auto &item: sequence) {
        cout << item;
    }
    cout << endl;
    for (int j = 0; j < sequence.size(); ++j) {
        if (sequence[j] == '.') {
            for (int k = j + 1; k < sequence.size(); ++k) {
                if (sequence[k] != '.') {
                    i = 0;
                    for (i = sequence.size() - 1; i >= 0; i--) {
                        if (sequence[i] != '.') break;
                    }
                    sequence[j] = sequence[i];
                    sequence[i] = '.';
                    j = 0;

                    break;
                }
            }

        }

    }
    size_t result = 0;
    for (i = 0; i < sequence.size(); i++) {
        auto item = sequence[i];
        if (item != '.')
            result += i * (item - 48);
    }
    for (const auto &item: sequence) {
        cout << item;
    }
    cout << endl;
    cout << "the solution of riddle9_1 is : " << result << endl;
}

int main(void) {
    riddle9_1("/home/nicola/Desktop/AoC2024/input_files/day9_1.txt");

    return EXIT_SUCCESS;
}