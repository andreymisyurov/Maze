//
// Created by Emery Reva on 8/13/22.
//

#include "Labyrinth.h"

int Labyrinth::generate_random_number(const int from, const int to) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(from, to);
  return distr(gen);
}

void Labyrinth::add_right(const int row) {
  int last_index {};
  for (int labyrinth_index {}; labyrinth_index < width_; labyrinth_index++) {
    if (generate_random_number(0, 1)) {
      labyrinth_right[row][labyrinth_index] = 1;
      set[row][labyrinth_index] = set[row][last_index];
      last_index = labyrinth_index + 1;
    } else if (labyrinth_index != width_ - 1 && set[row][labyrinth_index] == set[row][labyrinth_index + 1]) {
      labyrinth_right[row][labyrinth_index] = 1;
      set[row][labyrinth_index] = set[row][last_index];
      last_index = labyrinth_index + 1;
    } else {
      set[row][labyrinth_index] = set[row][last_index];
    }
  }
  labyrinth_right[row][width_ - 1] = 1;
  if (row == 0) {
    most_set = set[row][width_ - 1];
  }
}

void Labyrinth::add_bottom(const int row) {
  bool isExit{false};
  for (int labyrinth_index {}; labyrinth_index < width_; labyrinth_index++) {
    if (!generate_random_number(0, 1)) {
      isExit = true;
    } else if (!(!isExit && labyrinth_right[row][labyrinth_index] == 1)) {
      labyrinth_bottom[row][labyrinth_index] = 1;
    }
    if (labyrinth_right[row][labyrinth_index] == 1) isExit = false;
  }
}

void Labyrinth::finish_labyrinth(int row) {
  for (int labyrinth_index {}; labyrinth_index < width_; labyrinth_index++) {
    if (labyrinth_index != width_ - 1 && set[row][labyrinth_index] != set[row][labyrinth_index + 1]) {
      labyrinth_right[row][labyrinth_index] = 0;
//      set[row][labyrinth_index + 1] = set[row][labyrinth_index];
    }
  }
}
