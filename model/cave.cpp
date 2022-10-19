#include "cave.h"

#include <algorithm>
#include <iterator>

Cave::Cave(int rows, int columns, int cellForBorn, int cellForDead,
           int chanceForBorn) {
  if (rows < 1 || rows > 50) throw runtime_error("incorrect rows");
  if (columns < 1 || columns > 50) throw runtime_error("incorrect columns");
  if (cellForDead > 7 || cellForDead < 0)
    throw runtime_error("neighbours dead incorrect");
  if (cellForBorn > 7 || cellForBorn < 0)
    throw runtime_error("neighbours born incorrect");
  if (chanceForBorn < 0 || chanceForBorn > 100)
    throw runtime_error("incorrect chance for born");

  m_random = chanceForBorn;
  m_born = cellForBorn;
  m_dead = cellForDead;
  m_rows = rows + 2;
  m_columns = columns + 2;
  m_field = vector<vector<Cell>>(m_rows);
  fill(m_field.begin(), m_field.end(), vector<Cell>(m_columns));
}

auto Cave::smartRandom() -> bool {
  auto value = rand() % 100;
  return m_random - value > 0;
}

auto Cave::generateField() -> void {
  srand(time(0));
  for (auto &&row : m_field) {
    for (auto &&elem : row) {
      elem.neighbours = 0;
      elem.status = smartRandom();
    }
  }
}

auto Cave::killFrame() -> void {
  auto zero_out = [](Cell value) -> Cell {
    value.status = true;
    value.neighbours = 0;
    return value;
  };
  for (auto &&el : m_field.front()) el = zero_out(el);
  for (auto el = m_field.begin() + 1; el != m_field.end() - 1; ++el) {
    (*el).front() = zero_out((*el).front());
    (*el).back() = zero_out((*el).back());
  }
  for (auto &&el : m_field.back()) el = zero_out(el);
}

auto Cave::getNeighbors(int8_t i, int8_t j) -> int8_t {
  int8_t result = 0, l = -1, k = -1;
  for (l = -1; l <= 1; ++l) {
    for (k = -1; k <= 1; ++k) {
      if (l == 0 && k == 0) continue;
      result += m_field.at(i + l).at(j + k).status;
    }
  }
  return result;
}

auto Cave::writeNeighbours() -> void {
  killFrame();
  for (size_t i = 1, l = m_field.size() - 1; i < l; ++i) {
    for (size_t j = 1, k = m_field[0].size() - 1; j < k; ++j) {
      m_field.at(i).at(j).neighbours = getNeighbors(i, j);
    }
  }
}

auto Cave::backUpField(const vector<vector<Cell>> &value) -> void {
  m_base_field.push_back(value);
  if (static_cast<int>(m_base_field.size()) > (m_rows + m_columns) * 10) {
    m_base_field.erase(m_base_field.begin());
  }
}

auto Cave::lifeYear() -> void {
  backUpField(m_field);
  for (auto &&row : m_field) {
    for (auto &&cell : row) {
      if (!cell.status && cell.neighbours > m_born)
        cell.status = true;
      else if (cell.status && cell.neighbours < m_dead)
        cell.status = false;
    }
  }
}

auto Cave::checkEquals() -> bool {
  return any_of(
      m_base_field.begin(), m_base_field.end(),
      [this](const vector<vector<Cell>> &el) { return el == m_field; });
}

auto operator==(const vector<vector<Cell>> &that,
                const vector<vector<Cell>> &other) -> bool {
  for (int i = 0, l = that.size(); i < l; ++i) {
    for (int j = 0, k = that[0].size(); j < k; ++j) {
      if (that.at(i).at(j).status != other.at(i).at(j).status) return false;
    }
  }
  return true;
}

auto Cave::loadCave(const char *path) -> Cave {
  ifstream in(path);
  if (!in.is_open()) throw runtime_error("bad parse");

  int rows = 0, columns = 0, born = 0, dead = 0;
  string line;

  getline(in, line);
  int check = sscanf(line.c_str(), "%d %d", &rows, &columns);
  if (check != 2) throw runtime_error("bad parse");

  getline(in, line);
  int flag = sscanf(line.c_str(), "%d %d", &born, &dead);
  if (flag != 2) throw runtime_error("bad parse");

  Cave result(rows, columns, born, dead, 50);

  for (int i = 1; i < rows + 1; ++i) {
    std::getline(in, line);
    for (int j = 1; j < columns + 1; ++j) {
      result.m_field[i].at(j).status = atoi(line.c_str());
      line.erase(0, 2);
    }
  }
  return result;
}
