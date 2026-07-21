#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;
using vii = vector<ii>;
const int MOD = 1e9 + 7;
const ll INF = 1e18;
int n, m;
vector<vii> adj;
ll dist[100005];
ll ways[100005], mn[100005], mx[100005];

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
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        mn[i] = INF;
    }
    dist[1] = 0;
    ways[1] = 1;
    mn[1] = 0;
    mx[1] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        ii cur = pq.top();
        pq.pop();
        ll d = cur.first, v = cur.second;
        if (d > dist[v]) continue;
        for (ii e : adj[v]) {
            ll to = e.first, w = e.second;
            ll nd = d + w;
            if (nd < dist[to]) {
                dist[to] = nd;
                ways[to] = ways[v];
                mn[to] = mn[v] + 1;
                mx[to] = mx[v] + 1;
                pq.push({nd, to});
            } else if (nd == dist[to]) {
                ways[to] = (ways[to] + ways[v]) % MOD;
                mn[to] = min(mn[to], mn[v] + 1);
                mx[to] = max(mx[to], mx[v] + 1);
            }
        }
    }
    cout << dist[n] << ' ' << ways[n] << ' ' << mn[n] << ' ' << mx[n] << '\n';
}
