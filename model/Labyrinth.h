#ifndef SRC_MODEL_LABYRINTH_H_
#define SRC_MODEL_LABYRINTH_H_

#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

class Labyrinth {
 public:
  void createLabyrinth(int width, int height);
  [[nodiscard]] auto getLabyrinth() const
      -> std::pair<std::vector<std::vector<int>>,
                   std::vector<std::vector<int>>>;

  auto createLabyrinthFromFile(const std::string& filename) -> void;
  auto saveToFile(std::string value) -> void;

 private:
  auto generate_random_number(int from, int to) -> int;

  auto new_line(const int& row) -> void;
  auto set_unique(const int& row) -> void;
  auto add_right(const int& row) -> void;
  auto add_bottom(const int& row) -> void;

  auto unite_set(const int& row, const int& labyrinth_index) -> void;
  auto finish_labyrinth(const int& row) -> void;

 private:
  int most_set{};
  std::vector<std::vector<int>> labyrinth_right{};
  std::vector<std::vector<int>> labyrinth_bottom{};
  std::vector<std::vector<int>> set{};
  int width_{};
  int height_{};

  void bottom_fix(const int& row);
};

#endif  // SRC_MODEL_LABYRINTH_H_
