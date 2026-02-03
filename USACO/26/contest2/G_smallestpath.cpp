#include <bits/stdc++.h> //O (N M + M log M)
using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    vector<vector<pair<int,char>>> g(n+1);
    for(int i=0;i<m;i++) {
        int u,v; char c; cin >> u >> v >> c;
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }

    vector<int> d(n+1,-1);
    vector<int> cur = {1};
    d[1] = 0;

    for(int len=1; !cur.empty(); len++) {
        char mc = '{';

        for(int u : cur) for(auto& e : g[u]) mc = min(mc, e.second);
        if(mc == '{') break;

        vector<int> nxt;
        
        for(int u : cur) for(auto& e : g[u])
            if(e.second == mc && d[e.first] == -1) {
                d[e.first] = len;
                nxt.push_back(e.first);
            }

        sort(nxt.begin(), nxt.end()); // p
        nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
        cur = nxt;
    }

    for(int i=1;i<=n;i++) cout << d[i] << " \n"[i==n];
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();

    return 0;
}