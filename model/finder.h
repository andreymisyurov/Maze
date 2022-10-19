#ifndef SRC_MODEL_FINDER_H_
#define SRC_MODEL_FINDER_H_

#include <vector>

using namespace std;

class Finder {
 public:
  auto getPath(const pair<vector<vector<int>>, vector<vector<int>>> &walls,
               int iStart, int jStart, int iFinish, int jFinish)
      -> vector<pair<int, int>>;

 private:
  auto fillResultField(int i, int j, int value) -> vector<vector<int>>;
  auto getPartNext(int i, int j, const vector<vector<int>> &field,
                   const pair<vector<vector<int>>, vector<vector<int>>> &walls)
      -> std::pair<int, int>;
  auto writeWaveValue(
      vector<vector<int>> &field, int i, int j, int counter, bool &flag,
      const pair<vector<vector<int>>, const vector<vector<int>>> &walls)
      -> void;
  auto collectPath(vector<pair<int, int>> &result, pair<int, int> partPath,
                   const vector<vector<int>> &field,
                   const pair<vector<vector<int>>, vector<vector<int>>> &walls)
      -> void;
};

#endif  // SRC_MODEL_FINDER_H_
