#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)9e18;

void dijkstra(int s, vector<ll>& dist, const vector<vector<tuple<int, ll, int>>>& adj) {
    fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d !=    dist[u]) continue;
        for (const auto& t : adj[u]) {
            int v; ll w; int id;
            tie(v, w, id) = t;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({ dist[v], v });
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<int> U(M), V(M);
    vector<ll> L(M), C(M);
    for (int i = 0; i < M; ++i) {
        cin >> U[i] >> V[i] >> L[i] >> C[i];
        U[i]--; V[i]--;
    }
    vector<vector<tuple<int, ll, int>>> adj(N);
    for (int i = 0; i < M; ++i) {
        adj[U[i]].push_back({ V[i], L[i], i });
        adj[V[i]].push_back({ U[i], L[i], i });
    }
    vector<char> used(M, 0);
    vector<ll> dist(N);
    for (int s = 0; s < N; ++s) {
        dijkstra(s, dist, adj);
        for (int v = 0; v < N; ++v) {
            if (v == s) continue;
            if (dist[v] == INF) continue;
            ll bestCost = INF;
            int bestId = -1;
            for (const auto& t : adj[v]) {
                int u; ll w; int id;
                tie(u, w, id) = t;
                if (dist[u] + w == dist[v]) {
                    if (C[id] < bestCost) {
                        bestCost = C[id];
                        bestId = id;
                    }
                }
            }
            if (bestId != -1) used[bestId] = 1;
        }
    }
    ll ans = 0;
    for (int i = 0; i < M; ++i) if (used[i]) ans += C[i];
    cout << ans << "\n";
    return 0;
}
