#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> h(n), s(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) cin >> s[i];

    vector<int> dp(x + 1);

    for (int i = 0; i < n; i++) {
        for (int c = x; c >= h[i]; c--) {
            dp[c] = max(dp[c], dp[c - h[i]] + s[i]);
        }
    }

    cout << dp[x] << '\n';
}
