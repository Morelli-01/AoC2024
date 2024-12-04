//
// Created by nicola on 12/4/24.
//

#include "utils.h"


template<typename T>
struct Mat {
    size_t cols_;
    size_t rows_;
    vector<T> data_;

    Mat(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_ = vector<T>(rows * cols);
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
};

bool check_diag(size_t r, size_t c, Mat<char> &mat) {
    if (mat[r - 1, c - 1] == 'M' and mat[r + 1, c + 1] == 'S') return true;
    if (mat[r - 1, c - 1] == 'S' and mat[r + 1, c + 1] == 'M') return true;
    return false;
}

bool check_antidiag(size_t r, size_t c, Mat<char> &mat) {
    if (mat[r - 1, c + 1] == 'M' and mat[r + 1, c - 1] == 'S') return true;
    if (mat[r - 1, c + 1] == 'S' and mat[r + 1, c - 1] == 'M') return true;
    return false;
}

int check_neighborhood_X_MAS(size_t r, size_t c, Mat<char> &mat) {
    int cnt = 0;
    if (mat[r, c] == 'A') {
        if (check_diag(r, c, mat) and check_antidiag(r, c, mat))
            cnt++;
    }
    return cnt;
}


int check_neighborhood_XMAS(size_t r, size_t c, Mat<char> &mat) {
    char XMAS[] = {'X', 'M', 'A', 'S'};
    int cnt = 0;
    if (mat[r, c] == 'X') {
        for (int r1 = -1; r1 < 2; ++r1) {
            for (int c1 = -1; c1 < 2; ++c1) {
                if (mat[r + r1 * 1, c + c1 * 1] == XMAS[1]
                    and mat[r + r1 * 2, c + c1 * 2] == XMAS[2]
                    and mat[r + r1 * 3, c + c1 * 3] == XMAS[3]) {
//                    cout << "found solution: " << mat[r, c] << mat[r + r1 * 1, c + c1 * 1] <<
//                         mat[r + r1 * 2, c + c1 * 2] << mat[r + r1 * 3, c + c1 * 3] << endl;

                    cnt++;
                }

            }
        }
    }
    return cnt;
}

void riddle4_1(string file_name) {
    ifstream is(file_name);
    char tmpC;
    size_t rows = 0, cols;
    vector<char> data{};
    while (is.good()) {
        tmpC = is.get();
        if (tmpC == '\n' or tmpC == EOF) {
            rows++;
            continue;
        } else if (tmpC == 'X' or tmpC == 'M' or
                   tmpC == 'A' or tmpC == 'S') {
            data.push_back(tmpC);
        }
    }
    cols = data.size() / rows;
    Mat<char> m(rows, cols);
    m.data_ = data;
    Mat<char> padded_data(rows + 2, cols + 2);

    for (int r = 0; r < rows + 2; ++r) {
        if (r == 0 or r == rows + 1) {
            for (int c = 0; c < cols + 2; ++c)
                padded_data[r, c] = '.';
        } else {
            for (int c = 0; c < cols + 2; ++c) {
                if (c == 0 or c == cols + 1) padded_data[r, c] = '.';
                else {
                    padded_data[r, c] = m[r - 1, c - 1];
                }
            }
        }
    }
    padded_data.print();
    int cnt = 0;
    for (int r = 1; r < rows + 1; ++r) {
        for (int c = 1; c < cols + 1; ++c) {
            cnt += check_neighborhood_XMAS(r, c, padded_data);
        }
    }
    padded_data.print();


    cout << "The solution to riddle4_1 is: " << cnt << endl;
}

void riddle4_2(string file_name) {
    ifstream is(file_name);
    char tmpC;
    size_t rows = 0, cols;
    vector<char> data{};
    while (is.good()) {
        tmpC = is.get();
        if (tmpC == '\n' or tmpC == EOF) {
            rows++;
            continue;
        } else if (tmpC == 'X' or tmpC == 'M' or
                   tmpC == 'A' or tmpC == 'S') {
            data.push_back(tmpC);
        }
    }
    cols = data.size() / rows;
    Mat<char> m(rows, cols);
    m.data_ = data;
    Mat<char> padded_data(rows + 2, cols + 2);

    for (int r = 0; r < rows + 2; ++r) {
        if (r == 0 or r == rows + 1) {
            for (int c = 0; c < cols + 2; ++c)
                padded_data[r, c] = '.';
        } else {
            for (int c = 0; c < cols + 2; ++c) {
                if (c == 0 or c == cols + 1) padded_data[r, c] = '.';
                else {
                    padded_data[r, c] = m[r - 1, c - 1];
                }
            }
        }
    }
    padded_data.print();
    int cnt = 0;
    for (int r = 1; r < rows + 1; ++r) {
        for (int c = 1; c < cols + 1; ++c) {
            cnt += check_neighborhood_X_MAS(r, c, padded_data);
        }
    }
    padded_data.print();


    cout << "The solution to riddle4_2 is: " << cnt << endl;
}

int main(void) {
    riddle4_1("/home/nicola/Desktop/AoC2024/input_files/day4_1.txt");
    riddle4_2("/home/nicola/Desktop/AoC2024/input_files/day4_1.txt");

    return EXIT_SUCCESS;

}