#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> q(t);
    int mx = 0;

    for (int i = 0; i < t; i++) {
        cin >> q[i];
        mx = max(mx, q[i]);
    }

    vector<int> ans(mx + 1);
    ll a = 1, b = 1;
    ans[1] = 2;

    for (int i = 2; i <= mx; i++) {
        ll na = (4 * a + b) % MOD;
        ll nb = (a + 2 * b) % MOD;
        a = na;
        b = nb;
        ans[i] = (a + b) % MOD;
    }

    for (int n : q) cout << ans[n] << '\n';
}
