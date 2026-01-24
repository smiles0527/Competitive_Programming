#include <bits/stdc++.h>
#include <bits/hash.h>
using namespace std;

int gridTravelersBasic(int n, int m) {

  if (n == 0 || m == 0)
    return 0;

  if (n < 2 && m < 2)
    return min(m, n);

  return gridTravelersBasic(n - 1, m) + gridTravelersBasic(n, m - 1);
}

int gridTravelersMemo(int n, int m) {

  function<int(int, int,
                    unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &)>
      _gridTravelersMemo;
  _gridTravelersMemo =
      [&](int n, int m,
          unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> &memo) -> int {
    if (n == 0 || m == 0)
      return 0;

    if (n < 2 && m < 2)
      return min(m, n);

    pair<int, int> key(n, m);

    if (memo.count(key))
      return memo[key];

    memo[key] =
        _gridTravelersMemo(n - 1, m, memo) + _gridTravelersMemo(n, m - 1, memo);

    return memo[key];
  };

  unordered_map<pair<int, int>, int, std::hash<pair<int,int>>> memo;
  return _gridTravelersMemo(n, m, memo);
}

int gridTravelersTable(int n, int m) {

  vector<vector<int>> table(m + 1, vector<int>(n + 1));
  table[1][1] = 1;

  for (int i = 1; i <= m; i++) {

    for (int j = 1; j <= n; j++) {
      auto cur = table[i][j];

      if (i < m)
        table[i + 1][j] += cur;

      if (j < n)
        table[i][j + 1] += cur;
    }
  }

  return table[m][n];
}
