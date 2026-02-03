#include <bits/stdc++.h>
using namespace std;

bool canConstructBasic(const string &target,
                       const vector<string> &wordBank) {

  if (target.empty())
    return true;

  for (const auto &word : wordBank) {

    if (target.size() >= word.size() && target.substr(0, word.size()) == word) {
      auto remainder = target.substr(word.size());

      if (canConstructBasic(remainder, wordBank))
        return true;
    }
  }

  return false;
}

bool canConstructMemo(const string &target,
                      const vector<string> &wordBank) {

  function<bool(const string &, const vector<string> &,
                     unordered_map<string, bool> &)>
      _canConstructMemo;
  _canConstructMemo = [&](const string &target,
                          const vector<string> &wordBank,
                          unordered_map<string, bool> &memo) -> bool {
    if (target.empty())
      return true;

    if (memo.count(target))
      return memo[target];

    for (const auto &word : wordBank) {

      if (target.size() >= word.size() &&
          target.substr(0, word.size()) == word) {
        auto remainder = target.substr(word.size());

        if (_canConstructMemo(remainder, wordBank, memo)) {
          memo[target] = true;
          return true;
        }
      }
    }

    memo[target] = false;
    return false;
  };

  unordered_map<string, bool> memo;

  return _canConstructMemo(target, wordBank, memo);
}

bool canConstructTable(const string &target,
                       const vector<string> &wordBank) {

  vector<bool> table(target.size() + 1, false);
  table[0] = true;

  for (int i = 0; i < target.size(); i++) {

    if (table[i]) {
      for (const auto &word : wordBank) {

        if (target.substr(i, word.size()) == word) {

          table[i + word.size()] = true;
        }
      }
    }
  }

  return table.back();
}
