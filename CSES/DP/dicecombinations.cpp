#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int d = 1; d <= 6 && d <= i; d++) {
            dp[i] += dp[i - d];
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
    }

    cout << dp[n] << '\n';
}
