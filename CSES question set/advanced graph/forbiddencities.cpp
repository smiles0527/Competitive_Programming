#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

int n, m, q;
vector<vii> adj;          // (to, edge id)
vector<vector<int>> bct;  // block-cut tree

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    adj.assign(n + 1, {});
    for(int e = 0; e < m; e++){ int a, b; cin >> a >> b; if(a == b) continue; adj[a].pb({b, e}); adj[b].pb({a, e}); }

    vector<int> disc(n + 1, 0), low(n + 1, 0), vstk;
    bct.assign(n + 1, {});                       // block ids start at n+1
    int timer = 0, blocks = 0;
    vstk.reserve(n);

    // iterative Tarjan BCC; frames carry (u, parentEdge, edgePtr)
    vector<int> su, spe, si;
    su.reserve(n); spe.reserve(n); si.reserve(n);
    for(int s = 1; s <= n; s++) if(!disc[s]){
        su.pb(s); spe.pb(-1); si.pb(0);
        disc[s] = low[s] = ++timer; vstk.pb(s);
        while(!su.empty()){
            int u = su.back();
            int &i = si.back();
            if(i < (int)adj[u].size()){
                auto [v, id] = adj[u][i++];
                if(id == spe.back()) continue;   // skip the tree edge we arrived by (handles multi-edges)
                if(!disc[v]){
                    disc[v] = low[v] = ++timer; vstk.pb(v);
                    su.pb(v); spe.pb(id); si.pb(0);
                } else low[u] = min(low[u], disc[v]);
            } else {
                su.pop_back(); spe.pop_back(); si.pop_back();
                if(!su.empty()){
                    int p = su.back();
                    low[p] = min(low[p], low[u]);
                    if(low[u] >= disc[p]){        // p closes a biconnected block containing u's branch
                        ++blocks; int bn = n + blocks;
                        bct.pb({});
                        int x;
                        do{ x = vstk.back(); vstk.pop_back(); bct[bn].pb(x); bct[x].pb(bn); }while(x != u);
                        bct[bn].pb(p); bct[p].pb(bn);
                    }
                }
            }
        }
        vstk.clear();                            // root remnant
    }

    int N = n + blocks;
    int LOG = 1; while((1 << LOG) < N) LOG++;
    vector<vector<int>> up(LOG, vector<int>(N + 1, 0));
    vector<int> dep(N + 1, -1), order;
    order.reserve(N);
    for(int r = 1; r <= N; r++) if(dep[r] == -1){
        dep[r] = 0; up[0][r] = r;                 // self-parent at root saturates lifting
        int st = order.size(); order.pb(r);
        for(size_t h = st; h < order.size(); h++){
            int u = order[h];
            for(int v : bct[u]) if(dep[v] == -1){ dep[v] = dep[u] + 1; up[0][v] = u; order.pb(v); }
        }
    }
    for(int k = 1; k < LOG; k++) for(int v = 1; v <= N; v++) up[k][v] = up[k - 1][up[k - 1][v]];

    auto lca = [&](int a, int b){
        if(dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];
        for(int k = 0; k < LOG; k++) if(d >> k & 1) a = up[k][a];
        if(a == b) return a;
        for(int k = LOG - 1; k >= 0; k--) if(up[k][a] != up[k][b]){ a = up[k][a]; b = up[k][b]; }
        return up[0][a];
    };
    auto onPath = [&](int a, int b, int c){      // dist(a,c)+dist(c,b)==dist(a,b)
        int dab = dep[a] + dep[b] - 2 * dep[lca(a, b)];
        int dac = dep[a] + dep[c] - 2 * dep[lca(a, c)];
        int dcb = dep[c] + dep[b] - 2 * dep[lca(c, b)];
        return dac + dcb == dab;
    };

    string out;
    out.reserve(4 * q);
    while(q--){
        int a, b, c; cin >> a >> b >> c;
        out += onPath(a, b, c) ? "NO\n" : "YES\n";   // c interior to a-b path ⇒ c is a separating cut vertex
    }
    cout << out;
}   