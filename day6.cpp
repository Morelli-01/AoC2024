//
// Created by nicola on 12/6/24.
//

#include "utils.h"

#define DIRECTION_MAP (map<uint8_t, pair<int8_t, int8_t>>{{'^',{-1, 0}}, {'>',{0, 1} }, {'v', {1,0}}, {'<', {0, -1}} })
using crd = pair<size_t, size_t>;


bool move(Mat<uint8_t> &puzzle, pair<size_t, size_t> &prev_pos) {
    uint8_t guard = puzzle[prev_pos.first, prev_pos.second];
    puzzle[prev_pos.first, prev_pos.second] = 'X';
    bool is_moved = false;
    while (not is_moved) {
        auto guard_dir = DIRECTION_MAP[guard];
        if (puzzle[prev_pos.first + guard_dir.first, prev_pos.second + guard_dir.second] != '#') {
            prev_pos.first += guard_dir.first;
            prev_pos.second += guard_dir.second;
            if (prev_pos.first >= puzzle.rows_ or prev_pos.second >= puzzle.cols_ or
                prev_pos.first < 0 or prev_pos.second < 0)
                return false;
            puzzle[prev_pos.first, prev_pos.second] = guard;
            is_moved = true;
        } else {
            if (guard == '^') guard = '>';
            else if (guard == '>') guard = 'v';
            else if (guard == 'v') guard = '<';
            else if (guard == '<') guard = '^';
        }
    }
    return prev_pos.first <= puzzle.rows_ and prev_pos.second <= puzzle.cols_ and prev_pos.first >= 0 and
           prev_pos.second >= 0;
}

bool move_2(Mat<uint8_t> &puzzle, pair<size_t, size_t> &prev_pos, uint8_t &prev_char, vector<crd> &possible_locations) {
    uint8_t guard = puzzle[prev_pos.first, prev_pos.second];
    puzzle[prev_pos.first, prev_pos.second] = 'X';
    if (prev_char == '.')
        puzzle[prev_pos.first, prev_pos.second] = (guard == '^' or guard == 'v') ? '|' : '-';
    else if (prev_char == '|')
        puzzle[prev_pos.first, prev_pos.second] = (guard == '^' or guard == 'v') ? prev_char : '+';
    else
        puzzle[prev_pos.first, prev_pos.second] = (guard == '^' or guard == 'v') ? '+' : prev_char;

    bool is_moved = false;
    auto guard_dir = DIRECTION_MAP[guard];
    while (not is_moved) {
        guard_dir = DIRECTION_MAP[guard];
        if (puzzle[prev_pos.first + guard_dir.first, prev_pos.second + guard_dir.second] != '#') {
            prev_pos.first += guard_dir.first;
            prev_pos.second += guard_dir.second;
            prev_char = puzzle[prev_pos.first, prev_pos.second];
            puzzle[prev_pos.first, prev_pos.second] = guard;
            is_moved = true;
        } else {
            if (guard == '^') guard = '>';
            else if (guard == '>') guard = 'v';
            else if (guard == 'v') guard = '<';
            else if (guard == '<') guard = '^';
            puzzle[prev_pos.first, prev_pos.second] = '+';
        }
    }
    if (puzzle[prev_pos.first - guard_dir.first, prev_pos.second - guard_dir.second] == '+')
        possible_locations.push_back(prev_pos);
    return prev_pos.first <= puzzle.rows_ and prev_pos.second < puzzle.cols_;
}

bool check_loop(crd &pos_to_check, Mat<uint8_t> &&puzzle, size_t max_iter, crd start_pos) {
    puzzle[pos_to_check.first, pos_to_check.second] = 'O';
    size_t n_iters = 0;
    puzzle.print();
    puzzle[pos_to_check.first, pos_to_check.second] = '#';

    while (move(puzzle, start_pos)) {
//        puzzle.print();
        n_iters++;
        if (n_iters >= 2 * max_iter) {
            puzzle.print();
            return true;
        }
    }
    return false;
}

void riddle6_1(string file_name) {
    ifstream is(file_name);
    size_t rows = 1, cols = 0;
    vector<uint8_t> data{};
    char tmpC;
    pair<size_t, size_t> start_pos{0, 0};
    while (is.good() and is.peek() != EOF) {
        tmpC = is.get();
        if (tmpC == '\n') {
            rows++;
            cols = 0;
            continue;
        }
        if (tmpC == '^') {
            start_pos = {rows - 1, cols};
        }
        cols++;
        data.push_back(tmpC);
    }
    is.close();
    Mat<uint8_t> puzzle(rows, cols);
    puzzle.data_ = move(data);
    puzzle.print();
    while (move(puzzle, start_pos));
//        puzzle.print();

    size_t cnt = 0;
    for (auto &e: puzzle.data_)
        if (e == 'X')cnt++;
    cout << "the solution of riddle6_1 is: " << cnt << endl;
}

void riddle6_2(string file_name) {
    ifstream is(file_name);
    size_t rows = 1, cols = 0;
    vector<uint8_t> data{};
    char tmpC;
    pair<size_t, size_t> start_pos{0, 0};
    while (is.good() and is.peek() != EOF) {
        tmpC = is.get();
        if (tmpC == '\n') {
            rows++;
            cols = 0;
            continue;
        }
        if (tmpC == '^') {
            start_pos = {rows - 1, cols};
        }
        cols++;
        data.push_back(tmpC);
    }
    is.close();
    pair<size_t, size_t> start_pos2 = start_pos;

    Mat<uint8_t> puzzle(rows, cols);
    puzzle.data_ = move(data);
    uint8_t prev_char = '.';
    vector<crd> possibile_locations{};
    auto initial_puzzle = puzzle.copy();

    size_t move_cnt = 0;
    while (move_2(puzzle, start_pos, prev_char, possibile_locations))
        move_cnt++;

    for (const auto &item: possibile_locations){
        initial_puzzle[item.first, item.second] = 'O';
    }
    initial_puzzle.print();

//    for (auto &item: possibile_locations) {
//        if (check_loop(item, initial_puzzle.copy(), move_cnt, start_pos2)) {
//            puzzle[item.first, item.second] = 'O';
//            cout << "Good loop\n";
//        } else {
//            cout << "Bad loop\n";
//        }
//    }

    puzzle.print();
    size_t cnt = 0;
    for (auto &e: puzzle.data_)
        if (e == 'O')cnt++;
    cout << "the solution of riddle6_2 is: " << cnt << endl;
}


int main(void) {
    riddle6_1("/home/nicola/Desktop/AoC2024/input_files/day6_1.txt");
    riddle6_2("/home/nicola/Desktop/AoC2024/input_files/day6_1.txt");

    return EXIT_SUCCESS;
}


