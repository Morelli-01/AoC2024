//
// Created by nicola on 09/12/24.
//
#include "utils.h"

#define FREE_SPACE INT32_MAX
#define DEBUG false
using mem_space = pair<long long int, size_t>;

void riddle9_1(string file_name) {
    ifstream is(file_name);
    char tmpC;
    vector<size_t> free_space{};
    map<size_t, size_t> files{};
    int i = 0, id = 0;
    while (is.good() and (tmpC = is.get()) != EOF) {
        if (tmpC == '\n') continue;
        if (i % 2 == 0) {
            files[id] = stoi(string{tmpC});
            id++;
        } else {
            free_space.push_back(stoi(string{tmpC}));
        }
        i++;
    }
    is.close();
    vector<long long int> sequence{};
    for (int j = 0; j < files.size(); ++j) {
        for (int k = 0; k < files[j]; ++k)
            sequence.push_back(j);
        for (int k = 0; k < free_space[j]; ++k)
            sequence.push_back(FREE_SPACE);
    }

    for (long long int j = 0; j < sequence.size(); ++j) {
        if (sequence[j] == FREE_SPACE) {
            for (long long int k = j + 1; k < sequence.size(); ++k) {
                if (sequence[k] != FREE_SPACE) {
                    i = 0;
                    for (i = sequence.size() - 1; i >= 0; i--) {
                        if (sequence[i] != FREE_SPACE) break;
                    }
                    sequence[j] = sequence[i];
                    sequence[i] = FREE_SPACE;
                    j = 0;

                    break;
                }
            }

        }

    }
    size_t result = 0;
    for (i = 0; i < sequence.size(); i++) {
        auto item = sequence[i];
        if (item != FREE_SPACE)
            result += i * item;
    }
    cout << "the solution of riddle9_1 is : " << result << endl;
}

void riddle9_2(string file_name) {
    ifstream is(file_name);
    char tmpC;
    vector<size_t> free_space{};
    map<size_t, size_t> files{};
    long long int i = 0, id = 0;
    while (is.good() and (tmpC = is.get()) != EOF) {
        if (tmpC == '\n') continue;
        if (i % 2 == 0) {
            files[id] = stoi(string{tmpC});
            id++;
        } else {
            free_space.push_back(stoi(string{tmpC}));
        }
        i++;
    }
    is.close();

    vector<pair<long long int, size_t>> memory_map{};
    int upper_bound = (free_space.size() > files.size()) ? free_space.size() : files.size();
    for (size_t j = 0; j < upper_bound; ++j) {
        if (j < files.size())
            memory_map.emplace_back(j, files[j]);

        if (j < free_space.size())
            memory_map.emplace_back(FREE_SPACE, free_space[j]);

    }

    if (DEBUG) {
        for (const auto &item: memory_map) {
            if (item.first == FREE_SPACE)
                for (int j = 0; j < item.second; ++j)
                    cout << '.';
            else
                for (int j = 0; j < item.second; ++j)
                    cout << item.first;
        }
        cout << endl;
    }

    for (i = memory_map.size() - 1; i >= 0; i--) {
        mem_space item = memory_map[i];
        if (item.first == FREE_SPACE)continue;
        else {
            for (int j = 0; j < i; ++j) {
                mem_space new_space = memory_map[j];
                if (new_space.first == FREE_SPACE and new_space.second >= item.second) {
                    if (new_space.second == item.second) {
                        memory_map[i] = new_space;
                        memory_map[j] = item;
                    } else {
                        memory_map[i] = {FREE_SPACE, item.second};
                        memory_map[j] = {item.first, item.second};
                        mem_space space_left = {FREE_SPACE, new_space.second - item.second};
                        memory_map.insert(memory_map.begin() + j + 1, space_left);
                    }
                    if (DEBUG) {
                        for (const auto &item: memory_map) {
                            if (item.first == FREE_SPACE)
                                for (int j = 0; j < item.second; ++j)
                                    cout << '.';
                            else
                                for (int j = 0; j < item.second; ++j)
                                    cout << item.first;
                        }
                        cout << endl;
                    }

                    break;
                }
            }
        }
    }


    long long int result = 0;
    vector<size_t> seq{};
    for (const auto &item: memory_map) {
        if (item.first == FREE_SPACE)
            for (int j = 0; j < item.second; ++j)
                seq.push_back(0);
        else
            for (int j = 0; j < item.second; ++j)
                seq.push_back(item.first);
    }

    for (i = 0; i < seq.size(); i++) {
        result += i * seq[i];
    }
    cout << "the solution of riddle9_2 is : " << result << endl;
}


int main(void) {
    riddle9_1("/home/nicola/Desktop/AoC2024/input_files/day9_1.txt");
    riddle9_2("/home/nicola/Desktop/AoC2024/input_files/day9_1.txt");

    return EXIT_SUCCESS;
}