#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;
using vii = vector<ii>;
const ll INF = 1e18;
int n, m;
vector<vii> adj;
ll dist[100005][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    for (int i = 1; i <= n; i++) dist[i][0] = dist[i][1] = INF;
    dist[1][0] = 0;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    pq.push({0, 1, 0}); // {d, node, used}
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        ll d = cur[0], v = cur[1], u = cur[2];
        if (d > dist[v][u]) continue;
        for (ii e : adj[v]) {
            ll to = e.first, w = e.second;
            if (d + w < dist[to][u]) { // full price, same layer
                dist[to][u] = d + w;
                pq.push({dist[to][u], to, u});
            }
            if (u == 0 && d + w / 2 < dist[to][1]) { // spend coupon, jump layer
                dist[to][1] = d + w / 2;
                pq.push({dist[to][1], to, 1});
            }
        }
    }
    cout << min(dist[n][0], dist[n][1]) << '\n';
}
