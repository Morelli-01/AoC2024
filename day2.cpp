//
// Created by nicola on 12/2/24.
//

#include <cstdlib>
#include "cstdint"
#include "utility"
#include "vector"
#include "iostream"
#include "string"
#include "fstream"
#include "cmath"
#include "map"

using namespace std;

void riddle2_1(string file_name) {
    ifstream is_(file_name, ios::binary);
    string tmpStr = "";
    char tmpC;
    vector<vector<size_t>> v;
    size_t i = 0;
    v.push_back(vector<size_t>{});

    while (is_.good()) {
        while (is_.peek() != 32 and is_.peek() != '\n' and is_.peek() != EOF) {
            tmpStr.append(to_string(is_.get() - 48));
        }
        v[i].push_back(stoi(tmpStr));
        tmpStr.clear();
        if ((tmpC = is_.get()) == '\n') {
            i++;
            v.push_back(vector<size_t>{});
        }
    }

}

int main() {
    riddle2_1("/home/nicola/Desktop/AoC2024/input_files/day2_1.txt");
    return EXIT_SUCCESS;
}