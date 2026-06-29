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

const int LOG = 18;
int up[LOG][200005], dep[200005];
int mn[LOG][200005];                          // min coin-dist over 2^k nodes upward
int g[200005];                                // dist to nearest coin

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) cin >> c[i];
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }

    // multi-source BFS from coins -> g
    for(int i = 1; i <= n; i++) g[i] = -1;
    vector<int> bq; bq.reserve(n);
    for(int i = 1; i <= n; i++) if(c[i]){ g[i] = 0; bq.pb(i); }
    for(int h = 0; h < (int)bq.size(); h++){
        int u = bq[h];
        for(int w : adj[u]) if(g[w] < 0){ g[w] = g[u] + 1; bq.pb(w); }
    }

    // root at 1, iterative BFS: parent/depth
    vector<char> vis(n + 1, 0);
    vector<int> bfs; bfs.reserve(n);
    dep[1] = 0; up[0][1] = 1; vis[1] = 1; bfs.pb(1);
    for(int h = 0; h < (int)bfs.size(); h++){
        int u = bfs[h];
        for(int w : adj[u]) if(!vis[w]){
            vis[w] = 1; dep[w] = dep[u] + 1; up[0][w] = u; bfs.pb(w);
        }
    }
    for(int v = 1; v <= n; v++) mn[0][v] = g[v];
    for(int k = 1; k < LOG; k++)
        for(int v = 1; v <= n; v++){
            up[k][v] = up[k-1][ up[k-1][v] ];
            mn[k][v] = min(mn[k-1][v], mn[k-1][ up[k-1][v] ]);
        }

    auto lca = [&](int u, int v) -> int {
        if(dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for(int k = 0; k < LOG; k++) if(d >> k & 1) u = up[k][u];
        if(u == v) return u;
        for(int k = LOG - 1; k >= 0; k--) if(up[k][u] != up[k][v]){ u = up[k][u]; v = up[k][v]; }
        return up[0][u];
    };

    auto qmin = [&](int u, int v) -> int {      // min g over path u..v inclusive
        int res = INT_MAX;
        if(dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for(int k = 0; k < LOG; k++) if(d >> k & 1){ res = min(res, mn[k][u]); u = up[k][u]; }
        if(u == v) return min(res, g[u]);
        for(int k = LOG - 1; k >= 0; k--) if(up[k][u] != up[k][v]){
            res = min({res, mn[k][u], mn[k][v]}); u = up[k][u]; v = up[k][v];
        }
        return min({res, g[u], g[v], g[ up[0][u] ]});   // children + lca
    };

    string out; out.reserve(q * 7);
    for(int i = 0; i < q; i++){
        int a, b; cin >> a >> b;
        int l = lca(a, b);
        ll dist = dep[a] + dep[b] - 2LL * dep[l];
        out += to_string(dist + 2LL * qmin(a, b));
        out += '\n';
    }
    cout << out;
}