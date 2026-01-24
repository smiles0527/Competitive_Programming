#include <bits/stdc++.h>
using namespace std;

vector<int> search(const string &text, const string &pattern) {

  function<vector<int>(const string &)>
      find_longest_prefix_suffix = [&](const string &word) {
        vector<int> result(word.size());
        int i = 1;
        int j = 0;
        while (i < word.size()) {
          if (word[i] == word[j]) {
            j += 1;
            result[i] = j;
            i += 1;
          } else {
            if (j != 0) {
              j = result[j - 1];
            } else {
              result[i] = 0;
              i += 1;
            }
          }
        }
        return result;
      };

  auto longest_prefix_suffix = find_longest_prefix_suffix(pattern);
  vector<int> result;
  int j = 0;
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == pattern[j]) {
      j += 1;
    } else {
      if (j != 0) {
        j = longest_prefix_suffix[j - 1];
      }
    }
    if (j == pattern.size()) {
      result.push_back(i - j + 1);
      j = longest_prefix_suffix[j - 1];
    }
  }
  return result;
}
