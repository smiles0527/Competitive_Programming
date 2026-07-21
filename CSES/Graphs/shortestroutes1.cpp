#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;
using vii = vector<ii>;
int n, m;
vector<vii> adj;
ll dist[100005];

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
    for (int i = 1; i <= n; i++) dist[i] = LLONG_MAX;
    dist[1] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        ii cur = pq.top();
        pq.pop();
        ll d = cur.first, v = cur.second;
        if (d > dist[v]) continue;
        for (ii e : adj[v]) {
            ll to = e.first, w = e.second;
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                pq.push({dist[to], to});
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << dist[i] << (i == n ? '\n' : ' ');
}
