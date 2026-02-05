#include <bits/stdc++.h>
using namespace std;

struct C {
  int s, t, i;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<C> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].s >> a[i].t;
    a[i].i = i;
  }
  sort(a.begin(), a.end(), [](const C &x, const C &y) { return x.t < y.t; });

  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int dt = a[j].t - a[i].t;
      if (abs(a[j].s - a[i].s) <= dt)
        g[i].push_back(j);
    }
  }

  vector<int> mr(n, -1), ml(n, -1), vis(n, 0);
  int T = 0;

  function<int(int)> dfs = [&](int u) {
    if (vis[u] == T)
      return 0;
    vis[u] = T;
    for (int v : g[u]) {
      if (mr[v] == -1 || dfs(mr[v])) {
        mr[v] = u;
        ml[u] = v;
        return 1;
      }
    }
    return 0;
  };

  int m = 0;
  for (int u = 0; u < n; u++) {
    T++;
    m += dfs(u);
  }

  /*
    wagon can go i->j if time increases and |slot diff| <= dt.
    then one wagon is a path, we want cover all nodes with min paths.
    in DAG: min path cover = n - max matching (split nodes L/R).
  */

  int k = n - m;
  vector<int> prv(n, -1), nxt(n, -1);
  for (int u = 0; u < n; u++)
    if (ml[u] != -1)
      nxt[u] = ml[u];
  for (int v = 0; v < n; v++)
    if (mr[v] != -1)
      prv[v] = mr[v];

  vector<int> wag(n, 0);
  int id = 0;
  for (int v = 0; v < n; v++) {
    if (prv[v] == -1) {
      id++;
      int x = v;
      while (x != -1) {
        wag[x] = id;
        x = nxt[x];
      }
    }
  }

  cout << id << "\n";
  for (int p = 0; p < n; p++) {
    cout << a[p].s << " " << a[p].t << " " << wag[p] << "\n";
  }
  return 0;
}
