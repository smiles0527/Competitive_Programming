#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;
const ll INF = 1e18;
int n, m;
struct Edge {
    int to;
    ll cap;
};
vector<Edge> es;
vector<int> g[505];
int level_[505], it_[505];
int ea[1005], eb[1005]; // original street endpoints
void add(int a, int b, ll c) {
    g[a].push_back(es.size());
    es.push_back({b, c});
    g[b].push_back(es.size());
    es.push_back({a, c}); // undirected: both directions cap 1
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ea[i] = a;
        eb[i] = b;
        add(a, b, 1);
    }
    while (bfs(1, n)) {
        for (int i = 1; i <= n; i++) it_[i] = 0;
        while (dfs(1, n, INF) > 0);
    }
    vector<int> side(n + 1, 0);
    queue<int> q;
    q.push(1);
    side[1] = 1; // residual reachable from source
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int id : g[v])
            if (es[id].cap > 0 && !side[es[id].to]) {
                side[es[id].to] = 1;
                q.push(es[id].to);
            }
    }
    vector<ii> cut;
    for (int i = 0; i < m; i++)
        if (side[ea[i]] != side[eb[i]]) // street crosses the cut
            cut.push_back({ea[i], eb[i]});
    cout << cut.size() << '\n';
    for (auto& e : cut) cout << e.first << ' ' << e.second << '\n';
}
