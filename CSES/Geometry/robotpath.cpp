#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 62);

struct BIT {
    vector<ll> bit;

    BIT() {}
    BIT(int n) : bit(n + 1, -INF) {}

    void upd(int i, ll v) {
        for (int n = bit.size(); i < n; i += i & -i) bit[i] = max(bit[i], v);
    }

    ll qry(int i) const {
        ll r = -INF;
        for (; i > 0; i -= i & -i) r = max(r, bit[i]);
        return r;
    }
};

struct Seg {
    int m, n;
    vector<ll> c;
    vector<vector<ll>> ys;
    vector<BIT> fw;

    Seg() {}

    Seg(vector<ll> _c) : c(_c) {
        m = c.size();
        n = 1;
        while (n < m) n <<= 1;
        ys.assign(2 * n, {});
    }

    void prep(ll x, ll lo) {
        int id = lower_bound(c.begin(), c.end(), x) - c.begin();
        for (int p = id + n; p; p >>= 1) ys[p].push_back(lo);
    }

    void build() {
        fw.resize(2 * n);
        for (int i = 1; i < 2 * n; i++) {
            auto &v = ys[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            fw[i] = BIT(v.size());
        }
    }

    void add(ll x, ll lo, ll hi) {
        int id = lower_bound(c.begin(), c.end(), x) - c.begin();
        for (int p = id + n; p; p >>= 1) {
            int q = lower_bound(ys[p].begin(), ys[p].end(), lo) - ys[p].begin() + 1;
            fw[p].upd(q, hi);
        }
    }

    bool has(int p, ll y) const {
        if (ys[p].empty()) return false;
        int q = upper_bound(ys[p].begin(), ys[p].end(), y) - ys[p].begin();
        if (!q) return false;
        return fw[p].qry(q) >= y;
    }

    int first(int p, int l, int r, int ql, int qr, ll y) const {
        if (r < ql || qr < l || !has(p, y)) return -1;
        if (l == r) return l < m ? l : -1;
        int md = (l + r) >> 1;
        int z = first(p << 1, l, md, ql, qr, y);
        if (z != -1) return z;
        return first(p << 1 | 1, md + 1, r, ql, qr, y);
    }

    int last(int p, int l, int r, int ql, int qr, ll y) const {
        if (r < ql || qr < l || !has(p, y)) return -1;
        if (l == r) return l < m ? l : -1;
        int md = (l + r) >> 1;
        int z = last(p << 1 | 1, md + 1, r, ql, qr, y);
        if (z != -1) return z;
        return last(p << 1, l, md, ql, qr, y);
    }

    int first(int l, int r, ll y) const {
        if (!m || l > r) return -1;
        l = max(l, 0), r = min(r, m - 1);
        if (l > r) return -1;
        return first(1, 0, n - 1, l, r, y);
    }

    int last(int l, int r, ll y) const {
        if (!m || l > r) return -1;
        l = max(l, 0), r = min(r, m - 1);
        if (l > r) return -1;
        return last(1, 0, n - 1, l, r, y);
    }
};

struct Line {
    map<ll, ll> mp;

    ll hitR(ll x, ll r) const {
        auto it = mp.upper_bound(x);
        if (it != mp.begin()) {
            auto p = prev(it);
            if (p->second > x) return x;
        }
        if (it != mp.end() && it->first <= r) return it->first;
        return INF;
    }

    ll hitL(ll x, ll l) const {
        auto it = mp.lower_bound(x);
        if (it != mp.begin()) {
            auto p = prev(it);
            if (p->first < x && p->second >= x) return x;
            if (p->second < x && p->second >= l) return p->second;
        }
        return INF;
    }

    void add(ll l, ll r) {
        auto it = mp.lower_bound(l);

        if (it != mp.begin()) {
            auto p = prev(it);
            if (p->second >= l) {
                l = min(l, p->first);
                r = max(r, p->second);
                it = mp.erase(p);
            }
        }

        while (it != mp.end() && it->first <= r) {
            r = max(r, it->second);
            it = mp.erase(it);
        }

        mp[l] = r;
    }
};

struct Hsh {
    size_t operator()(ll x) const {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<char> d(n);
    vector<ll> a(n), x0(n), y0(n), x1(n), y1(n);
    vector<ll> xs, ys;

    ll x = 0, y = 0;

    for (int i = 0; i < n; i++) {
        cin >> d[i] >> a[i];

        x0[i] = x;
        y0[i] = y;

        if (d[i] == 'U') y += a[i];
        else if (d[i] == 'D') y -= a[i];
        else if (d[i] == 'R') x += a[i];
        else x -= a[i];

        x1[i] = x;
        y1[i] = y;

        if (x0[i] == x1[i]) xs.push_back(x0[i]);
        else ys.push_back(y0[i]);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    Seg V(xs), H(ys);

    for (int i = 0; i < n; i++) {
        if (x0[i] == x1[i]) V.prep(x0[i], min(y0[i], y1[i]));
        else H.prep(y0[i], min(x0[i], x1[i]));
    }

    V.build();
    H.build();

    unordered_map<ll, Line, Hsh> hh, vv;
    hh.reserve(2 * n + 1);
    vv.reserve(2 * n + 1);

    x = y = 0;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
        ll nx = x, ny = y;

        if (d[i] == 'U') ny += a[i];
        else if (d[i] == 'D') ny -= a[i];
        else if (d[i] == 'R') nx += a[i];
        else nx -= a[i];

        ll best = INF;

        if (y == ny) {
            if (nx > x) {
                int l = upper_bound(xs.begin(), xs.end(), x) - xs.begin();
                int r = upper_bound(xs.begin(), xs.end(), nx) - xs.begin() - 1;

                int id = V.first(l, r, y);
                if (id != -1) best = min(best, xs[id] - x);

                auto it = hh.find(y);
                if (it != hh.end()) {
                    ll p = it->second.hitR(x, nx);
                    if (p != INF) best = min(best, p - x);
                }
            } else {
                int l = lower_bound(xs.begin(), xs.end(), nx) - xs.begin();
                int r = lower_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;

                int id = V.last(l, r, y);
                if (id != -1) best = min(best, x - xs[id]);

                auto it = hh.find(y);
                if (it != hh.end()) {
                    ll p = it->second.hitL(x, nx);
                    if (p != INF) best = min(best, x - p);
                }
            }
        } else {
            if (ny > y) {
                int l = upper_bound(ys.begin(), ys.end(), y) - ys.begin();
                int r = upper_bound(ys.begin(), ys.end(), ny) - ys.begin() - 1;

                int id = H.first(l, r, x);
                if (id != -1) best = min(best, ys[id] - y);

                auto it = vv.find(x);
                if (it != vv.end()) {
                    ll p = it->second.hitR(y, ny);
                    if (p != INF) best = min(best, p - y);
                }
            } else {
                int l = lower_bound(ys.begin(), ys.end(), ny) - ys.begin();
                int r = lower_bound(ys.begin(), ys.end(), y) - ys.begin() - 1;

                int id = H.last(l, r, x);
                if (id != -1) best = min(best, y - ys[id]);

                auto it = vv.find(x);
                if (it != vv.end()) {
                    ll p = it->second.hitL(y, ny);
                    if (p != INF) best = min(best, y - p);
                }
            }
        }

        if (best <= a[i]) {
            cout << ans + best << '\n';
            return 0;
        }

        if (y == ny) {
            ll l = min(x, nx), r = max(x, nx);
            hh[y].add(l, r);
            H.add(y, l, r);
        } else {
            ll l = min(y, ny), r = max(y, ny);
            vv[x].add(l, r);
            V.add(x, l, r);
        }

        ans += a[i];
        x = nx;
        y = ny;
    }

    cout << ans << '\n';
    return 0;
}