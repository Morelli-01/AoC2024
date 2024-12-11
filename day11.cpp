//
// Created by nicola on 12/11/24.
//


#include "utils.h"
#include "omp.h"

#define N_BLINKS 75

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

void split_rule_parallel(vector<size_t> &v) {

    for (int i = 0; i < N_BLINKS; ++i) {
        split_rule(v);
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
    is.close();
    size_t n_blinks = N_BLINKS;
    for (int i = 0; i < n_blinks; ++i) {
        split_rule(v);
    }
    cout << "The solution of riddle11_1 is: " << v.size() << endl;
}

void riddle11_2(string file_name) {

    ifstream is(file_name);
    vector<vector<size_t>> v{};
    size_t tmp = 0;
    while (is.good() and is.peek() != EOF) {
        is >> tmp;
        v.push_back(vector<size_t>{tmp});
    }
    is.close();

#pragma omp parallel for simd
    for (int i = 0; i < v.size(); ++i)
        split_rule_parallel(v[i]);


    size_t result = 0;
    for (const auto &item: v) {
        result += item.size();
    }
    cout << "The solution of riddle11_2 is: " << result << endl;
}

int main(void) {
    Timer t("general");
//    t.start("riddle11_1");
//    riddle11_1("/home/nicola/Desktop/AoC2024/input_files/day11_1.txt");
//    t.stop();

    t.start("riddle11_2");
    riddle11_2("/home/nicola/Desktop/AoC2024/input_files/day11_1.txt");
    t.stop();

    return EXIT_SUCCESS;
}