#include <bits/stdc++.h>
using namespace std;

int minimum_insertions_for_palindrome_basic(const string &s) {
  int n = s.length();
  if (n == 0) {
    return 0;
  }

  function<int(const string &, int, int)> min_insertions_helper;
  min_insertions_helper = [&min_insertions_helper](const string &s, int l,
                                                   int h) {
    if (l > h) {
      return INT_MAX;
    }

    if (l == h) {
      return 0;
    }

    if (l == h - 1) {
      return s[l] == s[h] ? 0 : 1;
    }

    if (s[l] == s[h]) {
      return min_insertions_helper(s, l + 1, h - 1);
    } else {
      return 1 + min(min_insertions_helper(s, l, h - 1),
                          min_insertions_helper(s, l + 1, h));
    }
  };

  return min_insertions_helper(s, 0, n - 1);
}

int minimum_insertions_for_palindrome_memo(const string &s) {
  int n = s.length();
  if (n == 0) {
    return 0;
  }

  vector<vector<int>> memo(n, vector<int>(n, -1));
  function<int(const string &, int, int)> min_insertions_helper;
  min_insertions_helper = [&min_insertions_helper, &memo](const string &s,
                                                          int l, int h) {
    if (l > h) {
      return INT_MAX;
    }

    if (l == h) {
      return 0;
    }

    if (l == h - 1) {
      return s[l] == s[h] ? 0 : 1;
    }

    if (memo[l][h] != -1) {
      return memo[l][h];
    }

    if (s[l] == s[h]) {
      memo[l][h] = min_insertions_helper(s, l + 1, h - 1);
    } else {
      memo[l][h] = 1 + min(min_insertions_helper(s, l, h - 1),
                                min_insertions_helper(s, l + 1, h));
    }

    return memo[l][h];
  };

  return min_insertions_helper(s, 0, n - 1);
}

int minimum_insertions_for_palindrome_tab(const string &s) {
  int n = s.length();
  if (n == 0) {
    return 0;
  }

  vector<vector<int>> table(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    table[i][i] = 0;
  }

  for (int l = 2; l <= n; l++) {
    for (int i = 0; i < n - l + 1; i++) {
      int j = i + l - 1;
      if (l == 2) {
        table[i][j] = s[i] == s[j] ? 0 : 1;
      } else {
        if (s[i] == s[j]) {
          table[i][j] = table[i + 1][j - 1];
        } else {
          table[i][j] = 1 + min(table[i][j - 1], table[i + 1][j]);
        }
      }
    }
  }

  return table[0][n - 1];
}
