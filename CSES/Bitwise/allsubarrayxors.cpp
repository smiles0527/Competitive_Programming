#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void fwht(vector<ll>& a) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                ll x = a[i + j], y = a[i + j + len];
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n + 1);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        p[i] = p[i - 1] ^ x;
        mx = max(mx, p[i]);
    }

    int m = 1;
    while (m <= mx) m <<= 1;

    vector<ll> f(m);
    bool dup = false;
    for (int x : p) {
        if (f[x]) dup = true;
        f[x]++;
    }

    fwht(f);
    for (ll& x : f) x *= x;
    fwht(f);
    for (ll& x : f) x /= m;

    vector<int> ans;
    for (int x = 0; x < m; x++) {
        if ((x == 0 && dup) || (x > 0 && f[x] > 0)) ans.push_back(x);
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
