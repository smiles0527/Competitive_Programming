#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n), dp(n);
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = a[i];
        sum += a[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l] = max(a[l] - dp[l + 1], a[r] - dp[l]);
        }
    }

    cout << (sum + dp[0]) / 2 << '\n';
}
