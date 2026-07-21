#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;
int n, m;
struct Edge {
    int to;
    ll cap;
};
vector<Edge> es;
vector<int> g[505];
int level_[505], it_[505];
void add(int a, int b, ll c) {
    g[a].push_back(es.size());
    es.push_back({b, c});
    g[b].push_back(es.size());
    es.push_back({a, 0});
}
bool bfs(int s, int t) {
    for (int i = 1; i <= n; i++) level_[i] = -1;
    queue<int> q;
    q.push(s);
    level_[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int id : g[v])
            if (es[id].cap > 0 && level_[es[id].to] < 0) {
                level_[es[id].to] = level_[v] + 1;
                q.push(es[id].to);
            }
    }
    return level_[t] >= 0;
}
ll dfs(int v, int t, ll pushed) {
    if (v == t) return pushed;
    for (int& i = it_[v]; i < (int)g[v].size(); i++) {
        int id = g[v][i], to = es[id].to;
        if (es[id].cap > 0 && level_[to] == level_[v] + 1) {
            ll d = dfs(to, t, min(pushed, es[id].cap));
            if (d > 0) {
                es[id].cap -= d;
                es[id ^ 1].cap += d;
                return d;
            }
        }
    }
    return 0;
}
bool extractPath(int v, int t, vector<int>& route, vector<int>& seen) {
    if (v == t) return true;
    seen[v] = true;
    for (int id : g[v]) {
        if ((id % 2 == 0) && es[id].cap == 0 && es[id ^ 1].cap == 1 && !seen[es[id].to]) {
            es[id].cap = 1;
            es[id ^ 1].cap = 0;
            route.push_back(es[id].to);
            if (extractPath(es[id].to, t, route, seen)) return true;
            route.pop_back();
            es[id].cap = 0;
            es[id ^ 1].cap = 1;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b, 1);
    }
    int flow = 0;
    while (bfs(1, n)) {
        for (int i = 1; i <= n; i++) it_[i] = 0;
        while (dfs(1, n, INF) > 0) flow++;
    }
    cout << flow << '\n';
    vector<vector<int>> paths;
    for (int p = 0; p < flow; p++) {
        vector<int> route{1}, seen(n + 1, 0);
        extractPath(1, n, route, seen);
        paths.push_back(route);
    }
    for (auto& r : paths) {
        cout << r.size() << '\n';
        for (int i = 0; i < (int)r.size(); i++)
            cout << r[i] << (i + 1 == (int)r.size() ? '\n' : ' ');
    }
}
