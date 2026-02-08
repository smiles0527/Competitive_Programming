#include "cluedo.h"
#include <bits/stdc++.h>
using namespace std;

static int nxt(const vector<char> &a, int x) {
  while (x < (int)a.size() && !a[x])
    ++x;
  return x;
}

void Solve() {
  vector<char> m(7, 1), l(11, 1), w(7, 1);

  int i = 1, j = 1, k = 1;
  for (;;) {
    i = nxt(m, i);
    j = nxt(l, j);
    k = nxt(w, k);

    int r = Theory(i, j, k);
    if (!r)
      return;

    /*
      idea: every time Jack says "category X is wrong", we can delete exactly
      that value. even if multiple are wrong, Jack picks one of the wrong ones
      -> we still delete a wrong value. total deletions <= (6-1) + (10-1) +
      (6-1) = 19, then 1 final confirm => <= 20 calls.
    */

    if (r == 1) {
      m[i] = 0;
      i = nxt(m, i + 1);
    } else if (r == 2) {
      l[j] = 0;
      j = nxt(l, j + 1);
    } else {
      w[k] = 0;
      k = nxt(w, k + 1);
    }
  }
}
