//
// Created by nicola on 1/4/25.
//

#include "utils.h"

using crd = pair<int, int>;

void move_(Mat<uint8_t> &grid, uint8_t move, crd &robot_pos, map<char, crd> &rules) {
    const auto [dy, dx] = rules[move];
    const auto [y, x] = robot_pos;
    for (int i = 1;; ++i) {
        auto item_ = grid[y + dy * i, x + dx * i];
        if (item_ == '#')return;
        if (item_ == '.') {
            for (int j = i; j > 0; --j) {
                swap(grid[y + dy * j, x + dx * j], grid[y + dy * (j - 1), x + dx * (j - 1)]);
            }
            robot_pos.first += dy;
            robot_pos.second += dx;
            return;
        }
    }
}

bool special_move(Mat<uint8_t> &grid, uint8_t move, vector<crd> &&pos, map<char, crd> &rules) {
    const auto [dy, dx] = rules[move];
    set<crd> new_pos{};

    for (auto [y, x]: pos) {
        switch (grid[y + dy, x + dx]) {
            case '.':
                break;
            case '[': {
                new_pos.emplace(y + dy, x + dx);
                new_pos.emplace(y + dy, x + dx + 1);
                break;
            }
            case ']': {
                new_pos.emplace(y + dy, x + dx);
                new_pos.emplace(y + dy, x + dx - 1);
                break;
            }
            case '#':
                return false;
        }
    }

    if (!pos.empty()) if (!special_move(grid, move, vector<crd>{new_pos.begin(), new_pos.end()}, rules)) return false;

    for (auto &[y, x]: pos) {
        swap(grid[y, x], grid[y + dy, x + dx]);
    }
    return true;
}

Mat<uint8_t> read_grid(ifstream &is) {
    size_t rows = 0;
    vector<uint8_t> tmp_data{};
    char tmp = 0;
    while (tmp != '\n' or is.peek() != '\n') {
        tmp = is.get();
        if (tmp == '\n') rows++;
        else tmp_data.push_back(tmp);
    }

    is.get();
    Mat<uint8_t> grid(rows, tmp_data.size() / rows);
    grid.data_ = tmp_data;
    return grid;
}

vector<char> read_moves(ifstream &is) {
    vector<char> moves{};
    while (is.good() and is.peek() != EOF) {
        if (is.peek() != '\n')
            moves.emplace_back(is.get());
        else is.get();
    }
    return moves;
}

void riddle15_1(const string &file_name) {
    map<char, crd> rules{};
    rules['^'] = {-1, 0};
    rules['>'] = {0, +1};
    rules['<'] = {0, -1};
    rules['v'] = {+1, 0};
    ifstream is(file_name);

    crd robot_pos(0, 0);
    Mat<uint8_t> grid = read_grid(is);
    //    print(grid);

    for (int r = 0; r < grid.rows_; ++r)
        for (int c = 0; c < grid.cols_; ++c)
            if (grid[r, c] == '@') {
                robot_pos.first = r;
                robot_pos.second = c;
                break;
            }

    vector<char> moves = read_moves(is);
    is.close();
    for (auto &move: moves) {
        move_(grid, move, robot_pos, rules);
    }
    //    print(grid);


    size_t result = 0;
    for (int r = 0; r < grid.rows_; ++r) {
        for (int c = 0; c < grid.cols_; ++c) {
            if (grid[r, c] == 'O') {
                result += r * 100 + c;
            }
        }
    }
    cout << "The solution to riddle15_1 is: " << result << endl;
}

void edit_grid(Mat<uint8_t> &grid) {
    Mat<uint8_t> new_grid(grid.rows_, grid.cols_ * 2);
    for (int r = 0; r < grid.rows_; ++r) {
        for (int c = 0; c < grid.cols_; ++c) {
            if (grid[r, c] == '#') {
                new_grid[r, c * 2] = '#';
                new_grid[r, c * 2 + 1] = '#';
            } else if (grid[r, c] == 'O') {
                new_grid[r, c * 2] = '[';
                new_grid[r, c * 2 + 1] = ']';
            } else if (grid[r, c] == '.') {
                new_grid[r, c * 2] = '.';
                new_grid[r, c * 2 + 1] = '.';
            } else if (grid[r, c] == '@') {
                new_grid[r, c * 2] = '@';
                new_grid[r, c * 2 + 1] = '.';
            }
        }
    }
    grid = new_grid;
}

void update_pos(crd &old_pos, Mat<uint8_t> &grid) {
    auto &[y, x] = old_pos;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (grid[y + i,x + j] == '@')
                old_pos = {y + i, x + j};
        }
    }
}

void riddle15_2(const string &file_name) {
    map<char, crd> rules{};
    rules['^'] = {-1, 0};
    rules['>'] = {0, +1};
    rules['<'] = {0, -1};
    rules['v'] = {+1, 0};
    ifstream is(file_name);

    crd robot_pos(0, 0);
    Mat<uint8_t> grid = read_grid(is);
    edit_grid(grid);
    print(grid);

    for (int r = 0; r < grid.rows_; ++r)
        for (int c = 0; c < grid.cols_; ++c)
            if (grid[r, c] == '@') {
                robot_pos.first = r;
                robot_pos.second = c;
                break;
            }

    vector<char> moves = read_moves(is);
    is.close();
    for (auto &move: moves) {
        if (move == '<' or move == '>')
            move_(grid, move, robot_pos, rules);
        else {
            special_move(grid, move, vector{robot_pos}, rules);
            update_pos(robot_pos, grid);
        }
    }
    print(grid);


    size_t result = 0;
    for (int r = 0; r < grid.rows_; ++r) {
        for (int c = 0; c < grid.cols_; ++c) {
            if (grid[r, c] == '[') {
                result += r * 100 + c;
            }
        }
    }
    cout << "The solution to riddle15_1 is: " << result << endl;
}

int main(void) {
    riddle15_1("/home/nicola/Desktop/AoC2024/input_files/day15_1.txt");
    riddle15_2("/home/nicola/Desktop/AoC2024/input_files/day15_1.txt");

    return EXIT_SUCCESS;
}
