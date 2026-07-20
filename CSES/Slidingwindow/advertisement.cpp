#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Line {
    ll a = 0, b = 0;

    ll get(int x) {
        return a * x + b;
    }
};

int m;
vector<Line> tr;

void ins(Line z, int p, int l, int r) {
    int mid = (l + r) / 2;
    bool le = z.get(l) > tr[p].get(l);
    bool md = z.get(mid) > tr[p].get(mid);

    if (md) swap(z, tr[p]);
    if (l == r) return;

    if (le != md) ins(z, p * 2, l, mid);
    else ins(z, p * 2 + 1, mid + 1, r);
}

void add(Line z, int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return;

    if (ql <= l && r <= qr) {
        ins(z, p, l, r);
        return;
    }

    int mid = (l + r) / 2;
    add(z, ql, qr, p * 2, l, mid);
    add(z, ql, qr, p * 2 + 1, mid + 1, r);
}

void add(Line z, int l, int r) {
    l = max(l, 0);
    r = min(r, m - 1);
    if (l <= r) add(z, l, r, 1, 0, m - 1);
}

ll qry(int x, int p, int l, int r) {
    ll ans = tr[p].get(x);
    if (l == r) return ans;

    int mid = (l + r) / 2;
    if (x <= mid) ans = max(ans, qry(x, p * 2, l, mid));
    else ans = max(ans, qry(x, p * 2 + 1, mid + 1, r));

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), l(n), r(n), s;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.back()] >= a[i]) s.pop_back();
        l[i] = s.empty() ? 0 : s.back() + 1;
        s.push_back(i);
    }

    s.clear();

    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && a[s.back()] >= a[i]) s.pop_back();
        r[i] = s.empty() ? n - 1 : s.back() - 1;
        s.push_back(i);
    }

    m = n - k + 1;
    tr.resize(4 * m + 5);

    for (int i = 0; i < n; i++) {
        int x = l[i], y = r[i];
        int p = min(x, y - k + 1);
        int q = max(x, y - k + 1);
        ll h = a[i];

        add({h, h * (k - x)}, x - k + 1, p - 1);
        add({0, h * min(k, y - x + 1)}, p, q);
        add({-h, h * (y + 1)}, q + 1, y);
    }

    for (int i = 0; i < m; i++) {
        if (i) cout << ' ';
        cout << qry(i, 1, 0, m - 1);
    }

    cout << '\n';
}
