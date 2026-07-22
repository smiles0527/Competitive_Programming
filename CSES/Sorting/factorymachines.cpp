#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll t; cin >> n >> t;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    ll l = 0, r = *min_element(a.begin(), a.end()) * t;
    while (l < r) {
        ll m = l + (r - l) / 2, cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += m / a[i];
            if (cnt >= t) break;
        }
        if (cnt >= t) r = m;
        else l = m + 1;
    }
    cout << l << '\n';
}
