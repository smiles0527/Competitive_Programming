#include <bits/stdc++.h>
#include <bits/hash.h>
using namespace std;

int longestIncreasingSubarrayBasic(const vector<int> &array) {

  function<int(const vector<int> &, unsigned int, int)>
      _longestIncreasingSubarrayBasic;
  _longestIncreasingSubarrayBasic = [&](const vector<int> &array,
                                        unsigned int i, int prev) -> int {
    if (i == array.size())
      return 0;

    auto excl = _longestIncreasingSubarrayBasic(array, i + 1, prev);

    auto incl = 0;

    if (array[i] > prev)
      incl = _longestIncreasingSubarrayBasic(array, i + 1, array[i]) + 1;

    return max(incl, excl);
  };

  return _longestIncreasingSubarrayBasic(array, 0, INT_MIN);
}

int longestIncreasingSubarrayMemo(const vector<int> &array) {

  function<int(const vector<int> &, unsigned int, int,
                    unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &)>
      _longestIncreasingSubarrayMemo;
  _longestIncreasingSubarrayMemo =
      [&](const vector<int> &array, unsigned int i, int prev,
          unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &memo) -> int {
    if (i == array.size())
      return 0;

    pair<int, int> key(i, prev);

    if (memo.count(key))
      return memo[key];

    auto excl = _longestIncreasingSubarrayMemo(array, i + 1, prev, memo);

    auto incl = 0;

    if (array[i] > prev)
      incl = _longestIncreasingSubarrayMemo(array, i + 1, array[i], memo) + 1;

    memo[key] = max(incl, excl);
    return memo[key];
  };

  unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> memo;

  return _longestIncreasingSubarrayMemo(array, 0, INT_MIN, memo);
}

int longestIncreasingSubarrayTable(const vector<int> &array) {

  vector<vector<int>> table(array.size(), vector<int>());

  table[0].emplace_back(array[0]);

  for (auto i = 1; i < array.size(); i++) {
    for (auto j = 0; j < i; j++) {
      if (array[j] < array[i] && table[j].size() > table[i].size())
        table[i] = vector<int>(table[j]);
    }
    table[i].emplace_back(array[i]);
  }

  auto j = 0;
  for (auto i = 0; i < array.size(); i++) {
    if (table[j].size() < table[i].size())
      j = i;
  }

  return table[j].size();
}
