#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    ll ans = 1;

    for (int i = 0; i < n; i++) {
        if (a[i] > ans) break;
        ans += a[i];
    }

    cout << ans << '\n';
}
