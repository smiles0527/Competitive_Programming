#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//c[i] = min(c[i], 2c[i-1])
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

        for (int i = 60; i >= 0; i--) {
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
