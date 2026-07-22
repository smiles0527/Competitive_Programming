#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int x = i;

        while (x) {
            int d = x % 10;
            x /= 10;

            if (d) dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }

    cout << dp[n] << '\n';
}
