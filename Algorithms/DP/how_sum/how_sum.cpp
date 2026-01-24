#include <bits/stdc++.h>
using namespace std;

vector<unsigned int>
howSumBasic(const unsigned int target,
            const vector<unsigned int> &numbers) {

  function<vector<vector<unsigned int>>(
      const unsigned int, const vector<unsigned int> &)>
      _howSumBasic;
  _howSumBasic = [&](const unsigned int target,
                     const vector<unsigned int> &numbers)
      -> vector<vector<unsigned int>> {
    if (target == 0)
      return {{}};

    for (const auto &num : numbers) {
      if (num > target)
        continue;

      auto remainder = target - num;
      auto combination = _howSumBasic(remainder, numbers);

      if (!combination.empty()) {
        combination[0].push_back(num);
        return combination;
      }
    }

    return {};
  };

  auto result = _howSumBasic(target, numbers);

  if (!result.empty())
    return result.front();

  return {};
}

vector<unsigned int> howSumMemo(const unsigned int target,
                                     const vector<unsigned int> &numbers) {

  function<vector<vector<unsigned int>>(
      const unsigned int, const vector<unsigned int> &,
      unordered_map<unsigned int, vector<vector<unsigned int>>>
          &)>
      _howSumMemo;
  _howSumMemo =
      [&](const unsigned int target, const vector<unsigned int> &numbers,
          unordered_map<unsigned int,
                             vector<vector<unsigned int>>> &memo)
      -> vector<vector<unsigned int>> {
    if (target == 0)
      return {{}};

    if (memo.count(target))
      return memo[target];

    for (const auto &num : numbers) {
      if (num > target)
        continue;

      auto remainder = target - num;
      auto combination = _howSumMemo(remainder, numbers, memo);

      if (!combination.empty()) {
        combination[0].push_back(num);
        memo[target] = combination;
        return combination;
      }
    }

    memo[target] = {};
    return {};
  };

  unordered_map<unsigned int, vector<vector<unsigned int>>> memo;

  auto result = _howSumMemo(target, numbers, memo);

  if (!result.empty())
    return result.front();

  return {};
}

vector<unsigned int>
howSumTable(const unsigned int target,
            const vector<unsigned int> &numbers) {

  vector<vector<vector<unsigned int>>> table(target + 1);
  table[0] = {{}};

  for (unsigned int i = 0; i < target; i++) {
    if (!table[i].empty()) {
      for (const auto &number : numbers) {
        if (i + number <= target) {
          table[i + number] = table[i];
          table[i + number][0].push_back(number);
        }
      }
    }
  }

  if (!table.back().empty())
    return table.back().front();

  return {};
}
