#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long mn;
    int g;
    int cnt;
};

struct SegTree {
    int N;
    vector<Node> t;
    static Node id() { return { (long long)4e18, 0, 0 }; }
    static int G(int a, int b) { return std::gcd(a, b); }
    static Node merge(const Node& L, const Node& R) {
        if (L.mn == (long long)4e18) return R;
        if (R.mn == (long long)4e18) return L;
        Node res;
        res.mn = min(L.mn, R.mn);
        res.g = G(L.g, R.g);
        res.cnt = 0;
        if (L.g == res.g) res.cnt += L.cnt;
        if (R.g == res.g) res.cnt += R.cnt;
        return res;
    }
    SegTree(const vector<int>& a) {
        N = (int)a.size();
        t.assign(2*N, id());
        for (int i = 0; i < N; ++i) t[N+i] = { a[i], a[i], 1 };
        for (int i = N-1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
    }
    void update(int idx, int val) {
        int p = idx + N;
        t[p] = { val, val, 1 };
        for (p >>= 1; p; p >>= 1) t[p] = merge(t[p<<1], t[p<<1|1]);
    }
    Node query(int l, int r) {
        Node L = id(), R = id();
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, t[l++]);
            if (r & 1) R = merge(t[--r], R);
        }
        return merge(L, R);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegTree st(a);
    while (m--) {
        char op; cin >> op;
        if (op == 'C') {
            int x, v; cin >> x >> v;
            st.update(x-1, v);
        } else if (op == 'M') {
            int l, r; cin >> l >> r;
            cout << st.query(l-1, r-1).mn << '\n';
        } else if (op == 'G') {
            int l, r; cin >> l >> r;
            cout << st.query(l-1, r-1).g << '\n';
        } else if (op == 'Q') {
            int l, r; cin >> l >> r;
            cout << st.query(l-1, r-1).cnt << '\n';
        }
    }
    return 0;
}
