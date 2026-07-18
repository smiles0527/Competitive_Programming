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
    vector<vector<pair<int,int>>> adj(n + 1);   // (to, edge id)
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].pb({b, i}); adj[b].pb({a, i});
    }
    vector<int> tin(n + 1, 0), low(n + 1, 0), par(n + 1, 0), pare(n + 1, -1), it(n + 1, 0);
    vector<pair<int,int>> ored(m);
    int timer = 0; bool bad = false;

    // iterative DFS from 1: tree edges down, back edges up; flag bridges
    vector<int> st;
    tin[1] = low[1] = ++timer; st.pb(1);
    while(!st.empty()){
        int u = st.back();
        if(it[u] < (int)adj[u].size()){
            auto [w, e] = adj[u][it[u]++];
            if(e == pare[u]) continue;          // skip single parent edge once
            if(!tin[w]){                         // tree edge
                ored[e] = {u, w};
                tin[w] = low[w] = ++timer; par[w] = u; pare[w] = e;
                st.pb(w);
            } else {                             // non-tree: orient desc -> anc
                low[u] = min(low[u], tin[w]);
                ored[e] = (tin[u] > tin[w]) ? make_pair(u, w) : make_pair(w, u);
            }
        } else {
            st.pop_back();
            int p = par[u];
            if(p){
                low[p] = min(low[p], low[u]);
                if(low[u] > tin[p]) bad = true;  // bridge
            }
        }
    }
    for(int v = 1; v <= n; v++) if(!tin[v]) bad = true;   // disconnected

    if(bad){ cout << "IMPOSSIBLE\n"; return 0; }
    string out; out.reserve(m * 12);
    for(int i = 0; i < m; i++){
        out += to_string(ored[i].f); out += ' ';
        out += to_string(ored[i].s); out += '\n';
    }
    cout << out;
}