#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;
    cin >> n >> x;

    vector<ll> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];

    int m = 1 << n;
    vector<pair<int, ll>> dp(m, {n + 1, 0});
    dp[0] = {1, 0};

    for (int mask = 1; mask < m; mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;

            pair<int, ll> cur = dp[mask ^ (1 << i)];

            if (cur.second + w[i] <= x) {
                cur.second += w[i];
            } else {
                cur.first++;
                cur.second = w[i];
            }

            dp[mask] = min(dp[mask], cur);
        }
    }

    cout << dp[m - 1].first << '\n';
}
