#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }
    const int INF = 1e9;
    vector<int> dist(n + 1), par(n + 1);
    int ans = INF;

    // BFS from each source; non-parent visited neighbor closes a cycle
    for(int s0 = 1; s0 <= n; s0++){
        fill(dist.begin(), dist.end(), -1);
        dist[s0] = 0; par[s0] = 0;
        queue<int> q; q.push(s0);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int w : adj[u]){
                if(dist[w] < 0){
                    dist[w] = dist[u] + 1; par[w] = u; q.push(w);
                } else if(w != par[u]){
                    ans = min(ans, dist[u] + dist[w] + 1);
                }
            }
        }
    }

    cout << (ans == INF ? -1 : ans) << '\n';
}