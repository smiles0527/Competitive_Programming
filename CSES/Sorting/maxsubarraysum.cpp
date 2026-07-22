#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    ll x; cin >> x;
    ll cur = x, ans = x;

    for (int i = 1; i < n; i++) {
        cin >> x;
        cur = max(x, cur + x);
        ans = max(ans, cur);
    }

    cout << ans << '\n';
}
