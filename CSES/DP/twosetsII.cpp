#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int sum = n * (n + 1) / 2;
    if (sum % 2) {
        cout << 0 << '\n';
        return 0;
    }

    int target = sum / 2;
    vector<int> dp(target + 1);
    dp[0] = 1;

    for (int x = 1; x < n; x++) {
        for (int s = target; s >= x; s--) {
            dp[s] += dp[s - x];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    cout << dp[target] << '\n';
}
