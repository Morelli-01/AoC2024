//
// Created by nicola on 12/12/24.
//

#include "utils.h"


struct GardenData {
    uint8_t label;
    size_t perimeter;
    size_t area;
};

void riddle12_1(string file_name) {

    ifstream is(file_name);
    size_t rows = 1;
    vector<uint8_t> data{};
    char tmpC;
    while (is.good() and (tmpC = is.get()) != EOF) {
        if (tmpC == '\n') {
            rows++;
            continue;
        }
        data.push_back(tmpC);
    }
    is.close();
    int c4_connectivity[4][2] = {
            {-1, 0},
            {0,  -1},
            {1,  0},
            {0,  1}
    };
    Mat<uint8_t> garden(rows, data.size() / rows);
    Mat<int> labels(rows, data.size() / rows, 0);
    map<int, GardenData> gardendata_map{};
    int id = 1;
    garden.data_ = data;

//    garden.print();

    for (int r = 0; r < garden.rows_; ++r)
        for (int c = 0; c < garden.cols_; ++c) {
            for (auto &[dy, dx]: c4_connectivity)
                if (r + dy < garden.rows_ and c + dx < garden.cols_)
                    if (garden[r, c] == garden[r + dy, c + dx] and labels[r + dy, c + dx] != 0)
                        labels[r, c] = labels[r + dy, c + dx];


            if (labels[r, c] == 0) {
                labels[r, c] = id;
                id++;
            }
        }

    bool smt_changed_ = true;
    while (smt_changed_) {
        smt_changed_ = false;
        for (int c = 0; c < labels.cols_; ++c)
            for (int r = 0; r < labels.rows_; ++r) {
                auto &garden_patch = garden[r, c];
                auto &garedn_label = labels[r, c];
                for (int k = 0; k < 2; ++k) {
                    auto &[dy, dx] = c4_connectivity[k];
                    if (r + dy < garden.rows_ and c + dx < garden.cols_) {
                        auto &next_garden_patch = garden[r + dy, c + dx];
                        auto &next_garedn_label = labels[r + dy, c + dx];
                        if (garden_patch == next_garden_patch and garedn_label != next_garedn_label) {
                            smt_changed_ = true;
                            garedn_label = next_garedn_label;
                            break;
                        }
                    }
                }
            }

        for (int c = labels.cols_ - 1; c >= 0; --c)
            for (int r = labels.rows_ - 1; r >= 0; --r) {
                auto &garden_patch = garden[r, c];
                auto &garedn_label = labels[r, c];
                for (int k = 2; k < 4; ++k) {
                    auto &[dy, dx] = c4_connectivity[k];
                    if (r + dy < garden.rows_ and c + dx < garden.cols_) {
                        auto &next_garden_patch = garden[r + dy, c + dx];
                        auto &next_garedn_label = labels[r + dy, c + dx];
                        if (garden_patch == next_garden_patch and garedn_label != next_garedn_label) {
                            smt_changed_ = true;
                            garedn_label = next_garedn_label;
                            break;
                        }
                    }
                }
            }
    }

    for (int r = 0; r < garden.rows_; ++r)
        for (int c = 0; c < garden.cols_; ++c) {
            if (gardendata_map.contains(labels[r, c])) gardendata_map[labels[r, c]].area++;
            else gardendata_map[labels[r, c]] = GardenData(labels[r, c], 0, 1);

            for (auto &[dy, dx]: c4_connectivity)
                if (r + dy < garden.rows_ and c + dx < garden.cols_) {
                    if (labels[r, c] != labels[r + dy, c + dx])
                        gardendata_map[labels[r, c]].perimeter++;
                } else gardendata_map[labels[r, c]].perimeter++;

        }
//    labels.print();

    size_t result = 0;
    for (auto &[label, gardendata]: gardendata_map) {
        result += gardendata.area * gardendata.perimeter;
    }
    cout << "The solution for riddle12_1 is: " << result << endl;
}


void riddle12_2(string file_name) {

    ifstream is(file_name);
    size_t rows = 1;
    vector<uint8_t> data{};
    char tmpC;
    while (is.good() and (tmpC = is.get()) != EOF) {
        if (tmpC == '\n') {
            rows++;
            continue;
        }
        data.push_back(tmpC);
    }
    is.close();
    int c4_connectivity[4][2] = {
            {-1, 0},
            {0,  -1},
            {1,  0},
            {0,  1}
    };
    int acute_angles_kernel[4][2][4] = {
            {{0, 0, 1,  1},  {0, 1,  0, 1}},
            {{0, 0, -1, -1}, {0, 1,  0, 1}},
            {{0, 0, -1, -1}, {0, -1, 0, -1}},
            {{0, 0, 1,  1},  {0, -1, 0, -1}},
    };
    Mat<uint8_t> garden(rows, data.size() / rows);
    Mat<int> labels(rows, data.size() / rows, 0);

    map<int, GardenData> gardendata_map{};
    int id = 1;
    garden.data_ = data;


    for (int r = 0; r < garden.rows_; ++r)
        for (int c = 0; c < garden.cols_; ++c) {
            for (auto &[dy, dx]: c4_connectivity)
                if (r + dy < garden.rows_ and c + dx < garden.cols_)
                    if (garden[r, c] == garden[r + dy, c + dx] and labels[r + dy, c + dx] != 0)
                        labels[r, c] = labels[r + dy, c + dx];


            if (labels[r, c] == 0) {
                labels[r, c] = id;
                id++;
            }
        }

    bool smt_changed_ = true;
    while (smt_changed_) {
        smt_changed_ = false;
        for (int c = 0; c < labels.cols_; ++c)
            for (int r = 0; r < labels.rows_; ++r) {
                auto &garden_patch = garden[r, c];
                auto &garedn_label = labels[r, c];
                for (int k = 0; k < 2; ++k) {
                    auto &[dy, dx] = c4_connectivity[k];
                    if (r + dy < garden.rows_ and c + dx < garden.cols_) {
                        auto &next_garden_patch = garden[r + dy, c + dx];
                        auto &next_garedn_label = labels[r + dy, c + dx];
                        if (garden_patch == next_garden_patch and garedn_label != next_garedn_label) {
                            smt_changed_ = true;
                            garedn_label = next_garedn_label;
                            break;
                        }
                    }
                }
            }

        for (int c = labels.cols_ - 1; c >= 0; --c)
            for (int r = labels.rows_ - 1; r >= 0; --r) {
                auto &garden_patch = garden[r, c];
                auto &garedn_label = labels[r, c];
                for (int k = 2; k < 4; ++k) {
                    auto &[dy, dx] = c4_connectivity[k];
                    if (r + dy < garden.rows_ and c + dx < garden.cols_) {
                        auto &next_garden_patch = garden[r + dy, c + dx];
                        auto &next_garedn_label = labels[r + dy, c + dx];
                        if (garden_patch == next_garden_patch and garedn_label != next_garedn_label) {
                            smt_changed_ = true;
                            garedn_label = next_garedn_label;
                            break;
                        }
                    }
                }
            }
    }

    labels.add_padding(1);
    garden.add_padding(1, EOF);

//    garden.print();
//    labels.print();

    for (int r = 0; r < garden.rows_; ++r)
        for (int c = 0; c < garden.cols_; ++c) {
            auto &garden_patch = garden[r, c];
            if (gardendata_map.contains(labels[r, c])) gardendata_map[labels[r, c]].area++;
            else gardendata_map[labels[r, c]] = GardenData(labels[r, c], 0, 1);

            for (int i = 0; i < 4; ++i) {
                auto [dy, dx] = acute_angles_kernel[i];
                if (c + dx[3] >= 0 and c + dx[3] < garden.cols_ and
                    r + dy[3] >= 0 and r + dy[3] <= garden.rows_) {
                    auto &garden_patch_opposite = garden[r + dy[3], c + dx[3]];
                    if (garden_patch != garden_patch_opposite and
                        garden[r + dy[1], c + dx[1]] == garden[r + dy[2], c + dx[2]] and
                        garden_patch == garden[r + dy[1], c + dx[1]])
                        gardendata_map[labels[r, c]].perimeter += 1;

                    if (garden_patch != garden[r + dy[1], c + dx[1]] and
                        garden_patch != garden[r + dy[2], c + dx[2]])
                        gardendata_map[labels[r, c]].perimeter += 1;

                }
            }
        }


    size_t result = 0;

    for (auto &[label, gardendata]: gardendata_map) {
        if (label == 0)continue;
        result += gardendata.area * gardendata.perimeter;
    }
    cout << "The solution for riddle12_1 is: " << result << endl;
}

int main(void) {
    riddle12_1("/home/nicola/Desktop/AoC2024/input_files/day12_1.txt");
    riddle12_2("/home/nicola/Desktop/AoC2024/input_files/day12_1.txt");

    return EXIT_SUCCESS;

}