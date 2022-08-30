#include "cave.h"

Cave::Cave(int size, int burn, int dead) {
  if (size < 1 || size > 50) throw runtime_error("size below one");
  if (dead > 8 || dead < 0) throw runtime_error("neighboards dead incorrect");
  if (burn > 8 || burn < 0) throw runtime_error("neighboards burn incorrect");
  // весьма сомнительная Линия Калба
  m_field = vector<vector<Cell>>(size + 2);
  m_size = size;
  m_burn = burn;
  m_dead = dead;
  for (auto &row : m_field) {
    row = vector<Cell>(size + 2);
  }
}

auto Cave::generateField() -> void {
  srand(time(0));
  for (auto &row : m_field) {
    for (auto &elem : row) {
      elem.neighbours = 0;
      elem.status = rand() & 1;
    }
  }
}

auto Cave::killFrame() -> void {
  auto zero_out = [](Cell value) -> Cell {value.status = 1; value.neighbours = 0; return value; };
  for (auto &el : m_field.front()) el = zero_out(el);
  for (auto el = m_field.begin() + 1; el != m_field.end() - 1; ++el) {
    (*el).front() = zero_out((*el).front());
    (*el).back() = zero_out((*el).back());
  }
  for (auto &el : m_field.back()) el = zero_out(el);
}

auto Cave::getNeighbords(int i, int j) -> int {
  int result = 0;
  // слева справа
  result += m_field.at(i).at(j - 1).status;
  result += m_field.at(i).at(j + 1).status;
  // cверху
  result += m_field.at(i - 1).at(j - 1).status;
  result += m_field.at(i - 1).at(j).status;
  result += m_field.at(i - 1).at(j + 1).status;
  // снизу
  result += m_field.at(i + 1).at(j - 1).status;
  result += m_field.at(i + 1).at(j).status;
  result += m_field.at(i + 1).at(j + 1).status;
  return result;
}

auto Cave::writeNeighbours() -> void {
  for (size_t i = 1, l = m_field.size() - 1; i < l; ++i) {
    for (size_t j = 1; j < l; ++j) {
      m_field.at(i).at(j).neighbours = getNeighbords(i, j);
    }
  }
}

auto Cave::lifeYear() -> void {
  m_base_field.push_back(m_field);

  if (m_base_field.size() > m_size * 20) {
    m_base_field.erase(m_base_field.begin());
  }

  for (auto &&row : m_field) {
    // игра в жись
    // for (auto &&cell : row) {
    //   if (!cell.status && cell.neighbours == 3) {
    //     cell.status = true;
    //   } else if (cell.status && (cell.neighbours < m_burn || cell.neighbours > m_dead)) {
    //     cell.status = false;
    //   }
    // }

    for (auto &&cell : row) {
      if (!cell.status && cell.neighbours >= m_burn) {
        cell.status = true;
      } else if (cell.status && (cell.neighbours <= m_dead)) {
        cell.status = false;
      }
    }
  }
}

auto Cave::checkEquals() -> bool {
  for (auto const &el : m_base_field) {
    if (el == m_field) {
      return true;
    }
  }
  return false;
}

auto Cave::showBase() -> bool {
  for (auto const &el : m_base_field) {
    for (auto &row : el) {
      for (auto &elem : row) {
        cout << elem.status << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  return true;
}

auto operator==(const vector<vector<Cell>> &that, const vector<vector<Cell>> &other) -> bool const {
  for (int i = 0, l = that.size(); i < l; ++i) {
    for (int j = 0; j < l; ++j) {
      if (that.at(i).at(j).status != other.at(i).at(j).status) {
        return false;
      }
    }
  }
  return true;
}

auto Cave::printField() -> void {
  for (auto &row : m_field) {
    for (auto &elem : row) {
      cout << elem.status << " ";
    }
    cout << endl;
  }
}
