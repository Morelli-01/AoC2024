//
// Created by nicola on 1/7/25.
//
#include "utils.h"
#include <thread>
#include "omp.h"
using pos = pair<size_t, size_t>;


struct Point {
    size_t row, col, dir;

    bool operator ==(Point &rhs) const {
        if (row == col)
            return true;
        return false;
    }

    bool operator <(const Point &p) const {
        return row < p.row || (row == p.row && col < p.col) || (row == p.row && col == p.col && dir < p.dir);
    }
};

constexpr array<Point, 4> directions{
    Point(0, 1, 0),
    Point(1, 0, 1),
    Point(0, -1, 2),
    Point(-1, 0, 3)
};

struct ComparePointScore {
    bool operator()(const pair<Point, size_t> &lhs, const pair<Point, size_t> &rhs) const {
        return lhs.second >= rhs.second;
    }
};


Mat<uint8_t> parse_maze(ifstream &is) {
    vector<uint8_t> data{};
    size_t rows = 1;
    char tmp;
    while (is.good() and (tmp = is.get()) != EOF) {
        if (tmp == '\n') {
            rows++;
            continue;
        }
        data.emplace_back(tmp);
    }
    Mat<uint8_t> maze(rows, data.size() / rows);
    maze.data_ = data;
    return maze;
}

void get_min_idx(const vector<size_t> &spt, vector<size_t> &idxs) {
    size_t min_idx = 0, i = 0;
    size_t min_ = spt[min_idx];
    for (size_t data: spt) {
        if (data < min_) {
            if (!ranges::contains(idxs, i)) {
                min_ = data;
                min_idx = i;
            }
        }
        i++;
    }
    idxs.emplace_back(min_idx);
}

void update_distances(Mat<uint8_t> &maze, size_t r, size_t c, vector<size_t> &spt) {
    char actual_dir = 'E';
    size_t last_idx = r * maze.cols_ + c;
    map<char, pair<int8_t, int8_t> > directions{
        {'E', {0, +1}},
        {'N', {-1, 0}},
        {'S', {+1, 0}},
        {'W', {0, -1}},
    };
    for (auto &[dir, dydx]: directions) {
        auto &[dy, dx] = dydx;
        if (maze[r - dy, c - dx] == 'S')actual_dir = dir;
    }

    for (auto &[dir, dydx]: directions) {
        auto &[dy, dx] = dydx;
        if (maze[r + dy, c + dx] == '#' or maze[r + dy, c + dx] == 'S')continue;

        if (dir == actual_dir) {
            spt[(r + dy) * maze.cols_ + (c + dx)] = spt[last_idx] + 1;
        } else {
            spt[(r + dy) * maze.cols_ + (c + dx)] = spt[last_idx] + 1001;
        }
    }
}

size_t dijkstra_algo(Mat<uint8_t> &maze) {
    vector<size_t> spt(maze.rows_ * maze.cols_, UINT64_MAX);
    size_t i = 0, end_idx;
    char direction = 'E';
    for (uint8_t e: maze.data_) {
        if (e == 'S') {
            spt[i] = 0;
        }
        if (e == 'E') {
            end_idx = i;
        }
        i++;
    }
    vector<size_t> paths{};
    while (!ranges::contains(paths, end_idx)) {
        get_min_idx(spt, paths);
        size_t min_idx = paths.back();

        size_t r = min_idx / maze.cols_;
        size_t c = min_idx % maze.cols_;
        maze.data_[min_idx] = 'S';
        // std::system("clear");
        // print(maze);
        update_distances(maze, r, c, spt);
    }
    return spt[end_idx];
}

void riddle16_1(const string &file_name) {
    ifstream is(file_name);
    Mat maze = parse_maze(is);
    is.close();

    cout << "The solution to riddle16_1 is: " << dijkstra_algo(maze) << endl;
}

void riddle16_1_2(const string &file_name) {
    ifstream is(file_name);
    Mat maze = parse_maze(is);
    Mat visual_maze = maze;
    is.close();
    priority_queue<pair<Point, size_t>, vector<pair<Point, size_t> >, ComparePointScore> live_positions{};
    // set<pair<Point, size_t>, ComparePointScore> live_positions{};
    set<Point> visited{};
    Point start_point(0, 0, 0), end_point(0, 0, 0);
    for (size_t r = 0; r < maze.rows_; r++) {
        for (size_t c = 0; c < maze.cols_; c++) {
            if (maze[r, c] == 'S') {
                start_point.row = r;
                start_point.col = c;
            }
            if (maze[r, c] == 'E') {
                end_point.row = r;
                end_point.col = c;
            }
        }
    }

    live_positions.emplace(start_point, 0);
    size_t result = 0;
    while (live_positions.size() != 0) {
        // pair<Point, size_t> &[p, s] = live_positions.top();
        pair<Point, size_t> tmp = live_positions.top();
        live_positions.pop();
        auto &[p, s] = tmp;
        visited.emplace(p.row, p.col, 0);
        if (maze[p.row, p.col] == 'E') {
            result = s;
            break;
        }

        for (auto &d: directions) {
            if (maze[p.row + d.row, p.col + d.col] != '#' and !visited.contains(
                    Point(Point(p.row + d.row, p.col + d.col, 0)))) {
                if ((p.dir + 2) % 4 == d.dir)continue;
                if (p.dir == d.dir) {
                    live_positions.emplace(Point(p.row + d.row, p.col + d.col, d.dir), s + 1);
                    visual_maze[p.row + d.row, p.col + d.col] = 'S';
                } else {
                    live_positions.emplace(Point(p.row + d.row, p.col + d.col, d.dir), s + 1001);
                    visual_maze[p.row + d.row, p.col + d.col] = 'S';
                }
            }
        }
        // std::system("clear");
        // print(visual_maze);
    }
    cout << "The solution to riddle16_1_2 is: " << result << endl;
}

int main(void) {

    Timer t("riddle16_2");
    t.start();
    riddle16_1_2("/home/nicola/Desktop/AoC2024/input_files/day16_1.txt");
    // riddle16_1("/home/nicola/Desktop/AoC2024/input_files/day16_1.txt");
    // riddle16_2("/home/nicola/Desktop/AoC2024/input_files/day16_1.txt");
    t.stop();
    return EXIT_SUCCESS;
}
