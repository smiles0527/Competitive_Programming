#include <bits/stdc++.h>
using namespace std;

vector<vector<string>>
allConstructBasic(const string &target,
                  const vector<string> &word_bank) {

  function<vector<vector<string>>(const string &)>
      recurse = [&](const string &target)
      -> vector<vector<string>> {
    if (target.empty()) {
      return {{}};
    }

    vector<vector<string>> result;
    for (const auto &word : word_bank) {
      if (target.find(word) == 0) {
        auto suffix_ways = recurse(target.substr(word.size()));
        for (auto &way : suffix_ways) {
          way.push_back(word);
        }
        result.insert(result.end(), suffix_ways.begin(), suffix_ways.end());
      }
    }

    return result;
  };

  return recurse(target);
}

vector<vector<string>>
allConstructMemo(const string &target,
                 const vector<string> &word_bank) {
  unordered_map<string, vector<vector<string>>> memo;

  function<vector<vector<string>>(const string &)>
      recurse = [&](const string &target)
      -> vector<vector<string>> {
    if (target.empty()) {
      return {{}};
    }

    if (memo.count(target) > 0) {
      return memo[target];
    }

    vector<vector<string>> result;
    for (const auto &word : word_bank) {
      if (target.find(word) == 0) {
        auto suffix_ways = recurse(target.substr(word.size()));
        for (auto &way : suffix_ways) {
          way.push_back(word);
        }
        result.insert(result.end(), suffix_ways.begin(), suffix_ways.end());
      }
    }

    memo[target] = result;
    return result;
  };

  return recurse(target);
}

vector<vector<string>>
allConstructTable(const string &target,
                  const vector<string> &word_bank) {
  vector<vector<vector<string>>> table(target.size() + 1);
  table[0] = {{}};

  for (size_t i = 0; i <= target.size(); ++i) {
    for (const auto &word : word_bank) {
      if (target.substr(i, word.size()) == word) {
        auto new_combination = table[i];
        for (auto &combination : new_combination) {
          combination.push_back(word);
        }
        table[i + word.size()].insert(table[i + word.size()].end(),
                                      new_combination.begin(),
                                      new_combination.end());
      }
    }
  }

  return table[target.size()];
}
