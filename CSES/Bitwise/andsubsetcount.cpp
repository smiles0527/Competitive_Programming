#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int m = 1;
    while (m <= n) m <<= 1;

    vector<int> f(m), pw(n + 1), ans(m);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        f[x]++;
    }

    for (int b = 1; b < m; b <<= 1) {
        for (int mask = 0; mask < m; mask++) {
            if (!(mask & b)) f[mask] += f[mask | b];
        }
    }

    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = (ll)pw[i - 1] * 2 % mod;

    for (int mask = 0; mask < m; mask++) {
        ans[mask] = pw[f[mask]] - 1;
        if (ans[mask] < 0) ans[mask] += mod;
    }

    for (int b = 1; b < m; b <<= 1) {
        for (int mask = 0; mask < m; mask++) {
            if (mask & b) continue;
            ans[mask] -= ans[mask | b];
            if (ans[mask] < 0) ans[mask] += mod;
        }
    }

    for (int i = 0; i <= n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
