#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define int long long
#define pii pair<int,int>
#define pb push_back

const int N = 1e5+5;
const int INF = 1e18;

struct Edge {
    int to, cost;
};

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<int> t(n+1); 
    for(int i=1;i<=n;i++) cin >> t[i];

    vector<vector<Edge>> g(n+1);
    for(int i=0;i<m;i++){
        int u, v, c;
        cin >> u >> v >> c;
        g[u].pb({v,c});
        g[v].pb({u,c});
    }

    vector<int> profit(n+1, -INF);
    priority_queue<pii> pq;

    for(int i=1;i<=n;i++) {
        profit[i] = t[i];
        pq.push({profit[i], i});
    }

    while(!pq.empty()){
        auto [val, u] = pq.top(); pq.pop();
        if(val != profit[u]) continue;

        for(auto e : g[u]){
            int v = e.to, c = e.cost;
            if(val - c > profit[v]){
                profit[v] = val - c;
                pq.push({profit[v], v});
            }
        }
    }

    for(int i=1;i<=n;i++) cout << profit[i] << '\n';
    return 0;
}
