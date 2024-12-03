//
// Created by nicola on 12/3/24.
//

#include "utils.h"

void riddle3_1(string file_name) {
    ifstream is(file_name);
    char tmpC;
    string tmpStr = "";
    vector<string> matmuls;
    vector<size_t> factors;
    while (((tmpC = is.get()) != EOF) and is.good()) {
        tmpStr.clear();
        if (tmpC == 'm') {
            tmpStr += tmpC;

            if (is.peek() == 'u') tmpStr += is.get();
            else continue;
            if (is.peek() == 'l') tmpStr += is.get();
            else continue;
            if (is.peek() == '(') tmpStr += is.get();
            else continue;
            string factor1, factor2;
            while (isdigit(is.peek())) {
                factor1 += is.get();
            }
            tmpStr += factor1;
            if (is.peek() == ',') tmpStr += is.get();
            else continue;
            while (isdigit(is.peek())) {
                factor2 += is.get();
            }
            tmpStr += factor2;
            if (is.peek() == ')') tmpStr += is.get();
            else continue;
            matmuls.push_back(tmpStr);
            factors.push_back(stoi(factor1));
            factors.push_back(stoi(factor2));
        }
    }
    size_t result = 0;
    for (int i = 0; i < factors.size() / 2; ++i) {
        result += factors[i * 2] * factors[i * 2 + 1];
    }
    cout << "the result of riddle3_1 is : " << result << endl;

}

void riddle3_2(string file_name) {
    ifstream is(file_name);
    char tmpC;
    string tmpStr = "";
    vector<string> matmuls;
    vector<size_t> factors;
    bool matmuls_enable = true;
    while (((tmpC = is.get()) != EOF) and is.good()) {
        tmpStr.clear();
        if (tmpC == 'm') {
            tmpStr += tmpC;

            if (is.peek() == 'u') tmpStr += is.get();
            else continue;
            if (is.peek() == 'l') tmpStr += is.get();
            else continue;
            if (is.peek() == '(') tmpStr += is.get();
            else continue;
            string factor1, factor2;
            while (isdigit(is.peek())) {
                factor1 += is.get();
            }
            tmpStr += factor1;
            if (is.peek() == ',') tmpStr += is.get();
            else continue;
            while (isdigit(is.peek())) {
                factor2 += is.get();
            }
            tmpStr += factor2;
            if (is.peek() == ')') tmpStr += is.get();
            else continue;
            matmuls.push_back(tmpStr);
            if (matmuls_enable) {
                factors.push_back(stoi(factor1));
                factors.push_back(stoi(factor2));
            }
        } else if (tmpC == 'd') {
            tmpStr += tmpC;
            if (is.peek() == 'o') tmpStr += is.get();
            else continue;
            if (is.peek() == '(') {
                tmpStr += is.get();
                if (is.peek() == ')') tmpStr += is.get();
                else continue;
                matmuls_enable = true;
            }
            if (is.peek() == 'n') tmpStr += is.get();
            else continue;
            if (is.peek() == '\'') tmpStr += is.get();
            else continue;
            if (is.peek() == 't') tmpStr += is.get();
            else continue;
            if (is.peek() == '(') tmpStr += is.get();
            else continue;
            if (is.peek() == ')') tmpStr += is.get();
            else continue;
            matmuls_enable = false;
        }
    }
    size_t result = 0;
    for (int i = 0; i < factors.size() / 2; ++i) {
        result += factors[i * 2] * factors[i * 2 + 1];
    }
    cout << "the result of riddle3_2 is : " << result << endl;

}


int main() {
    riddle3_1("/home/nicola/Desktop/AoC2024/input_files/day3_1.txt");
    riddle3_2("/home/nicola/Desktop/AoC2024/input_files/day3_1.txt");
    return EXIT_SUCCESS;
}