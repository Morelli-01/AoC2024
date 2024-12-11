//
// Created by nicola on 12/11/24.
//


#include "utils.h"

void split_rule(vector<size_t> &v) {
    for (int i = 0; i < v.size(); i++) {
        auto &item = v[i];
        if (item == 0) item = 1;
        else if (to_string(item).size() % 2 == 0) {
            auto tmp = to_string(item);
            size_t lhs = stoi(tmp.substr(0, (tmp.size()) / 2));
            size_t rhs = stoi(tmp.substr(tmp.size() / 2, tmp.size() / 2));
            item = lhs;
            v.insert(v.begin() + i + 1, rhs);
            i++;
        } else item *= 2024;
    }
}

void riddle11_1(string file_name) {

    ifstream is(file_name);
    vector<size_t> v{};
    size_t tmp = 0;
    while (is.good() and is.peek() != EOF) {
        is >> tmp;
        v.push_back(tmp);
    }
    size_t n_blinks = 25;
    for (int i = 0; i < n_blinks; ++i) {
        split_rule(v);
    }
    cout << "The solution of riddle11_1 is: " << v.size() << endl;
}

int main(void) {
    riddle11_1("/home/nicola/Desktop/AoC2024/input_files/day11_1.txt");


    return EXIT_SUCCESS;
}