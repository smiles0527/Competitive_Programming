#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    ll length, cost;
};

struct DSU {
    vector<int> parent;
    DSU(int n): parent(n+1) {
        for(int i = 0; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        parent[a] = b;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for(int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].length >> edges[i].cost;
    }

    sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
        if(a.length == b.length) return a.cost < b.cost;
        return a.length < b.length;
    });

    DSU dsu(n);
    vector<vector<pair<int,ll>>> graph(n+1);
    ll totalCost = 0;

    auto pathLongerThan = [&](int src, int dst, ll limit) {
        const ll INF = numeric_limits<ll>::max() / 2;
        vector<ll> dist(n+1, INF);
        vector<bool> seen(n+1, false);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if(seen[node]) continue;
            seen[node] = true;
            if(node == dst) break;
            for(auto &e : graph[node]) {
                int to = e.first;
                ll w = e.second;
                if(dist[to] > d + w) {
                    dist[to] = d + w;
                    pq.push({dist[to], to});
                }
            }
        }
        return dist[dst] > limit;
    };

    for(auto &e : edges) {
        if(dsu.unite(e.u, e.v) || pathLongerThan(e.u, e.v, e.length)) {
            totalCost += e.cost;
            graph[e.u].push_back({e.v, e.length});
            graph[e.v].push_back({e.u, e.length});
        }
    }

    cout << totalCost << "\n";
    return 0;
}
