//
// Created by nicola on 12/9/24.
//
#include "utils.h"

//using coord_ = pair<size_t, size_t>;

struct coord_ {
    size_t x;
    size_t y;

    coord_ operator-(coord_ &rhs) {
        coord_ result(0, 0);
        result.x = x - rhs.x;
        result.y = y - rhs.y;
        return result;
    }

    coord_ operator+(coord_ &rhs) {
        coord_ result(0, 0);
        result.x = x + rhs.x;
        result.y = y + rhs.y;
        return result;
    }

};

void print(Mat<vector<uint8_t>> &antinodes) {
    cout << "[" << antinodes.rows_ << "," << antinodes.cols_ << "]\n";
    for (int r = 0; r < antinodes.rows_; ++r) {
        for (int c = 0; c < antinodes.cols_; ++c) {
            auto v = antinodes.data_[r * antinodes.cols_ + c];
            if (v.empty())
                cout << "., ";
            else {
                cout << '[';
                for (const auto &item: v) {
                    cout << item << ',';
                }
                cout << ']';
            }
        }
        cout << endl;
    }
}


void compute_antinodes(Mat<uint8_t> &antennas, Mat<vector<uint8_t>> &antinodes) {

    map<uint8_t, vector<coord_>> antennas_map{};

    for (size_t r = 0; r < antennas.rows_; ++r) {
        for (size_t c = 0; c < antennas.cols_; ++c) {
            if (antennas[r, c] != '.') {
                if (antennas_map.contains(antennas[r, c]))
                    antennas_map[antennas[r, c]].emplace_back(r, c);
                else {
                    antennas_map[antennas[r, c]] = vector<coord_>{coord_(r, c)};
                }
            }
        }
    }
    for (auto ant: antennas_map) {
        auto positions = ant.second;
        for (int j1 = 0; j1 < positions.size() - 1; ++j1) {
            for (int j2 = j1 + 1; j2 < positions.size(); ++j2) {
                coord_ dst = positions[j2] - positions[j1];
                coord_ antinode1 = positions[j1] - dst;
                coord_ antinode2 = positions[j2] + dst;
                if (antinode1.x < antinodes.cols_ and antinode1.y < antinodes.rows_)
                    antinodes[antinode1.x, antinode1.y].push_back(ant.first);
                if (antinode2.x < antinodes.cols_ and antinode2.y < antinodes.rows_)
                    antinodes[antinode2.x, antinode2.y].push_back(ant.first);

            }
        }
    }
//    print(antinodes);
}

void compute_antinodes_2(Mat<uint8_t> &antennas, Mat<vector<uint8_t>> &antinodes) {

    map<uint8_t, vector<coord_>> antennas_map{};

    for (size_t r = 0; r < antennas.rows_; ++r) {
        for (size_t c = 0; c < antennas.cols_; ++c) {
            if (antennas[r, c] != '.') {
                if (antennas_map.contains(antennas[r, c]))
                    antennas_map[antennas[r, c]].emplace_back(r, c);
                else {
                    antennas_map[antennas[r, c]] = vector<coord_>{coord_(r, c)};
                }
            }
        }
    }
    for (auto ant: antennas_map) {
        auto positions = ant.second;
        for (int j1 = 0; j1 < positions.size() - 1; ++j1) {
            for (int j2 = j1 + 1; j2 < positions.size(); ++j2) {
                coord_ dst = positions[j2] - positions[j1];
                coord_ antinode1 = positions[j1];
                while (antinode1.x < antinodes.cols_ and antinode1.y < antinodes.rows_) {
                    antinodes[antinode1.x, antinode1.y].push_back(ant.first);
                    antinode1 = antinode1 - dst;
                }
                coord_ antinode2 = positions[j2];
                while (antinode2.x < antinodes.cols_ and antinode2.y < antinodes.rows_) {
                    antinodes[antinode2.x, antinode2.y].push_back(ant.first);
                    antinode2 = antinode2 + dst;
                }
            }
        }
    }
//    print(antinodes);
}

void riddle8_1(string file_name) {
//    Mat<uint8_t> antennas
    ifstream is(file_name);
    vector<uint8_t> data{};
    size_t rows = 1;
    while (is.good() and is.peek() != EOF) {
        if (is.peek() == '\n') {
            rows++;
            is.get();
        } else
            data.push_back(is.get());
    }
    is.close();
    for (auto &item: data) {
        if (item == '#') item = '.';
    }

    Mat<uint8_t> antennas(rows, data.size() / rows);
    Mat<vector<uint8_t>> antinodes(rows, data.size() / rows, vector<uint8_t>{});

    antennas.data_ = data;
    compute_antinodes(antennas, antinodes);

    size_t result = 0;
    for (auto &item: antinodes.data_) {
        if (!item.empty()) result++;
    }


    cout << "The solution of riddle8_1 is: " << result << endl;
}

void riddle8_2(string file_name) {
//    Mat<uint8_t> antennas
    ifstream is(file_name);
    vector<uint8_t> data{};
    size_t rows = 1;
    while (is.good() and is.peek() != EOF) {
        if (is.peek() == '\n') {
            rows++;
            is.get();
        } else
            data.push_back(is.get());
    }
    is.close();
    for (auto &item: data) {
        if (item == '#') item = '.';
    }

    Mat<uint8_t> antennas(rows, data.size() / rows);
    Mat<vector<uint8_t>> antinodes(rows, data.size() / rows, vector<uint8_t>{});

    antennas.data_ = data;
    compute_antinodes_2(antennas, antinodes);

    size_t result = 0;
    for (auto &item: antinodes.data_) {
        if (!item.empty()) result++;
    }


    cout << "The solution of riddle8_1 is: " << result << endl;
}

int main(void) {
    riddle8_1("/home/nicola/Desktop/AoC2024/input_files/day8_1.txt");
    riddle8_2("/home/nicola/Desktop/AoC2024/input_files/day8_1.txt");

    return EXIT_SUCCESS;
}