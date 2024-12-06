//
// Created by nicola on 12/5/24.
//


#include "utils.h"

bool is_sequence_good(map<size_t, vector<size_t>> &rules, vector<size_t> &sequence) {
    for (int i = 1; i < sequence.size(); ++i) {
        auto v = sequence[i];
        if (rules.contains(v)) {
            auto rule = rules[v];
            for (int j = 0; j < i; ++j) {
                if (ranges::contains(rule, sequence[j]))
                    return false;
            }
        }

    }
    return true;
}

bool is_sequence_good_or_fix(map<size_t, vector<size_t>> &rules, vector<size_t> &sequence) {
    bool flag = true;
    start:
    for (int i = 1; i < sequence.size(); ++i) {
        auto v = sequence[i];
        if (rules.contains(v)) {
            auto rule = rules[v];
            for (int j = 0; j < i; ++j) {
                if (ranges::contains(rule, sequence[j])) {
                    sequence[i] = sequence[j];
                    sequence[j] = v;
                    flag = false;
                    goto start;
                }
            }
        }

    }
    return flag;
}

void riddle5_1(string file_name) {

    ifstream is(file_name);
    map<size_t, vector<size_t>> rules;
    char tmpC;
    string tmpStr = "";
    while ((tmpC = is.get()) != '\n') {
        string key = to_string(tmpC - 48), value = "";
        while ((tmpC = is.get()) != '|')key += tmpC;
        while ((tmpC = is.get()) != '\n')value += tmpC;

        if (rules.contains(stoi(key))) {
            rules[stoi(key)].push_back(stoi(value));
        } else {
            rules[stoi(key)] = vector<size_t>{(size_t) stoi(value)};
        }
        key.clear();
        value.clear();
    }

    vector<vector<size_t>> sequencies{};
        while (is.good() and (tmpC = is.get()) != EOF) {
            tmpStr.clear();
            vector<size_t> tmpV{};
            tmpStr += tmpC;

            while (is.peek() != '\n' and is.good()) {
                tmpC = is.get();
                if (tmpC == ',') {
                    tmpV.push_back(stoi(tmpStr));
                    tmpStr.clear();
                } else tmpStr += tmpC;
            }
            tmpV.push_back(stoi(tmpStr));
            if (is_sequence_good(rules, tmpV))
                sequencies.push_back(tmpV);
        }
    size_t solution = 0;
    for (auto &s: sequencies) {
        auto middle_idx = floor(s.size() / 2);
        solution += s[middle_idx];
    }
    cout << "The solution of riddle5_1 is: " << solution << endl;
}

void riddle5_2(string file_name) {

    ifstream is(file_name);
    map<size_t, vector<size_t>> rules;
    char tmpC;
    string tmpStr = "";
    while ((tmpC = is.get()) != '\n') {
        string key = to_string(tmpC - 48), value = "";
        while ((tmpC = is.get()) != '|')key += tmpC;
        while ((tmpC = is.get()) != '\n')value += tmpC;

        if (rules.contains(stoi(key))) {
            rules[stoi(key)].push_back(stoi(value));
        } else {
            rules[stoi(key)] = vector<size_t>{(size_t) stoi(value)};
        }
        key.clear();
        value.clear();
    }

    vector<vector<size_t>> sequencies{};
    vector<vector<size_t>> bad_sequencies{};

    while (is.good() and (tmpC = is.get()) != EOF) {
        tmpStr.clear();
        vector<size_t> tmpV{};
        tmpStr += tmpC;

        while (is.peek() != '\n' and is.good()) {
            tmpC = is.get();
            if (tmpC == ',') {
                tmpV.push_back(stoi(tmpStr));
                tmpStr.clear();
            } else tmpStr += tmpC;
        }
        tmpV.push_back(stoi(tmpStr));
        if (is_sequence_good_or_fix(rules, tmpV))
            sequencies.push_back(tmpV);
        else bad_sequencies.push_back(tmpV);
    }
    size_t solution = 0;
    for (auto &s: bad_sequencies) {
        auto middle_idx = floor(s.size() / 2);
        solution += s[middle_idx];
    }
    cout << "The solution of riddle5_2 is: " << solution << endl;
}

int main(void) {

    riddle5_1("/home/nicola/Desktop/AoC2024/input_files/day5_1.txt");
    riddle5_2("/home/nicola/Desktop/AoC2024/input_files/day5_1.txt");
    return EXIT_SUCCESS;
}
