#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<vector<pair<int,int>>> g(N + 1);
    for (int i = 0; i < M; ++i) {
        int A, B, L;
        cin >> A >> B >> L;
        g[A].push_back({B, L});
    }
    
    const long long INF = (1LL<<62);
    vector<long long> d1(N + 1, INF), d2(N + 1, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    
    d1[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du > d2[u]) continue;
        for (auto [v, w] : g[u]) {
            long long nd = du + w;
            if (nd < d1[v]) {
                d2[v] = d1[v];
                d1[v] = nd;
                pq.push({d1[v], v});
            } else if (nd > d1[v] && nd < d2[v]) {
                d2[v] = nd;
                pq.push({d2[v], v});
            }
        }
    }
    
    cout << (d2[N] == INF ? -1 : d2[N]) << "\n";
    return 0;
}
