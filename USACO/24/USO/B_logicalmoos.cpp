#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<string> s(n);
    for (auto &x : s) cin >> x;

    int m = (n + 1) / 2;
    vector<int> a(m), grp(m), pf(m + 1);

    for (int i = 0; i < m; ++i) {
        a[i] = s[2 * i] == "true";
        pf[i + 1] = pf[i] + !a[i];
    }

    int g = 0;
    grp[0] = 0;

    for (int i = 1; i < m; ++i) {
        if (s[2 * i - 1] == "or") ++g;
        grp[i] = g;
    }

    ++g;

    vector<int> lo(g, m), hi(g, -1), ok(g, 1);

    for (int i = 0; i < m; ++i) {
        int id = grp[i];
        lo[id] = min(lo[id], i);
        hi[id] = max(hi[id], i);
        ok[id] &= a[i];
    }

    vector<int> pg(g + 1);
    for (int i = 0; i < g; ++i)
        pg[i + 1] = pg[i] + ok[i];

    auto all_true = [&](int l, int r) {
        return l > r || pf[r + 1] == pf[l];
    };

    string ans;
    ans.reserve(q);

    while (q--) {
        int l, r;
        string want;
        cin >> l >> r >> want;

        int L = (l - 1) / 2;
        int R = (r - 1) / 2;
        int x = grp[L], y = grp[R];

        bool outside =
            pg[x] > 0 ||
            pg[g] - pg[y + 1] > 0;

        bool tails =
            all_true(lo[x], L - 1) &&
            all_true(R + 1, hi[y]);

        bool can = want == "true"
            ? outside || tails
            : !outside;

        ans += can ? 'Y' : 'N';
    }

    cout << ans << '\n';
}