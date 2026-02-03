#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
  Key observation:
  - Deal i gives 2^i buckets for cost a[i]
  - Each deal can be used unlimited times
  - We want minimum cost to buy at least x buckets

  Step 1 : normalize costs
  A larger pack should never be worse than buying two smaller ones:
    c[i] = min(c[i], 2 * c[i-1])

  Also, since x <= 10^9, any deal with size >= 2^60 already covers all queries

  So we keep costs only for i = 0..60
        and fold all larger deals into c[60] by takijng the minimum cost


  Step 2 : greedy per query
  For each query x:
    - iterate from largest pack (2^60) down to smallest
    - greedily take as many packs as possible without exceeding x
    - track current cost cur
    - at eaech step, consider buying one extra pack to overshoot and finish

  That answer is the minimum of all such candidates.

  This works because, after normalizaiton, larger packs are never inefficient compared to smaller ones,
  so greedy is optimal.

  Complexity:
  - preprocessing: O(60)
  - each query: O(60)
  - total: O(Q * 60)
 */

// if i < 61 store manually (large numbers)
void solve() {
    int N, Q; cin >> N >> Q;

    const ll INF = 1LL << 60;
    vector<long long> c(61, INF);

    for (int i = 0; i < N; i++){
      long long a; cin >> a;
      if(i < 61) c[i] = a;
      else c[60] = min(c[60], a);
    }

    for (int i = 1; i <= 60; i++) c[i] = min(c[i], 2LL * c[i - 1]);

    while (Q--) {
        ll x; cin >> x;

        ll cur = 0, ans = INF;

        for(int i = 60; i >= 0; i--) {
            ll sz = 1LL << i;
            ll take = x / sz;
            cur += take * c[i];
            x -= take * sz;
            ans = min(ans, cur + (x ? c[i] : 0));
        }

        cout << ans << "\n";
    }
}

int main() {
    solve();
    return 0;
}
