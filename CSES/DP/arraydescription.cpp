#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> dp(m + 2), ndp(m + 2);

    if (a[0]) {
        dp[a[0]] = 1;
    } else {
        for (int v = 1; v <= m; v++) dp[v] = 1;
    }

    for (int i = 1; i < n; i++) {
        fill(ndp.begin(), ndp.end(), 0);

        int l = 1, r = m;
        if (a[i]) l = r = a[i];

        for (int v = l; v <= r; v++) {
            ndp[v] = dp[v - 1] + dp[v];
            if (ndp[v] >= MOD) ndp[v] -= MOD;

            ndp[v] += dp[v + 1];
            if (ndp[v] >= MOD) ndp[v] -= MOD;
        }

        dp.swap(ndp);
    }

    int ans = 0;
    for (int v = 1; v <= m; v++) {
        ans += dp[v];
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';
}
