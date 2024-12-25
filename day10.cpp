//
// Created by nicola on 24/12/24.
//

#include "utils.h"
#include "map"


struct Crd {
    size_t r;
    size_t c;
};

struct HikingTrail {
    Crd trail_head_;

    map<size_t, uint8_t> trail_tails_;

    explicit HikingTrail(Crd trail_head) : trail_head_(trail_head), trail_tails_() {}
};

void get_trail(Mat<uint8_t> &map, Crd trail_head, HikingTrail &ht_) {
    uint8_t target = map[trail_head.r, trail_head.c] + 1;
    if (map[trail_head.r, trail_head.c] == '9') {
        ht_.trail_tails_[trail_head.r * map.cols_ + trail_head.c] = 1;
    }
    int8_t dydx[4][2] = {
            {-1, 0},
            {0,  1},
            {1,  0},
            {0,  -1}
    };

    for (int i = 0; i < 4; ++i) {
        if (trail_head.r + dydx[i][0] < map.rows_ and trail_head.r + dydx[i][0] >= 0
            and trail_head.c + dydx[i][1] < map.cols_ and trail_head.c + dydx[i][1] >= 0) {
            if (map[trail_head.r + dydx[i][0], trail_head.c + dydx[i][1]] == target) {
                get_trail(map, Crd(trail_head.r + dydx[i][0], trail_head.c + dydx[i][1]), ht_);
            }
        }
    }
}

void get_trail_2(Mat<uint8_t> &map, Crd trail_head, HikingTrail &ht_) {
    uint8_t target = map[trail_head.r, trail_head.c] + 1;
    if (map[trail_head.r, trail_head.c] == '9') {
        if (ht_.trail_tails_.contains(trail_head.r * map.cols_ + trail_head.c))
            ht_.trail_tails_[trail_head.r * map.cols_ + trail_head.c] += 1;
        else
            ht_.trail_tails_[trail_head.r * map.cols_ + trail_head.c] = 1;
    }
    int8_t dydx[4][2] = {
            {-1, 0},
            {0,  1},
            {1,  0},
            {0,  -1}
    };

    for (int i = 0; i < 4; ++i) {
        if (trail_head.r + dydx[i][0] < map.rows_ and trail_head.r + dydx[i][0] >= 0
            and trail_head.c + dydx[i][1] < map.cols_ and trail_head.c + dydx[i][1] >= 0) {
            if (map[trail_head.r + dydx[i][0], trail_head.c + dydx[i][1]] == target) {
                get_trail_2(map, Crd(trail_head.r + dydx[i][0], trail_head.c + dydx[i][1]), ht_);
            }
        }
    }
}

void riddle10_1(string file_name) {
    ifstream is(file_name);
    vector<uint8_t> raw_data_{};
    size_t rows = 1, cols;
    while (is.good() and is.peek() != EOF) {
        if (is.peek() != '\n')
            raw_data_.emplace_back(is.get());
        else {
            rows++;
            is.get();
        }
    }
    cols = raw_data_.size() / rows;
    Mat<uint8_t> hiking_map(rows, cols);
    hiking_map.data_ = raw_data_;

    hiking_map.print();
    vector<HikingTrail> trails{};

    for (int r = 0; r < hiking_map.rows_; ++r) {
        for (int c = 0; c < hiking_map.cols_; ++c) {
            if (hiking_map[r, c] == '0') {
                HikingTrail ht_(Crd(r, c));
                get_trail(hiking_map, Crd(r, c), ht_);
                trails.push_back(ht_);
            }
        }

    }

    size_t result = 0;
    for (auto &t: trails) {
        result += t.trail_tails_.size();
    }
    cout << "The solution of riddle10_1 is: " << result << endl;
}

void riddle10_2(string file_name) {
    ifstream is(file_name);
    vector<uint8_t> raw_data_{};
    size_t rows = 1, cols;
    while (is.good() and is.peek() != EOF) {
        if (is.peek() != '\n')
            raw_data_.emplace_back(is.get());
        else {
            rows++;
            is.get();
        }
    }
    cols = raw_data_.size() / rows;
    Mat<uint8_t> hiking_map(rows, cols);
    hiking_map.data_ = raw_data_;

    hiking_map.print();
    vector<HikingTrail> trails{};

    for (int r = 0; r < hiking_map.rows_; ++r) {
        for (int c = 0; c < hiking_map.cols_; ++c) {
            if (hiking_map[r, c] == '0') {
                HikingTrail ht_(Crd(r, c));
                get_trail_2(hiking_map, Crd(r, c), ht_);
                trails.push_back(ht_);
            }
        }

    }

    size_t result = 0;
    for (auto &trail: trails) {
        for (auto &[tail, n]: trail.trail_tails_) {
            result += n;
        }
//        result += trail.trail_tails_.size();
    }
    cout << "The solution of riddle10_1 is: " << result << endl;
}


int main(void) {
    riddle10_1("/home/nicola/Desktop/AoC2024/input_files/day10_1.txt");
    riddle10_2("/home/nicola/Desktop/AoC2024/input_files/day10_1.txt");

    return EXIT_SUCCESS;
}