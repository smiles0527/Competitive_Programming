#include <bits/stdc++.h>
#include <bits/hash.h>
using namespace std;

int longestCommonSubsequenceBasic(const vector<int> &arrayA,
                                  const vector<int> &arrayB) {

  function<int(const vector<int> &, const vector<int> &, int,
                    int)>
      _longestCommonSubsequenceBasic;
  _longestCommonSubsequenceBasic = [&](const vector<int> &arrayA,
                                       const vector<int> &arrayB, int m,
                                       int n) -> int {
    if (m < 0 || n < 0)
      return 0;

    if (arrayA[m] == arrayB[n])
      return _longestCommonSubsequenceBasic(arrayA, arrayB, m - 1, n - 1) + 1;

    return max(_longestCommonSubsequenceBasic(arrayA, arrayB, m, n - 1),
                    _longestCommonSubsequenceBasic(arrayA, arrayB, m - 1, n));
  };

  return _longestCommonSubsequenceBasic(
      arrayA, arrayB, static_cast<int>(arrayA.size()) - 1,
      static_cast<int>(arrayB.size()) - 1);
}

int longestCommonSubsequenceMemo(const vector<int> &arrayA,
                                 const vector<int> &arrayB) {

  function<int(const vector<int> &, const vector<int> &, int,
                    int, unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &)>
      _longestCommonSubsequenceMemo;
  _longestCommonSubsequenceMemo =
      [&](const vector<int> &arrayA, const vector<int> &arrayB, int m,
          int n,
          unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &memo) -> int {
    if (m < 0 || n < 0)
      return 0;

    pair<int, int> key(m, n);

    if (memo.count(key))
      return memo[key];

    if (arrayA[m] == arrayB[n]) {
      memo[key] =
          _longestCommonSubsequenceMemo(arrayA, arrayB, m - 1, n - 1, memo) + 1;
    } else {
      memo[key] = max(
          _longestCommonSubsequenceMemo(arrayA, arrayB, m, n - 1, memo),
          _longestCommonSubsequenceMemo(arrayA, arrayB, m - 1, n, memo));
    }

    return memo[key];
  };

  unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> memo;

  return _longestCommonSubsequenceMemo(
      arrayA, arrayB, static_cast<int>(arrayA.size()) - 1,
      static_cast<int>(arrayB.size()) - 1, memo);
}

int longestCommonSubsequenceTable(const vector<int> &arrayA,
                                  const vector<int> &arrayB) {

  auto m = arrayA.size();
  auto n = arrayB.size();
  vector<vector<int>> table(m + 1, vector<int>(n + 1));

  for (auto i = 1; i < m + 1; i++) {
    for (auto j = 1; j < n + 1; j++) {
      if (arrayA[i - 1] == arrayB[j - 1])
        table[i][j] = table[i - 1][j - 1] + 1;
      else
        table[i][j] = max(table[i - 1][j], table[i][j - 1]);
    }
  }

  return table[m][n];
}
