#include <time.h>

#include <algorithm>
#include <cstdint>
#include <exception>
#include <iostream>
#include <vector>
using namespace std;

struct Cell {
  bool status;
  int neighbours;
};

class Cave {
 public:
  Cave(int size, int burn, int dead);

  auto generateField() -> void;
  auto killFrame() -> void;
  auto getNeighbords(int i, int j) -> int;
  auto writeNeighbours() -> void;
  auto lifeYear() -> void;
  auto checkEquals() -> bool;

  auto printField() -> void;
  auto showBase() -> bool;
  friend auto operator==(const vector<vector<Cell>>& other2,
                         const vector<vector<Cell>>& other) -> bool const;

 public:
  vector<vector<Cell>> m_field;
  int m_size;
  int m_burn;
  int m_dead;
  vector<vector<vector<Cell>>> m_base_field;
};

auto operator==(const vector<vector<Cell>>& other2,
                const vector<vector<Cell>>& other) -> bool const;
