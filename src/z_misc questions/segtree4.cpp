#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum;
};

struct SegTree {
    int N;
    vector<Node> t;
    static Node id() { return {0}; }
    static Node merge(const Node& L, const Node& R) {
        return { L.sum + R.sum };
    }
    SegTree(int n) {
        N = n;
        t.assign(2*N, id());
    }
    void add(int idx, long long delta) {
        int p = idx + N - 1;
        t[p].sum += delta;
        for (p >>= 1; p; p >>= 1) t[p] = merge(t[p<<1], t[p<<1|1]);
    }
    long long range_sum(int l, int r) {
        Node L = id(), R = id();
        for (l += N - 1, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = merge(L, t[l++]);
            if (r & 1) R = merge(t[--r], R);
        }
        return merge(L, R).sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<pair<int,int>>> qs(n+1);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        qs[r].push_back({l, i});
    }
    SegTree st(n);
    vector<int> last(n+1, 0), second_last(n+1, 0);
    vector<int> ans(q);
    for (int r = 1; r <= n; ++r) {
        int v = a[r];
        if (last[v]) {
            st.add(last[v], -1);
            if (second_last[v]) st.add(second_last[v], +1);
            second_last[v] = last[v];
        }
        last[v] = r;
        st.add(r, +1);
        if (second_last[v]) st.add(second_last[v], -1);
        for (auto &pr : qs[r]) {
            int l = pr.first, id = pr.second;
            ans[id] = (int)st.range_sum(l, r);
        }
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
