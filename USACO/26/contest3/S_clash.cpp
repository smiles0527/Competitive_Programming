#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<pii> a(n);
    for (auto &[w, c] : a) cin >> c;

    int k;
    cin >> k;
    while (k--) {
        int x;
        cin >> x;
        a[--x].first = -1;
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < h - 1; ++i) pq.push(a[i]);

    vector<ll> win;
    ll cyc = 0;

    for (int i = h - 1; i < n; ++i) {
        pq.push(a[i]);

        auto [w, c] = pq.top();
        pq.pop();

        cyc += c;
        if (w == -1) win.push_back(cyc);
    }

    int q;
    cin >> q;

    while (q--) {
        ll t;
        cin >> t;

        ll ans = t / cyc * (ll)win.size();
        ans += upper_bound(win.begin(), win.end(), t % cyc) - win.begin();

        cout << ans << '\n';
    }
}