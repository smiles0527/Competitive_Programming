#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1), pos(n + 1), s(n + 1), ans(n + 1), vis(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        s[i] = pos[b[i]];
    }

    if (n == 2) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<array<int, 2>> two;
    vector<vector<int>> big;

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;

        vector<int> cyc;
        int v = i;

        while (!vis[v]) {
            vis[v] = 1;
            cyc.push_back(v);
            v = s[v];
        }

        int m = cyc.size();

        if (m == 2) {
            two.push_back({cyc[0], cyc[1]});
        } else {
            for (int j = 0; j < m; j++) ans[cyc[j]] = cyc[(j + 2) % m];
            big.push_back(cyc);
        }
    }

    int z = two.size();

    if (z >= 2) {
        for (int i = 0; i < z; i++) {
            int j = (i + 1) % z;
            ans[two[i][0]] = two[j][0];
            ans[two[i][1]] = two[j][1];
        }
    } else if (z == 1) {
        auto p = two[0];
        auto &c = big.back();

        int x = p[0], y = p[1], m = c.size();

        ans[x] = c[0];
        ans[y] = c[1];

        for (int i = 0; i + 2 < m; i++) ans[c[i]] = c[i + 2];

        ans[c[m - 2]] = x;
        ans[c[m - 1]] = y;
    }

    for (int i = 1; i <= n; i++) cout << a[ans[i]] << ' ';
    cout << '\n';
}