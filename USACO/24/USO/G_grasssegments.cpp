#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> t;

    BIT(int n = 0) : n(n), t(n + 1) {}

    void add(int p, int v) {
        for (++p; p <= n; p += p & -p) t[p] += v;
    }

    int sum(int p) const {
        int s = 0;
        for (; p > 0; p -= p & -p) s += t[p];
        return s;
    }
};

struct Seg {
    int l, r, k, id;

    int len() const {
        return r - l;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Seg> a(n);
    vector<int> xs;
    xs.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i].l >> a[i].r >> a[i].k;
        a[i].id = i;
        xs.push_back(a[i].l);
        xs.push_back(a[i].r);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    vector<int> byLen(n), byK(n);
    iota(byLen.begin(), byLen.end(), 0);
    iota(byK.begin(), byK.end(), 0);

    sort(byLen.begin(), byLen.end(), [&](int x, int y) {
        return a[x].len() > a[y].len();
    });

    sort(byK.begin(), byK.end(), [&](int x, int y) {
        return a[x].k > a[y].k;
    });

    BIT bl(xs.size()), br(xs.size());
    vector<int> ans(n);

    int p = 0, cnt = 0;

    for (int qi : byK) {
        while (p < n && a[byLen[p]].len() >= a[qi].k) {
            int j = byLen[p++];

            int il = lower_bound(xs.begin(), xs.end(), a[j].l) - xs.begin();
            int ir = lower_bound(xs.begin(), xs.end(), a[j].r) - xs.begin();

            bl.add(il, 1);
            br.add(ir, 1);
            ++cnt;
        }

        int x = lower_bound(
            xs.begin(), xs.end(), a[qi].l + a[qi].k
        ) - xs.begin();

        int y = upper_bound(
            xs.begin(), xs.end(), a[qi].r - a[qi].k
        ) - xs.begin();

        int leftBad = br.sum(x);
        int rightBad = cnt - bl.sum(y);

        ans[qi] = cnt - 1 - leftBad - rightBad;
    }

    for (int x : ans) cout << x << '\n';
}