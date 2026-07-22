#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    sort(c.begin(), c.end());

    vector<int> dp(x + 1, x + 1);
    dp[0] = 0;

    for (int s = 1; s <= x; s++) {
        for (int i = 0; i < n && c[i] <= s; i++) {
            dp[s] = min(dp[s], dp[s - c[i]] + 1);
        }
    }

    if (dp[x] > x) cout << -1 << '\n';
    else cout << dp[x] << '\n';
}
