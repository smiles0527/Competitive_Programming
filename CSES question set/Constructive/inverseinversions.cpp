#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    ll lo = 0, hi = n;
    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if (mid * (mid - 1) / 2 <= k) lo = mid;
        else hi = mid - 1;
    }

    ll q = lo;
    ll r = k - q * (q - 1) / 2;

    if (r == 0) {
        for (ll i = 1; i <= n - q; i++) cout << i << ' ';
        for (ll i = n; i >= n - q + 1; i--) cout << i << ' ';
        cout << '\n';
        return 0;
    }

    for (ll i = 1; i <= n - q - 1; i++) cout << i << ' ';

    for (ll i = 0; i < r; i++) cout << n - i << ' ';
    cout << n - q << ' ';
    for (ll i = r; i < q; i++) cout << n - i << ' ';

    cout << '\n';
}