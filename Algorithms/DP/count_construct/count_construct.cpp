#include <bits/stdc++.h>
using namespace std;

int countConstructBasic(const string &target,
                        const vector<string> &wordBank) {
  if (target.empty())
    return 1;

  int totalCount = 0;

  for (const auto &word : wordBank) {

    if (target.size() >= word.size() && target.substr(0, word.size()) == word) {
      auto suffix = target.substr(word.size());
      totalCount += countConstructBasic(suffix, wordBank);
    }
  }

  return totalCount;
}

int countConstructMemo(const string &target,
                       const vector<string> &wordBank) {

  function<int(const string &, const vector<string> &,
                    unordered_map<string, int> &)>
      _countConstructMemo;
  _countConstructMemo = [&](const string &target,
                            const vector<string> &wordBank,
                            unordered_map<string, int> &memo) -> int {
    if (target.empty())
      return 1;

    if (memo.count(target))
      return memo[target];

    int totalCount = 0;

    for (const auto &word : wordBank) {

      if (target.size() >= word.size() &&
          target.substr(0, word.size()) == word) {
        auto suffix = target.substr(word.size());
        totalCount += _countConstructMemo(suffix, wordBank, memo);
      }
    }

    memo[target] = totalCount;
    return totalCount;
  };

  unordered_map<string, int> memo;

  return _countConstructMemo(target, wordBank, memo);
}

int countConstructTable(const string &target,
                        const vector<string> &wordBank) {

  vector<int> table(target.size() + 1);
  table[0] = 1;

  for (int i = 0; i < target.size(); i++) {

    for (const auto &word : wordBank) {

      if (target.substr(i, word.size()) == word) {

        table[i + word.size()] += table[i];
      }
    }
  }

  return table.back();
}
