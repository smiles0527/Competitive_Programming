#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dp(n);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < n; j++) {
            if (s[j] == '*') {
                dp[j] = 0;
            } else if (j) {
                dp[j] += dp[j - 1];
                if (dp[j] >= MOD) dp[j] -= MOD;
            }
        }
    }

    cout << dp[n - 1] << '\n';
}
