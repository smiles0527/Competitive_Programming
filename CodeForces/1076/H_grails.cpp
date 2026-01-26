#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = (int)(a[i] & 1LL);
    }

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> odd_nodes;
    odd_nodes.reserve(n);
    for (int i = 1; i <= n; i++) if (p[i] == 1) odd_nodes.push_back(i);

    if (odd_nodes.empty()) {
        cout << "NO\n";
        return;
    }

    vector<int> evenOddCnt(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            int cnt = 0;
            for (int v : g[i]) if (p[v] == 1) cnt++;
            if (cnt == 0) {
                cout << "NO\n";
                return;
            }
            evenOddCnt[i] = cnt & 1;
        }
    }

    vector<vector<int>> godd(n + 1);
    godd.assign(n + 1, {});
    for (int u = 1; u <= n; u++) {
        if (p[u] == 0) continue;
        for (int v : g[u]) if (p[v] == 1) godd[u].push_back(v);
    }

    vector<int> parent(n + 1, 0), comp_id(n + 1, -1);
    vector<int> comp_roots;
    vector<vector<int>> comps;
    int cid = 0;

    for (int start : odd_nodes) {
        if (comp_id[start] != -1) continue;
        vector<int> stackv;
        stackv.push_back(start);
        comp_id[start] = cid;
        parent[start] = 0;

        vector<int> comp;
        while (!stackv.empty()) {
            int u = stackv.back();
            stackv.pop_back();
            comp.push_back(u);
            for (int v : godd[u]) {
                if (comp_id[v] != -1) continue;
                comp_id[v] = cid;
                parent[v] = u;
                stackv.push_back(v);
            }
        }

        if (((int)comp.size() & 1) == 0) {
            cout << "NO\n";
            return;
        }

        comps.push_back(move(comp));
        comp_roots.push_back(start);
        cid++;
    }

    vector<vector<int>> dir(n + 1);
    vector<int> indeg(n + 1, 0);
    vector<int> subpar(n + 1, 0);

    vector<char> used(n + 1, 0);
    for (int idx = 0; idx < (int)comps.size(); idx++) {
        int root = comp_roots[idx];

        vector<int> st;
        vector<int> order;
        st.push_back(root);
        parent[root] = 0;
        used[root] = 1;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (int v : godd[u]) {
                if (v == parent[u]) continue;
                if (used[v]) continue;
                used[v] = 1;
                parent[v] = u;
                st.push_back(v);
            }
        }

        for (int u : order) subpar[u] = 1;
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            for (int v : godd[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                subpar[u] ^= subpar[v];
            }
        }

        for (int u : order) {
            for (int v : godd[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != u) continue;
                if (subpar[v] == 1) {
                    dir[u].push_back(v);
                    indeg[v]++;
                } else {
                    dir[v].push_back(u);
                    indeg[u]++;
                }
            }
        }
    }

    queue<int> q;
    for (int u : odd_nodes) if (indeg[u] == 0) q.push(u);

    vector<int> odd_order;
    odd_order.reserve((int)odd_nodes.size());
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        odd_order.push_back(u);
        for (int v : dir[u]) {
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }

    if ((int)odd_order.size() != (int)odd_nodes.size()) {
        cout << "NO\n";
        return;
    }

    vector<char> rem(n + 1, 0);
    queue<int> eq;
    for (int i = 1; i <= n; i++) if (p[i] == 0 && evenOddCnt[i] == 1) eq.push(i);

    vector<int> ans;
    ans.reserve(n);

    auto drain_even = [&]() {
        while (!eq.empty()) {
            int u = eq.front();
            eq.pop();
            if (rem[u]) continue;
            if (p[u] != 0) continue;
            if ((evenOddCnt[u] & 1) == 0) continue;
            rem[u] = 1;
            ans.push_back(u);
        }
    };

    drain_even();

    for (int u : odd_order) {
        drain_even();
        if (rem[u]) continue;
        rem[u] = 1;
        ans.push_back(u);
        for (int v : g[u]) {
            if (rem[v]) continue;
            if (p[v] == 0) {
                evenOddCnt[v] ^= 1;
                if (evenOddCnt[v] == 1) eq.push(v);
            }
        }
    }

    drain_even();

    if ((int)ans.size() != n) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
