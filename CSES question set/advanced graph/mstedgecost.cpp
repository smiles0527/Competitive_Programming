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
int p[100005], sz[100005];
int fnd(int x){ while(x != p[x]) x = p[x] = p[p[x]]; return x; }

int up[LOG][100005], dep[100005];
int mx[LOG][100005];                         // max edge weight over 2^k jump

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<array<int,4>> e(m);               // (w, a, b, id) ascending for Kruskal
    vector<array<int,3>> qe(m);              // (a, b, w) by id for queries
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        e[i] = {w, a, b, i}; qe[i] = {a, b, w};
    }
    sort(e.begin(), e.end());                 // light -> heavy
    for(int i = 1; i <= n; i++){ p[i] = i; sz[i] = 1; }

    vector<vector<pair<int,int>>> g(n + 1);   // MST adjacency (to, w)
    ll T = 0;
    for(auto &ed : e){
        int w = ed[0], a = fnd(ed[1]), b = fnd(ed[2]);
        if(a == b) continue;
        T += w; g[ed[1]].pb({ed[2], w}); g[ed[2]].pb({ed[1], w});
        if(sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
    }

    // root at 1, iterative BFS: set parent/depth and the edge weight to parent
    vector<char> vis(n + 1, 0);
    vector<int> bfs; bfs.reserve(n);
    dep[1] = 0; up[0][1] = 1; mx[0][1] = 0; vis[1] = 1; bfs.pb(1);
    for(int h = 0; h < (int)bfs.size(); h++){
        int u = bfs[h];
        for(auto [w, c] : g[u]) if(!vis[w]){
            vis[w] = 1; dep[w] = dep[u] + 1; up[0][w] = u; mx[0][w] = c; bfs.pb(w);
        }
    }
    for(int k = 1; k < LOG; k++)
        for(int v = 1; v <= n; v++){
            up[k][v] = up[k-1][ up[k-1][v] ];
            mx[k][v] = max(mx[k-1][v], mx[k-1][ up[k-1][v] ]);
        }

    auto qmax = [&](int u, int v) -> int {
        int res = 0;
        if(dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for(int k = 0; k < LOG; k++) if(d >> k & 1){ res = max(res, mx[k][u]); u = up[k][u]; }
        if(u == v) return res;
        for(int k = LOG - 1; k >= 0; k--) if(up[k][u] != up[k][v]){
            res = max({res, mx[k][u], mx[k][v]}); u = up[k][u]; v = up[k][v];
        }
        return max({res, mx[0][u], mx[0][v]});
    };

    string out; out.reserve(m * 8);
    for(int i = 0; i < m; i++){
        int a = qe[i][0], b = qe[i][1], w = qe[i][2];
        out += to_string(T - (ll)qmax(a, b) + w);   // tree edge => qmax==w => T
        out += '\n';
    }
    cout << out;
}