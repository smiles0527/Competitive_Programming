#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<pair<int,int>>> adj(N+1);
    for(int i = 0; i < N-1; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }

    vector<ll> sz(N+1, 0);
    ll total = 0;

    // iterative DFS for subtree sizes and sum of pair distances
    vector<tuple<int,int,int>> stk;
    stk.reserve(2*N);
    stk.emplace_back(1, 0, 0); // (node, parent, state)
    while(!stk.empty()) {
        auto [u, p, state] = stk.back();
        stk.pop_back();
        if(state == 0) {
            stk.emplace_back(u, p, 1);
            for(auto &pr : adj[u]) {
                int v = pr.first;
                if(v == p) continue;
                stk.emplace_back(v, u, 0);
            }
        } else {
            sz[u] = 1;
            for(auto &pr : adj[u]) {
                int v = pr.first, w = pr.second;
                if(v == p) continue;
                sz[u] += sz[v];
                ll s = sz[v];
                total += w * s * (N - s);
            }
        }
    }

    cout << total << "\n";
    return 0;
}
