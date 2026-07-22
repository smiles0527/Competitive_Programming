#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int n = a.size(), m = b.size();
    vector<int> dp(m + 1);

    for (int j = 0; j <= m; j++) dp[j] = j;

    for (int i = 1; i <= n; i++) {
        int prev = dp[0];
        dp[0] = i;

        for (int j = 1; j <= m; j++) {
            int old = dp[j];

            if (a[i - 1] == b[j - 1]) {
                dp[j] = prev;
            } else {
                dp[j] = 1 + min(prev, min(dp[j], dp[j - 1]));
            }

            prev = old;
        }
    }

    cout << dp[m] << '\n';
}
