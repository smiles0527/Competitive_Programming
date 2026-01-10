#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long mn;
    int idx;
};

struct SegTree {
    int N;
    vector<Node> t;
    static Node id() { return { (long long)4e18, INT_MAX }; }
    static Node merge(const Node& L, const Node& R) {
        if (L.mn < R.mn) return L;
        if (R.mn < L.mn) return R;
        return (L.idx < R.idx) ? L : R;
    }
    SegTree(const vector<int>& a) {
        N = (int)a.size();
        t.assign(2*N, id());
        for (int i = 0; i < N; ++i) t[N+i] = { (long long)a[i], i };
        for (int i = N-1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
    }
    void update(int idx, long long val) {
        int p = idx + N;
        t[p] = { val, idx };
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegTree st(a);
    while (q--) {
        char op; cin >> op;
        if (op == 'M') {
            int l, r; cin >> l >> r;
            auto res = st.query(l-1, r-1);
            cout << res.mn << ' ' << (res.idx + 1) << '\n';
        } else if (op == 'U') {
            int i; long long x; cin >> i >> x;
            st.update(i-1, x);
        }
    }
    return 0;
}
