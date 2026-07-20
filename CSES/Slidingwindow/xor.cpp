#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        int l = max(0, i - k + 1);
        int r = min(i, n - k);

        if ((r - l + 1) & 1) {
            ans ^= x;
        }

        x = (a * x + b) % c;
    }

    cout << ans << '\n';
}
