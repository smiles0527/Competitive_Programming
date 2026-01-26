#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
vector<int> sz;
vector<bool> used;

int dfs_size(int v, int p) {
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            sz[v] += dfs_size(u, v);
        }
    }
    return sz[v];
}

int dfs_centroid(int v, int p, int tot) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > tot / 2) {
            return dfs_centroid(u, v, tot);
        }
    }
    return v;
}

int ask(int a, int b) {
    cout << "? " << a << " " << b << "\n";
    cout.flush();
    int res;
    cin >> res;
    if (res == -1) exit(0);
    return res;
}

int solve(int v) {
    int tot = dfs_size(v, -1);
    int c = dfs_centroid(v, -1, tot);

    if (ask(c, c)) {
        cout << "! " << c << "\n";
        cout.flush();
        exit(0);
    }

    used[c] = true;
    for (int u : g[c]) {
        if (!used[u]) {
            if (ask(u, u)) {
                return solve(u);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        g.assign(n + 1, {});
        sz.assign(n + 1, 0);
        used.assign(n + 1, false);

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        solve(1);
    }
    return 0;
}
