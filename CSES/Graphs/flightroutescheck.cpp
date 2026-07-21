#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, radj;
bool vis[100005];
void bfs(vector<vector<int>>& g, int src) {
    for (int i = 1; i <= n; i++) vis[i] = false;
    queue<int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v])
            if (!vis[to]) {
                vis[to] = true;
                q.push(to);
            }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    radj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }
    bfs(adj, 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            cout << "NO\n" << 1 << ' ' << i << '\n';
            return 0;
        }
    bfs(radj, 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            cout << "NO\n" << i << ' ' << 1 << '\n';
            return 0;
        }
    cout << "YES\n";
}
