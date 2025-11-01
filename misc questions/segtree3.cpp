#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum;
    long long pref;
};

struct SegTree {
    int N;
    vector<Node> t;
    static Node id() { return {0, (long long)-4e18}; }
    static Node merge(const Node& L, const Node& R) {
        return { L.sum + R.sum, max(L.pref, L.sum + R.pref) };
    }
    SegTree(const vector<int>& a) {
        N = (int)a.size();
        t.assign(2*N, id());
        for (int i = 0; i < N; ++i) t[N+i] = { (long long)a[i], (long long)a[i] };
        for (int i = N-1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
    }
    void update(int idx, long long val) {
        int p = idx + N;
        t[p] = { val, val };
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
        if (op == 'P') {
            int l, r; cin >> l >> r;
            cout << st.query(l-1, r-1).pref << '\n';
        } else if (op == 'U') {
            int i; long long x; cin >> i >> x;
            st.update(i-1, x);
        }
    }
    return 0;
}
