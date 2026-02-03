#include <bits/stdc++.h>
using namespace std;

vector<unsigned int>
bestSumBasic(unsigned int target, const vector<unsigned int> &numbers) {
  function<vector<vector<unsigned int>>(
      unsigned int, const vector<unsigned int> &)>
      _bestSumBasic;
  _bestSumBasic = [&](unsigned int target,
                      const vector<unsigned int> &numbers)
      -> vector<vector<unsigned int>> {
    if (target == 0) {
      return {{}};
    }

    vector<unsigned int> shortestCombination;

    for (const auto &num : numbers) {
      if (num > target) {
        continue;
      }

      auto remainder = target - num;
      auto combination = _bestSumBasic(remainder, numbers);

      if (!combination.empty()) {
        combination[0].push_back(num);

        if (shortestCombination.empty() ||
            combination[0].size() < shortestCombination.size()) {
          shortestCombination = combination[0];
        }
      }
    }

    if (!shortestCombination.empty()) {
      return {shortestCombination};
    }

    return {};
  };

  auto result = _bestSumBasic(target, numbers);

  if (!result.empty()) {
    return result.front();
  }

  return {};
}

vector<unsigned int>
bestSumMemo(unsigned int target, const vector<unsigned int> &numbers) {
  unordered_map<unsigned int, vector<vector<unsigned int>>> memo;

  function<vector<vector<unsigned int>>(
      unsigned int, const vector<unsigned int> &)>
      _bestSumMemo;
  _bestSumMemo = [&](unsigned int target,
                     const vector<unsigned int> &numbers)
      -> vector<vector<unsigned int>> {
    if (target == 0) {
      return {{}};
    }

    if (memo.find(target) != memo.end()) {
      return memo[target];
    }

    vector<unsigned int> shortestCombination;

    for (const auto &num : numbers) {
      if (num > target) {
        continue;
      }

      auto remainder = target - num;
      auto combination = _bestSumMemo(remainder, numbers);

      if (!combination.empty()) {
        combination[0].push_back(num);

        if (shortestCombination.empty() ||
            combination[0].size() < shortestCombination.size()) {
          shortestCombination = combination[0];
        }
      }
    }

    if (!shortestCombination.empty()) {
      memo[target] = {shortestCombination};
      return memo[target];
    }

    memo[target] = {};
    return memo[target];
  };

  auto result = _bestSumMemo(target, numbers);

  if (!result.empty()) {
    return result.front();
  }

  return {};
}

vector<unsigned int>
bestSumTabulation(unsigned int target,
                  const vector<unsigned int> &numbers) {
  vector<vector<vector<unsigned int>>> table(
      target + 1, vector<vector<unsigned int>>());

  table[0] = {{}};

  for (auto i = 0; i <= target; ++i) {
    if (!table[i].empty()) {
      for (const auto &num : numbers) {
        if (i + num <= target) {
          auto combination = table[i];

          for (auto &comb : combination) {
            comb.push_back(num);
          }

          if (table[i + num].empty()) {
            table[i + num] = combination;
          } else if (table[i + num].front().size() >
                     combination.front().size()) {
            table[i + num] = combination;
          }
        }
      }
    }
  }

  if (!table[target].empty()) {
    return table[target].front();
  }

  return {};
}
