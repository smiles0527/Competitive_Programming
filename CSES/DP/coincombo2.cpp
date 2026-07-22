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

    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int s = c[i]; s <= x; s++) {
            dp[s] += dp[s - c[i]];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    cout << dp[x] << '\n';
}
