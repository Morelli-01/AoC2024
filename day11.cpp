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


void split_rule_parallel_bruteforce(size_t &&v, size_t start_idx, size_t *result) {
    string tmpStr{};
    for (int i = start_idx; i < N_BLINKS; ++i) {
        if (v == 0) v = 1;
        else if ((tmpStr = to_string(v)).size() % 2 == 0) {
            v = stoi(tmpStr.substr(0, (tmpStr.size()) / 2));
#pragma omp task
            split_rule_parallel_bruteforce(stoi(tmpStr.substr(tmpStr.size() / 2, tmpStr.size() / 2)), i + 1, result);
        } else v *= 2024;
    }
#pragma omp atomic
    (*result)++;
}

void riddle11_2_bruteforce(string file_name) {

    ifstream is(file_name);
    vector<size_t> v{};
    size_t tmp = 0;
    while (is.good() and is.peek() != EOF) {
        is >> tmp;
        v.push_back(tmp);
    }
    is.close();

    size_t result = 0;

#pragma omp parallel master
    for (int i = 0; i < v.size(); ++i)
#pragma omp task
            split_rule_parallel_bruteforce(move(v[i]), 0, &result);

#pragma omp taskwait

    cout << "The solution of riddle11_2 is: " << result << endl;
}

void blink_rule(map<size_t, size_t> &m_) {
    map<size_t, size_t> new_m_{};
    for (auto &[key, value]: m_) {
        size_t new_key;
        if (key == 0) new_key = 1;
        else if (to_string(key).size() % 2 == 0) {
            auto tmp = to_string(key);
            size_t lhs = stoi(tmp.substr(0, (tmp.size()) / 2));
            new_key = lhs;

            size_t rhs = stoi(tmp.substr(tmp.size() / 2, tmp.size() / 2));
            if (new_m_.contains(rhs)) new_m_[rhs] += value;
            else new_m_[rhs] = value;

        } else new_key = key * 2024;

        if (new_m_.contains(new_key)) new_m_[new_key] += value;
        else new_m_[new_key] = value;
    }
    m_ = new_m_;
}

void riddle11_2(string file_name) {

    ifstream is(file_name);
    map<size_t, size_t> m_{};
    size_t tmp = 0;
    while (is.good() and is.peek() != EOF) {
        is >> tmp;
        m_[tmp] = 1;
    }
    is.close();

    for (int i = 0; i < N_BLINKS; ++i) {
        blink_rule(m_);
    }

    size_t result = 0;
    for (const auto &item: m_) {
        result += item.second;
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