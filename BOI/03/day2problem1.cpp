#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> root, rnk;
    DSU(int n): root(n), rnk(n, 1) {
        for(int i = 0; i < n; ++i) root[i] = i;
    }
    int find(int x) {
        if (root[x] == x) return x;
        return root[x] = find(root[x]);
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rnk[rx] > rnk[ry]) root[ry] = rx;
        else if (rnk[rx] < rnk[ry]) root[rx] = ry;
        else {
            root[ry] = rx;
            rnk[rx]++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    DSU uf(N + 1);
    vector<vector<int>> enemies(N + 1);

    for (int i = 0; i < M; ++i) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == 'F') {
            uf.unite(a, b);
        } else {
            enemies[a].push_back(b);
            enemies[b].push_back(a);
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int e : enemies[i]) {
            for (int f : enemies[e]) {
                uf.unite(i, f);
            }
        }
    }

    unordered_set<int> groups;
    for (int i = 1; i <= N; ++i) {
        groups.insert(uf.find(i));
    }

    cout << groups.size() << "\n";
    return 0;
}
