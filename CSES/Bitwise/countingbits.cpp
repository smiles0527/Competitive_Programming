#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, ans = 0;
    cin >> n;

    for (ll b = 1; b <= n; b <<= 1) {
        ll len = b << 1;
        ans += (n + 1) / len * b;
        ans += max(0LL, (n + 1) % len - b);
    }

    cout << ans << '\n';
}
