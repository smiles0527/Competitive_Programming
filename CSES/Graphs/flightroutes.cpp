#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vii = vector<ii>;
int n, m, k;
vector<vii> adj;
int cnt[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, 1});
    vi ans;
    while (!pq.empty()) {
        ii cur = pq.top();
        pq.pop();
        ll d = cur.first, v = cur.second;
        if (cnt[v] >= k) continue;
        cnt[v]++;
        if (v == n) ans.push_back(d);
        if (cnt[v] == k && v == n) break; // collected all k for target
        for (ii e : adj[v]) {
            ll to = e.first, w = e.second;
            if (cnt[to] < k) pq.push({d + w, to});
        }
    }
    for (int i = 0; i < k; i++) cout << ans[i] << (i + 1 == k ? '\n' : ' ');
}
