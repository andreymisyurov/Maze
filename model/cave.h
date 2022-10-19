#ifndef SRC_MODEL_CAVE_H_
#define SRC_MODEL_CAVE_H_

#include <time.h>

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Cell {
  bool status;
  int8_t neighbours;
};

class Cave {
 public:
  Cave(int rows, int columns, int born, int dead, int random);

 public:
  auto getRows() const -> size_t { return m_field.size(); }
  auto getColumns() const -> size_t { return m_field[0].size(); }
  auto getField() const -> const vector<vector<Cell>> & { return m_field; }
  auto generateField() -> void;
  auto writeNeighbours() -> void;
  auto lifeYear() -> void;
  auto checkEquals() -> bool;
  auto static loadCave(const char *path) -> Cave;
  friend auto operator==(const vector<vector<Cell>> &that,
                         const vector<vector<Cell>> &other) -> bool;

 private:
  auto smartRandom() -> bool;
  auto killFrame() -> void;
  auto getNeighbors(int8_t i, int8_t j) -> int8_t;
  auto backUpField(const vector<vector<Cell>> &value) -> void;

 private:
  int8_t m_rows;
  int8_t m_columns;
  int8_t m_born;
  int8_t m_dead;
  int8_t m_random;
  vector<vector<Cell>> m_field;
  vector<vector<vector<Cell>>> m_base_field;
};

auto operator==(const vector<vector<Cell>> &that,
                const vector<vector<Cell>> &other) -> bool;

#endif  // SRC_MODEL_CAVE_H_
