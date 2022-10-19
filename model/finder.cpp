#include "finder.h"

auto Finder::fillResultField(int i, int j, int value) -> vector<vector<int>> {
  vector<vector<int>> result(i);
  fill(result.begin(), result.end(), vector<int>(j, value));
  return result;
}

auto Finder::getPath(
    const pair<vector<vector<int>>, vector<vector<int>>> &walls, int iStart,
    int jStart, int iFinish, int jFinish) -> vector<pair<int, int>> {
  auto waveField =
      fillResultField(walls.first.size(), walls.first[0].size(), -1);
  waveField[iStart][jStart] = 0;
  waveField[iFinish][jFinish] = -2;

  auto flag = true;
  int i, j, counter = -1, i_max = waveField.size(), j_max = waveField[0].size();
  while (flag) {
    ++counter;
    for (i = 0; i < i_max; ++i) {
      for (j = 0; j < j_max; ++j) {
        if (waveField[i][j] == counter) {
          writeWaveValue(waveField, i, j, counter, flag, walls);
        }
      }
    }
  }

  vector<pair<int, int>> result;
  result.push_back(make_pair(iFinish, jFinish));
  collectPath(result, make_pair(iFinish, jFinish), waveField, walls);

  return result;
}

auto Finder::getPartNext(
    int i, int j, const vector<vector<int>> &field,
    const pair<vector<vector<int>>, vector<vector<int>>> &walls)
    -> std::pair<int, int> {
  int nextPathValue = field[i][j] - 1;
  if (j > 0 && (!walls.first[i][j - 1]) && (field[i][j - 1] == nextPathValue))
    return std::pair<int, int>(i, j - 1);
  else if (i > 0 && (!walls.second[i - 1][j]) &&
           (field[i - 1][j] == nextPathValue))
    return std::pair<int, int>(i - 1, j);
  else if (j < static_cast<int>(field[0].size() - 1) && (!walls.first[i][j]) &&
           (field[i][j + 1] == nextPathValue))
    return std::pair<int, int>(i, j + 1);
  else
    return std::pair<int, int>(i + 1, j);
}

auto Finder::writeWaveValue(
    vector<vector<int>> &field, int i, int j, int counter, bool &flag,
    const pair<vector<vector<int>>, const vector<vector<int>>> &walls) -> void {
  if (j > 0 && field[i][j - 1] == -2 && walls.first[i][j - 1] != 1) {
    field[i][j - 1] = counter + 1;
    flag = false;
    return;
  }

  if (j < static_cast<int>(field[0].size() - 1) && field[i][j + 1] == -2 &&
      walls.first[i][j] != 1) {
    field[i][j + 1] = counter + 1;
    flag = false;
    return;
  }

  if (i > 0 && field[i - 1][j] == -2 && walls.second[i - 1][j] != 1) {
    field[i - 1][j] = counter + 1;
    flag = false;
    return;
  }

  if (i < static_cast<int>(field.size() - 1) && field[i + 1][j] == -2 &&
      walls.second[i][j] != 1) {
    field[i + 1][j] = counter + 1;
    flag = false;
    return;
  }

  if (j > 0 && field.at(i).at(j - 1) == -1 && walls.first[i][j - 1] != 1)
    field.at(i).at(j - 1) = counter + 1;
  if (j < static_cast<int>(field[0].size() - 1) &&
      field.at(i).at(j + 1) == -1 && walls.first[i][j] != 1)
    field.at(i).at(j + 1) = counter + 1;
  if (i > 0 && field.at(i - 1).at(j) == -1 && walls.second[i - 1][j] != 1)
    field.at(i - 1).at(j) = counter + 1;
  if (i < static_cast<int>(field.size() - 1) && field.at(i + 1).at(j) == -1 &&
      walls.second[i][j] != 1)
    field.at(i + 1).at(j) = counter + 1;
}

auto Finder::collectPath(
    vector<pair<int, int>> &result, pair<int, int> partPath,
    const vector<vector<int>> &field,
    const pair<vector<vector<int>>, vector<vector<int>>> &walls) -> void {
  if (field[partPath.first][partPath.second] == 0) return;
  auto nextPart = getPartNext(partPath.first, partPath.second, field, walls);
  result.push_back(make_pair(nextPart.first, nextPart.second));
  collectPath(result, nextPart, field, walls);
}
