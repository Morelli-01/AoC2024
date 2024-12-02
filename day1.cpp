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

void classic_sort(vector<size_t> &v) {

}

void riddle1_1(string file_name) {

    ifstream is_(file_name);
    vector<size_t> v1, v2;
    size_t tmp;
    while (is_.good()) {
        is_ >> tmp;
        v1.push_back(tmp);
        is_ >> tmp;
        v2.push_back(tmp);
    }
    is_.close();
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
//    return pair<vector<size_t>, vector<size_t>>{v1, v2};
    size_t dst = 0;
    for (int i = 0; i < v1.size(); ++i) {
        dst += std::abs((int) (v1[i] - v2[i]));
    }
    cout << "The solution of riddle 1_1 is " << dst << endl;
}

void riddle1_2(string file_name) {

    ifstream is_(file_name);
    vector<size_t> v1, v2;
    size_t tmp;
    while (is_.good()) {
        is_ >> tmp;
        v1.push_back(tmp);
        is_ >> tmp;
        v2.push_back(tmp);
    }
    is_.close();
//    std::sort(v1.begin(), v1.end());
//    std::sort(v2.begin(), v2.end());
    size_t dst = 0;
    map<size_t, size_t> freq_;
    for (int i = 0; i < v1.size(); ++i) {
        if (not freq_.contains(v1[i])) {
            size_t freq = 0;
            for (auto &e: v2) {
                freq = (e == v1[i]) ? freq + 1 : freq;
            }
            freq_.insert({v1[i], freq});
            dst += freq * v1[i];
        }else{
            dst += freq_[v1[i]] * v1[i];
        }
    }
    cout << "The solution of riddle 1_2 is " << dst << endl;
}

int main() {
    riddle1_1("/home/nicola/Desktop/AoC2024/input_files/day1_1.txt");
    riddle1_2("/home/nicola/Desktop/AoC2024/input_files/day1_1.txt");

    return EXIT_SUCCESS;
}