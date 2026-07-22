#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<ll> a(n); ll l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i]; l = max(l, a[i]); r += a[i];
    }
    while (l < r) {
        ll m = l + (r - l) / 2;
        int cnt = 1; ll sum = 0;
        for (int i = 0; i < n; i++) {
            if (sum + a[i] > m) { cnt++; sum = a[i]; }
            else sum += a[i];
        }
        if (cnt <= k) r = m;
        else l = m + 1;
    }
    cout << l << '\n';
}
