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
int g[200005];                                // f(v): dist up to first node in coin Steiner tree

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> c(n + 1);
    int root = 1;
    for(int i = 1; i <= n; i++){ cin >> c[i]; if(c[i]) root = i; }   // root at a coin
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }

    // root at a coin, iterative BFS: parent/depth
    vector<char> vis(n + 1, 0);
    vector<int> bfs; bfs.reserve(n);
    dep[root] = 0; up[0][root] = root; vis[root] = 1; bfs.pb(root);
    for(int h = 0; h < (int)bfs.size(); h++){
        int u = bfs[h];
        for(int w : adj[u]) if(!vis[w]){
            vis[w] = 1; dep[w] = dep[u] + 1; up[0][w] = u; bfs.pb(w);
        }
    }

    // inTc[v] = subtree(v) contains a coin  (reverse BFS order)
    vector<char> inTc(n + 1, 0);
    for(int i = (int)bfs.size() - 1; i >= 0; i--){
        int u = bfs[i];
        if(c[u]) inTc[u] = 1;
        if(u != root && inTc[u]) inTc[ up[0][u] ] = 1;
    }
    int Ec = -1;                              // |Tc| - 1
    for(int i = 1; i <= n; i++) Ec += inTc[i];

    // f(v): pendant-chain length to Tc  (forward BFS order)
    g[root] = 0;
    for(int i = 1; i < (int)bfs.size(); i++){
        int u = bfs[i];
        g[u] = inTc[u] ? 0 : g[ up[0][u] ] + 1;
    }

    for(int k = 1; k < LOG; k++)
        for(int v = 1; v <= n; v++)
            up[k][v] = up[k-1][ up[k-1][v] ];

    auto lca = [&](int u, int v) -> int {
        if(dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for(int k = 0; k < LOG; k++) if(d >> k & 1) u = up[k][u];
        if(u == v) return u;
        for(int k = LOG - 1; k >= 0; k--) if(up[k][u] != up[k][v]){ u = up[k][u]; v = up[k][v]; }
        return up[0][u];
    };

    string out; out.reserve(q * 8);
    for(int i = 0; i < q; i++){
        int a, b; cin >> a >> b;
        int l = lca(a, b);
        ll Ew = (ll)Ec + g[a] + g[b] - g[l];          // |E(W)|
        ll d  = dep[a] + dep[b] - 2LL * dep[l];
        out += to_string(2 * Ew - d);                  // 2E - dist
        out += '\n';
    }
    cout << out;
}