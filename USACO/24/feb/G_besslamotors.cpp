#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using State = tuple<ll, int, int>;

struct Edge {
    int v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c, k;
    ll r;
    cin >> n >> m >> c >> r >> k;

    vector<vector<Edge>> g(n);

    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    priority_queue<State, vector<State>, greater<State>> pq;

    vector<array<int, 10>> src(n);
    vector<unsigned char> cnt(n);

    for (int s = 0; s < c; ++s)
        pq.emplace(0, s, s);

    while (!pq.empty()) {
        auto [d, u, s] = pq.top();
        pq.pop();

        if (d > r || cnt[u] == k) continue;

        bool seen = false;
        for (int i = 0; i < cnt[u]; ++i)
            if (src[u][i] == s) {
                seen = true;
                break;
            }

        if (seen) continue;

        src[u][cnt[u]++] = s;

        for (auto [v, w] : g[u]) {
            if (cnt[v] < k && w <= r - d)
                pq.emplace(d + w, v, s);
        }
    }

    vector<int> ans;
    for (int u = c; u < n; ++u)
        if (cnt[u] == k)
            ans.push_back(u + 1);

    cout << ans.size() << '\n';
    for (int u : ans) cout << u << '\n';
}