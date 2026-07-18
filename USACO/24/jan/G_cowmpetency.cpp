#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1'000'000'007;

ll pw(ll a, long long e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int q, C;
    cin >> n >> q >> C;

    map<long long, long long> mn;
    for (int i = 0; i < q; ++i) {
        long long a, h;
        cin >> a >> h;

        auto it = mn.find(h);
        if (it == mn.end()) mn[h] = a;
        else it->second = min(it->second, a);
    }

    vector<pair<long long, long long>> p;
    p.emplace_back(0, 0);

    for (auto [h, a] : mn)
        p.emplace_back(a, h);

    sort(p.begin() + 1, p.end());

    vector<int> prv(C + 1), cur(C + 1);
    prv[0] = 1;

    for (int i = 1; i < (int)p.size(); ++i) {
        auto [a, h] = p[i];
        long long ph = p[i - 1].second;

        long long x = a - ph;
        long long y = h - a - 1;

        fill(cur.begin(), cur.end(), 0);

        ll pref = 0;

        for (int j = 1; j <= C; ++j) {
            ll v = cur[j - 1];

            v += (ll)prv[j - 1] * pw(j - 1, x + y) % MOD;

            ll ways_raise =
                (pw(j - 1, x) - pw(j - 2, x) + MOD) % MOD;

            v += pref * ways_raise % MOD * pw(j - 1, y) % MOD;

            cur[j] = v % MOD;
            pref += prv[j - 1];

            if (pref >= MOD) pref -= MOD;
        }

        swap(prv, cur);
    }

    ll ans = 0;
    for (int j = 0; j <= C; ++j) {
        ans += prv[j];
        if (ans >= MOD) ans -= MOD;
    }

    long long last = p.back().second;
    ans = ans * pw(C, n - last) % MOD;

    cout << ans << '\n';
    return 0;
}