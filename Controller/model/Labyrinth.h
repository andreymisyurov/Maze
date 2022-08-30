//
// Created by Emery Reva on 8/13/22.
//

#ifndef LABYRINTH_MODEL_LABYRINTH_H_
#define LABYRINTH_MODEL_LABYRINTH_H_

#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <cstdio>

class Labyrinth {
public:
    void createLabyrinth(int width, int height) {
        width_ = width;
        height_ = height;
        set.emplace_back(*new std::vector<int>(width));
        labyrinth_right.emplace_back(*new std::vector<int>(width));
        labyrinth_bottom.emplace_back(*new std::vector<int>(width));
        std::iota(set[0].begin(), set[0].end(), 1);
        add_right(0);
        add_bottom(0);
        for (int row{1}; row < height_; row++) {
            labyrinth_right.emplace_back(*new std::vector<int>(width_));
            labyrinth_bottom.emplace_back(*new std::vector<int>(labyrinth_bottom[row - 1]));
            set.emplace_back(*new std::vector<int>(set[row-1]));
            for (int labyrinth_index {}; labyrinth_index < width_; labyrinth_index++) {
                if (labyrinth_bottom[row][labyrinth_index] == 1) {
                    labyrinth_bottom[row][labyrinth_index] = 0;
                    most_set += 1;
                    set[row][labyrinth_index] = most_set;
                }
            }
            add_right(row);
            add_bottom(row);
            if (row == height - 1) {
                finish_labyrinth(row);
            }
        }
    }

    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> getLabyrinth() const{
        return std::make_pair(labyrinth_right, labyrinth_bottom);
    }

private:
    int generate_random_number(int from, int to);
    void add_right(int row);
    void add_bottom(int row);
    void finish_labyrinth(int row);
    int most_set{};
    std::vector<std::vector<int>> labyrinth_right{};
    std::vector<std::vector<int>> labyrinth_bottom{};
    std::vector<std::vector<int>> set{};
    int width_{};
    int height_{};
};



#endif //LABYRINTH_MODEL_LABYRINTH_H_
