#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sum += x; mx = max(mx, x);
    }
    cout << max(sum, 2 * mx) << '\n';
}
