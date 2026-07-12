#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    set<int> s;

    auto fix = [&](int i) {
        if (i <= 0 || i >= n) return;
        if (a[i] > a[i - 1]) s.insert(i);
        else s.erase(i);
    };

    for (int i = 1; i < n; ++i) fix(i);

    int q;
    cin >> q;

    while (q--) {
        int p;
        ll v, t;
        cin >> p >> v >> t;
        --p;

        a[p] = v;
        fix(p);
        fix(p + 1);

        ll x = max(0LL, t - (ll)n + 1);
        x /= a[0] + 1;

        for (int i : s) {
            if (!x) break;
            ll f = (a[i] + a[i - 1] - 1) / a[i - 1];
            x /= f;
        }

        cout << x * a.back() << '\n';
    }
}