//
// Created by nicola on 25/12/24.
//

#include "utils.h"
#include "omp.h"

#define TOKEN_A_COST 3
#define TOKEN_B_COST 1
#define POS_OFFSET 10000000000000
struct Button {
    size_t dy, dx;
};

struct Arcade {
    Button A, B;
    size_t prize_y, prize_x;
    size_t sol_A, sol_B;
    bool solution_found;
};

void find_solution(Arcade &ar_) {
    size_t tmp_x_sol = 0, tmp_y_sol = 0;
    size_t sol_A = 0, sol_B = 0;

    for (size_t a = 0; not ar_.solution_found; ++a) {
        tmp_x_sol = a * ar_.A.dx + 0 * ar_.B.dx;
        tmp_y_sol = a * ar_.A.dy + 0 * ar_.B.dy;
        if (tmp_y_sol == ar_.prize_y and tmp_x_sol == ar_.prize_x) {
            ar_.solution_found = true;
            ar_.sol_A = a;
            ar_.sol_B = 0;
        }
        if (tmp_x_sol > ar_.prize_x or tmp_y_sol > ar_.prize_y)break;
        for (size_t b = 0; not ar_.solution_found; ++b) {
            tmp_x_sol = a * ar_.A.dx + b * ar_.B.dx;
            tmp_y_sol = a * ar_.A.dy + b * ar_.B.dy;
            if (tmp_y_sol == ar_.prize_y and tmp_x_sol == ar_.prize_x) {
                ar_.solution_found = true;
                ar_.sol_A = a;
                ar_.sol_B = b;
            }
            if (tmp_x_sol > ar_.prize_x or tmp_y_sol > ar_.prize_y)break;
        }
    }

}

void find_solution2(Arcade &ar_) {

    size_t a = 0;
    size_t sol_B_max = min(ceil((double) ar_.prize_x / ar_.B.dx), ceil((double) ar_.prize_y / ar_.B.dy));

#pragma omp simd
    for (long int b = sol_B_max; b >= 0; --b) {
        size_t tmp_x_sol = a * ar_.A.dx + b * ar_.B.dx;
        size_t tmp_y_sol = a * ar_.A.dy + b * ar_.B.dy;

        while (tmp_x_sol < ar_.prize_x and tmp_y_sol < ar_.prize_y) {
            a++;
            tmp_x_sol += ar_.A.dx;
            tmp_y_sol += ar_.A.dy;
        }

        if (tmp_y_sol == ar_.prize_y and tmp_x_sol == ar_.prize_x) {
            ar_.solution_found = true;
            ar_.sol_A = a;
            ar_.sol_B = b;
            b = -1;
//            break;
        }
    }
    cout << "arcade done!" << endl;
}

void riddle13_1(string file_name) {
    vector<Arcade> arcades{};
    ifstream is(file_name);

    while (is.good() and is.peek() != EOF) {
        Arcade ar_(Button(0, 0), Button(0, 0), 0, 0, 0, 0, false);
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.A.dx;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.A.dy;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.B.dx;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.B.dy;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.prize_x;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.prize_y;

        arcades.push_back(ar_);
    }

#pragma omp parallel for
    for (int i = 0; i < arcades.size(); ++i) {
        find_solution2(arcades[i]);
    }

    size_t result = 0;
    for (auto &item: arcades) {
        if (item.solution_found) {
            result += TOKEN_A_COST * item.sol_A;
            result += TOKEN_B_COST * item.sol_B;
        }
    }
    cout << "The solution to riddle13_1 is: " << result << endl;
}

void riddle13_2(string file_name) {
    vector<Arcade> arcades{};
    ifstream is(file_name);

    while (is.good() and is.peek() != EOF) {
        Arcade ar_(Button(0, 0), Button(0, 0), 0, 0, 0, 0, false);
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.A.dx;
        ar_.A.dx;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.A.dy;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.B.dx;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.B.dy;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.prize_x;
        ar_.prize_x += POS_OFFSET;
        while (is.peek() < 48 or is.peek() > 57) is.get();
        is >> ar_.prize_y;
        ar_.prize_y += POS_OFFSET;

        arcades.push_back(ar_);
    }

#pragma omp parallel for
    for (auto &item: arcades) {
        find_solution2(item);
    }

    size_t result = 0;
    for (auto &item: arcades) {
        if (item.solution_found) {
            result += TOKEN_A_COST * item.sol_A;
            result += TOKEN_B_COST * item.sol_B;
        }
    }
    cout << "The solution to riddle13_1 is: " << result << endl;
}

int main(void) {
    riddle13_1("/home/nicola/Desktop/AoC2024/input_files/day13_1.txt");
    riddle13_2("/home/nicola/Desktop/AoC2024/input_files/day13_1.txt");

    return EXIT_SUCCESS;
}