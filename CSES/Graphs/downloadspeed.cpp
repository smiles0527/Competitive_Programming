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
        for (int id : g[v]) {
            if (es[id].cap > 0 && level_[es[id].to] < 0) {
                level_[es[id].to] = level_[v] + 1;
                q.push(es[id].to);
            }
        }
    }
    return level_[t] >= 0;
}
ll dfs(int v, int t, ll pushed) {
    if (v == t) return pushed;
    for (int& i = it_[v]; i < (int)g[v].size(); i++) {
        int id = g[v][i];
        int to = es[id].to;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    ll flow = 0;
    while (bfs(1, n)) {
        for (int i = 1; i <= n; i++) it_[i] = 0;
        ll f;
        while ((f = dfs(1, n, INF)) > 0) flow += f;
    }
    cout << flow << '\n';
}
