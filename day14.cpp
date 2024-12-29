//
// Created by nicola on 12/29/24.
//

#include "utils.h"
#include <thread>

#define DIM_X 101
#define DIM_Y 103

using Crd = pair<int, int>;
using Vel = pair<int, int>;

void print(Mat<size_t> &m) {
    cout << "[" << m.rows_ << "," << m.cols_ << "]\n";
    for (int r = 0; r < m.rows_; ++r) {
        for (int c = 0; c < m.cols_; ++c) {
            if (m.data_[r * m.cols_ + c] == 0)
                cout << " ";
            else
//                cout << m.data_[r * m.cols_ + c] << "";
                cout << "#" << "";
        }
        cout << endl;
    }
    cout << endl;
}


struct Robot {
    Crd crd;
    Vel vel;

    explicit Robot(size_t x, size_t y, int dx, int dy) : crd(x, y), vel(dx, dy) {}

    void step() {
        crd.first = crd.first + vel.first;
        while (crd.first < 0)
            crd.first = DIM_X + crd.first;
        while (crd.first >= DIM_X)
            crd.first = crd.first - DIM_X;
        crd.second = crd.second + vel.second;
        while (crd.second < 0)
            crd.second = DIM_Y + crd.second;
        while (crd.second >= DIM_Y)
            crd.second = crd.second - DIM_Y;
    }
};

void update_space(Mat<size_t> &space, vector<Robot> &robots) {
    for (auto &item: space.data_) {
        item = 0;
    }
    for (const auto &item: robots) {
        space[item.crd.second, item.crd.first] += 1;
    }
}

bool look_for_tree(Mat<size_t> &space) {
    Mat<size_t> k(3, 3, 1);

    for (int r = 0; r < space.rows_ - 3; ++r)
        for (int c = 0; c < space.cols_ - 3; ++c) {
            size_t tmp = 0;
            for (int r1 = 0; r1 < 3; ++r1)
                for (int c1 = 0; c1 < 3; ++c1)
                    tmp += (space[r + r1, c + c1] * k[r1, c1] != 0) ? 1 : 0;


            if (tmp == 9) return true;
        }


    return false;
}

void riddle14_1(string file_name) {

    ifstream is(file_name);
    vector<Robot> robots{};

    while (is.good() and is.peek() != EOF) {
        Robot r(0, 0, 0, 0);
        size_t tmp = is.peek();
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> r.crd.first;
        while (is.peek() < 48 or is.peek() > 57)is.get();
        is >> r.crd.second;
        while ((is.peek() < 48 or is.peek() > 57) and is.peek() != 45)is.get();
        is >> r.vel.first;
        while ((is.peek() < 48 or is.peek() > 57) and is.peek() != 45)is.get();
        is >> r.vel.second;
        robots.emplace_back(r);
    }

    Mat<size_t> space(DIM_Y, DIM_X);
    update_space(space, robots);
//    print(space);
    for (int i = 0; i < 100; ++i) {
        for (auto &r: robots) {
            r.step();
        }
        update_space(space, robots);
//        print(space);
    }

    size_t median_x = (DIM_X - 1) / 2, median_y = (DIM_Y - 1) / 2;
    size_t robots_count[4] = {0, 0, 0, 0};
    for (int r = 0; r < space.rows_; ++r) {
        if (r == median_y)continue;
        for (int c = 0; c < space.cols_; ++c) {
            if (c == median_x)continue;
            robots_count[2 * ((r > median_y) ? 1 : 0) + ((c > median_x) ? 1 : 0)] += space[r, c];
        }
    }

    size_t result = 1;
    for (const auto &item: robots_count) {
        result *= item;
    }
    cout << "The solution for riddle12_1 is: " << result << endl;
}

void riddle14_2(string file_name) {

    ifstream is(file_name);
    vector<Robot> robots{};

    while (is.good() and is.peek() != EOF) {
        Robot r(0, 0, 0, 0);
        size_t tmp = is.peek();
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> r.crd.first;
        while (is.peek() < 48 or is.peek() > 57)is.get();
        is >> r.crd.second;
        while ((is.peek() < 48 or is.peek() > 57) and is.peek() != 45)is.get();
        is >> r.vel.first;
        while ((is.peek() < 48 or is.peek() > 57) and is.peek() != 45)is.get();
        is >> r.vel.second;
        robots.emplace_back(r);
    }

    Mat<size_t> space(DIM_Y, DIM_X);
    update_space(space, robots);
    size_t median_x = (DIM_X - 1) / 2, median_y = (DIM_Y - 1) / 2;


    for (int i = 0; i < 10000; ++i) {
        for (auto &r: robots) {
            r.step();
        }
        update_space(space, robots);
        if (look_for_tree(space)) {
            std::system("clear");
            cout << (i + 1) << endl;
            print(space);
            return;
        }

    }

}


int main(void) {
    riddle14_1("/home/nicola/Desktop/AoC2024/input_files/day14_1.txt");
    riddle14_2("/home/nicola/Desktop/AoC2024/input_files/day14_1.txt");

    return EXIT_SUCCESS;

}