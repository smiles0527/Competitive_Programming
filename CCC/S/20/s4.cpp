#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = (int)s.size();
  vector<int> cnt(3, 0), a(2 * n);
  for (int i = 0; i < n; i++) {
    int x = (s[i] == 'A' ? 0 : (s[i] == 'B' ? 1 : 2));
    cnt[x]++;
    a[i] = a[i + n] = x;
  }

  vector<vector<int>> p(3, vector<int>(2 * n + 1, 0));
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 2 * n; i++)
      p[k][i + 1] = p[k][i] + (a[i] == k);
  }
  auto get = [&](int k, int l, int r) -> int { return p[k][r] - p[k][l]; };

  vector<int> ord = {0, 1, 2};
  long long best = (1LL << 60);

  /* misplacements matrix m[x][y] = how many of group x sit inside segment meant
     for y direct swaps fix two wrong spots at once: min(mAB,mBA)+... leftover
     wrong seats form 3-cycles, each cycle needs 2 swaps -> +2*(rem/3) */
  do {
    int len0 = cnt[ord[0]], len1 = cnt[ord[1]], len2 = cnt[ord[2]];
    for (int st = 0; st < n; st++) {
      int l0 = st, r0 = st + len0;
      int l1 = r0, r1 = r0 + len1;
      int l2 = r1, r2 = r1 + len2;

      long long m[3][3] = {0};

      int c0a = get(0, l0, r0), c0b = get(1, l0, r0), c0c = len0 - c0a - c0b;
      int c1a = get(0, l1, r1), c1b = get(1, l1, r1), c1c = len1 - c1a - c1b;
      int c2a = get(0, l2, r2), c2b = get(1, l2, r2), c2c = len2 - c2a - c2b;

      m[0][ord[0]] += c0a;
      m[1][ord[0]] += c0b;
      m[2][ord[0]] += c0c;
      m[0][ord[1]] += c1a;
      m[1][ord[1]] += c1b;
      m[2][ord[1]] += c1c;
      m[0][ord[2]] += c2a;
      m[1][ord[2]] += c2b;
      m[2][ord[2]] += c2c;

      long long dab = min(m[0][1], m[1][0]);
      long long dac = min(m[0][2], m[2][0]);
      long long dbc = min(m[1][2], m[2][1]);
      long long dir = dab + dac + dbc;

      long long off =
          (m[0][1] + m[0][2] + m[1][0] + m[1][2] + m[2][0] + m[2][1]);
      long long rem = off - 2 * dir;
      long long ans = dir + 2 * (rem / 3);

      if (ans < best)
        best = ans;
    }
  } while (next_permutation(ord.begin(), ord.end()));

  cout << best << "\n";
  return 0;
}
