#include <bits/stdc++.h>
using namespace std;

struct It {
  int l, r;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<It> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i].l >> a[i].r;

  vector<int> L(n), R(n);
  iota(L.begin(), L.end(), 0);
  iota(R.begin(), R.end(), 0);

  sort(L.begin(), L.end(), [&](int i, int j) {
    if (a[i].l != a[j].l)
      return a[i].l < a[j].l;
    return a[i].r < a[j].r;
  });
  sort(R.begin(), R.end(), [&](int i, int j) {
    if (a[i].r != a[j].r)
      return a[i].r < a[j].r;
    return a[i].l < a[j].l;
  });

  priority_queue<pair<int, int>> pq;
  int lp = 0, rp = 0, ans = 0;

  /* interval graph dominating set greedy:
     take I = undominated with smallest right endpoint p.
     choose J among all intervals with left < p that has maximum right R.
     then every interval K with left < R is dominated (since K.right >= p >
     J.left, strict-open endpoints matter: left < R). */
  while (rp < n) {
    int p = a[R[rp]].r;
    while (lp < n && a[L[lp]].l < p)
      pq.push({a[L[lp]].r, L[lp]}), lp++;
    int Rr = pq.top().first;
    ans++;
    while (rp < n && a[R[rp]].l < Rr)
      rp++;
  }

  cout << ans << "\n";
  return 0;
}
