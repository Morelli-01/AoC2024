//
// Created by nicola on 12/3/24.
//

#ifndef AOC2024_UTILS_H
#define AOC2024_UTILS_H

#include <cstdlib>
#include "cstdint"
#include "utility"
#include "vector"
#include "iostream"
#include "string"
#include "fstream"
#include "cmath"
#include "map"
#include "chrono"
#include "algorithm"

using namespace std;
using namespace chrono;

struct Timer {
    time_point<steady_clock> start_ = steady_clock::now();
    time_point<steady_clock> stop_ = steady_clock::now();
    string task_name_;

    Timer(string task_name);

    void start();

    void start(string task_name);

    void stop();

    void stop_flops(float flops);
};

template<typename T>
struct Mat {
    size_t cols_;
    size_t rows_;
    vector<T> data_;

    Mat(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_ = vector<T>(rows * cols);
    }

    Mat(size_t rows, size_t cols, T fill_data) : rows_(rows), cols_(cols) {
        data_ = vector<T>(rows * cols, fill_data);
    }

    T &operator[](size_t r, size_t c) {
        return data_[r * cols_ + c];
    }

    const T &operator[](size_t r, size_t c) const {
        return data_[r * cols_ + c];
    }

    auto ptr() {
        return data_.data();
    }

    void print() {
        cout << "[" << rows_ << "," << cols_ << "]\n";
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                cout << data_[r * cols_ + c] << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Mat<T> copy() {
        Mat<T> cpy(rows_, cols_);
        for (int i = 0; i < data_.size(); ++i) {
            cpy.data_[i] = data_[i];

        }

        return cpy;
    }
};

#endif //AOC2024_UTILS_H
