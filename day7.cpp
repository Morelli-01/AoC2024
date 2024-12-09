//
// Created by nicola on 12/9/24.
//
#include "utils.h"

#define PLUS 0
#define MUL 1
#define CONCAT 2


using eq = vector<long long int>;

bool check_combinations(eq &eq_) {
    vector<bool> possible_op(eq_.size() - 2, PLUS);


    for (int j = 0; j < pow(2, possible_op.size()); ++j) {
        size_t partial_res = eq_[1];
        for (int i = 2; i < eq_.size(); ++i)
            partial_res = (possible_op[i - 2] == PLUS) ? partial_res + eq_[i] : partial_res * eq_[i];

        if (partial_res == eq_[0]) return true;

        for (int i = possible_op.size() - 1; i >= 0; i--) {
            possible_op[i] = !possible_op[i];
            if (possible_op[i]) break;
        }
    }


    return false;
}

bool check_combinations_2(eq &eq_) {
    vector<uint8_t> possible_op(eq_.size() - 2, PLUS);

    for (int j = 0; j < pow(3, possible_op.size()); ++j) {
        size_t partial_res = eq_[1];
        for (int i = 2; i < eq_.size(); ++i) {
            switch (possible_op[i - 2]) {
                case PLUS: {
                    partial_res += eq_[i];
                    break;
                }
                case MUL: {
                    partial_res *= eq_[i];
                    break;
                }
                case CONCAT: {
                    partial_res = stoll((to_string(partial_res) + to_string(eq_[i])).c_str());
                    break;
                }
            }
        }
//        partial_res = (possible_op[i - 2] == PLUS) ? partial_res + eq_[i] : partial_res * eq_[i];

        if (partial_res == eq_[0]) return true;

        for (int i = possible_op.size() - 1; i >= 0; i--) {
            possible_op[i] += 1;
            possible_op[i] %= 3;
            if (possible_op[i] != 0)
                break;
        }
    }

    return false;
}

void riddle7_1(string file_name) {
    ifstream is(file_name);
    vector<eq> equations{};
    char tmpC;
    string tmpStr = "";
    is >> tmpStr;
    while (is.good() and is.peek() != EOF) {
        tmpStr.pop_back();
        eq eq_{};
        eq_.push_back(stoll(tmpStr));
        tmpStr.clear();
        while (is.peek() != '\n' or is.peek() != EOF) {
            is >> tmpStr;
            if (tmpStr.contains(':'))break;
            eq_.push_back(stoi(tmpStr));
            tmpStr.clear();
            if (!is.good())break;
        }
        equations.push_back(eq_);
    }
    is.close();

    size_t result = 0;
    for (auto &eq_: equations) {
        if (check_combinations(eq_))
            result += eq_[0];
    }


    cout << "The solution to the riddle7_1 is: " << result << endl;
}

void riddle7_2(string file_name) {
    ifstream is(file_name);
    vector<eq> equations{};
    char tmpC;
    string tmpStr = "";
    is >> tmpStr;
    while (is.good() and is.peek() != EOF) {
        tmpStr.pop_back();
        eq eq_{};
        eq_.push_back(stoll(tmpStr));
        tmpStr.clear();
        while (is.peek() != '\n' or is.peek() != EOF) {
            is >> tmpStr;
            if (tmpStr.contains(':'))break;
            eq_.push_back(stoi(tmpStr));
            tmpStr.clear();
            if (!is.good())break;
        }
        equations.push_back(eq_);
    }
    is.close();

    size_t result = 0;
    for (auto &eq_: equations) {
        if (check_combinations_2(eq_))
            result += eq_[0];
    }
    cout << "The solution to the riddle7_2 is: " << result << endl;
}


int main(void) {
    riddle7_1("/home/nicola/Desktop/AoC2024/input_files/day7_1.txt");
    riddle7_2("/home/nicola/Desktop/AoC2024/input_files/day7_1.txt");
    return EXIT_SUCCESS;
}