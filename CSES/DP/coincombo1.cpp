#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    sort(c.begin(), c.end());

    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int s = 1; s <= x; s++) {
        for (int i = 0; i < n && c[i] <= s; i++) {
            dp[s] += dp[s - c[i]];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    cout << dp[x] << '\n';
}
