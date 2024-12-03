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
    size_t safe_reporst = 0;
    int j = 0;
    outer_for:
    for (j; j < v.size(); j++) {
        auto rep = v[j];
        bool is_increasing = (rep.back() > rep.front());
        int dst;
        if (is_increasing) {
            for (i = 0; i < rep.size() - 1; ++i) {
                dst = rep[i + 1] - rep[i];
                if (dst <= 0 or dst > 3) {
                    j++;
                    goto outer_for;
                }
            }
        } else {
            for (i = 0; i < rep.size() - 1; ++i) {
                dst = rep[i + 1] - rep[i];
                if (dst >= 0 or dst < -3) {
                    j++;
                    goto outer_for;
                }
            }
        }
        safe_reporst++;
    }
    cout << "the solution of riddle2_1 is: " << safe_reporst << endl;
}

void fix(vector<size_t> &v, int idx) {
    size_t prev, succ;
    if (idx == 0) prev = v[idx] - 1;
    else prev = v[idx - 1];
    if (idx + 2 >= v.size()) succ = v[idx] + 1;
    else succ = v[idx + 2];
    int dst1 = v[idx] - prev, dst2 = succ - v[idx];
    if (dst1 > 0 and dst1 <= 3 and dst2 > 0 and dst2 <= 3) {
        v.erase(v.begin() + idx + 1);
    } else {
        v.erase(v.begin() + idx);
    }
}

void riddle2_2(string file_name) {
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
    size_t safe_reporst = 0;
    for (auto &rep: v) {
        bool is_increasing = (rep.back() > rep.front());
        int counter = 0;
        for (i = 0; i <= rep.size() - 1; i++) {
            if (rep[i] < rep[i + 1]) counter++;
            else counter--;
        }
        is_increasing = (counter > 0);

        if (not is_increasing)std::reverse(rep.begin(), rep.end());
        bool bonus = true;
        bool safe = true;

        int dst;
        for (i = 0; i < rep.size() - 1; ++i) {
            dst = rep[i + 1] - rep[i];
            if ((dst <= 0 or dst > 3) and bonus) {
                bonus = false;
                dst = rep[i + 2] - rep[i];
                fix(rep, i);
                i = -1;
            } else if ((dst <= 0 or dst > 3) and not bonus) {
                safe = false;
            }
        }
        if (safe) safe_reporst++;
    }
    cout << "the solution of riddle2_1 is: " << safe_reporst << endl;
}

int main() {
    riddle2_1("/home/nicola/Desktop/AoC2024/input_files/day2_1.txt");
    riddle2_2("/home/nicola/Desktop/AoC2024/input_files/day2_1.txt");
    return EXIT_SUCCESS;
}