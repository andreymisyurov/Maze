#include "Labyrinth.h"

auto Labyrinth::saveToFile(std::string value) -> void {
  std::ofstream file(value);
  file << height_ << " " << width_ << std::endl;
  for (auto &i : labyrinth_right) {
    for (auto &j : i) {
      file << j << " ";
    }
    file << std::endl;
  }
  file << std::endl;
  for (auto &i : labyrinth_bottom) {
    for (auto &j : i) {
      file << j << " ";
    }
    file << std::endl;
  }
  file.close();
}

auto Labyrinth::createLabyrinthFromFile(const std::string &filename) -> void {
  std::ifstream file(filename);
  file >> height_ >> width_;
  labyrinth_bottom.clear();
  labyrinth_right.clear();
  for (int i{}; i < height_; i++) {
    labyrinth_right.emplace_back(std::vector<int>(width_, 0));
    labyrinth_bottom.emplace_back(std::vector<int>(width_, 0));
  }
  for (auto &i : labyrinth_right) {
    for (auto &j : i) {
      file >> j;
    }
  }
  for (auto &i : labyrinth_bottom) {
    for (auto &j : i) {
      file >> j;
    }
  }
}

auto Labyrinth::createLabyrinth(int width, int height) -> void {
  width_ = width;
  height_ = height;
  most_set = 0;
  set.clear();
  labyrinth_bottom.clear();
  labyrinth_right.clear();
  set.emplace_back(std::vector<int>(width, 0));
  labyrinth_right.emplace_back(std::vector<int>(width, 0));
  labyrinth_bottom.emplace_back(std::vector<int>(width, 0));
  for (int row{}; row < height_ - 1; row++) {
    if (row != 0) {
      new_line(row);
    }
    set_unique(row);
    add_right(row);
    add_bottom(row);
    bottom_fix(row);
  }
  if (height_ > 1) {
    finish_labyrinth(height - 1);
  }
}

auto Labyrinth::set_unique(const int &row) -> void {
  for (int labyrinth_index{}; labyrinth_index < width_; labyrinth_index++) {
    if (!set[row][labyrinth_index]) {
      most_set += 1;
      set[row][labyrinth_index] = most_set;
    }
  }
}

auto Labyrinth::new_line(const int &row) -> void {
  set.emplace_back(set[row - 1]);
  labyrinth_right.emplace_back(std::vector<int>(width_, 0));
  labyrinth_bottom.emplace_back(std::vector<int>(width_, 0));
  for (int labyrinth_index{}; labyrinth_index < width_; labyrinth_index++) {
    if (labyrinth_bottom[row - 1][labyrinth_index]) {
      set[row][labyrinth_index] = 0;
    }
  }
}

auto Labyrinth::generate_random_number(const int from, const int to) -> int {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(from, to);
  return distr(gen);
}

auto Labyrinth::add_right(const int &row) -> void {
  for (int labyrinth_index{}; labyrinth_index < width_ - 1; labyrinth_index++) {
    if (generate_random_number(0, 1) ||
        set[row][labyrinth_index] == set[row][labyrinth_index + 1]) {
      labyrinth_right[row][labyrinth_index] = 1;
    } else {
      unite_set(row, labyrinth_index);
    }
  }
  labyrinth_right[row][width_ - 1] = 1;
  if (row == 0) {
    most_set = set[row][width_ - 1];
  }
}

auto Labyrinth::add_bottom(const int &row) -> void {
  for (int labyrinth_index{}; labyrinth_index < width_; labyrinth_index++) {
    int countUniqSet = 0;
    for (int i = 0; i < width_; i++) {
      if (set[row][i] == set[row][labyrinth_index]) {
        countUniqSet++;
      }
    }
    if (countUniqSet != 1 && generate_random_number(0, 1)) {
      labyrinth_bottom[row][labyrinth_index] = 1;
    }
  }
}

auto Labyrinth::bottom_fix(const int &row) -> void {
  for (int i = 0; i < width_; i++) {
    int countHorizontalWalls = 0;
    for (int j = 0; j < width_; j++) {
      if (set[row][j] == set[row][i] && !labyrinth_bottom[row][j]) {
        countHorizontalWalls++;
      }
    }
    if (countHorizontalWalls == 0) {
      labyrinth_bottom[row][i] = 0;
    }
  }
}

auto Labyrinth::unite_set(const int &row, const int &labyrinth_index) -> void {
  int mutableSet = set[row][labyrinth_index + 1];
  for (int j = 0; j < width_; j++) {
    if (set[row][j] == mutableSet) {
      set[row][j] = set[row][labyrinth_index];
    }
  }
}

auto Labyrinth::finish_labyrinth(const int &row) -> void {
  new_line(row);
  set_unique(row);
  add_right(row);
  for (int labyrinth_index{}; labyrinth_index < width_ - 1; labyrinth_index++) {
    if (set[row][labyrinth_index] != set[row][labyrinth_index + 1]) {
      labyrinth_right[row][labyrinth_index] = 0;
      unite_set(row, labyrinth_index);
    }
    labyrinth_bottom[row][labyrinth_index] = 1;
  }
  labyrinth_bottom[row][width_ - 1] = 1;
}
auto Labyrinth::getLabyrinth() const
    -> std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> {
  return std::make_pair(labyrinth_right, labyrinth_bottom);
}
