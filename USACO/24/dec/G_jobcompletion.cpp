#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
      ll s, t;
      cin >> s >> t;
      a.push_back({s + t, t});
    }
    sort(a.begin(), a.end());

    ll sum = 0;
    priority_queue<ll> pq;

    /* keep tasks sorted by deadline d
       invariant: after processing prefix, pq holds a feasible subset
       if sum > d, best repair is drop the biggest t (max time saved for losing
       1 task) so we maximize count by never dropping smaller ones when a bigger
       one exists */
    for (auto &e : a) {
      ll d = e.first, t = e.second;
      pq.push(t);
      sum += t;
      if (sum > d) {
        sum -= pq.top();
        pq.pop();
      }
    }

    cout << (int)pq.size() << "\n";
  }
}
