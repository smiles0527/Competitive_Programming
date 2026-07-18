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
    vector<int> tin(n + 1, 0), par(n + 1, 0), pare(n + 1, -1), it(n + 1, 0), outd(n + 1, 0);
    vector<pair<int,int>> ored(m);
    vector<char> done(m, 0);
    int timer = 0; bool bad = false;
    vector<int> st;

    // iterative DFS forest: back edges fixed on sight, tree edges fixed in post-order to keep each node even
    for(int s0 = 1; s0 <= n; s0++){
        if(tin[s0]) continue;
        tin[s0] = ++timer; st.pb(s0);
        while(!st.empty()){
            int u = st.back();
            if(it[u] < (int)adj[u].size()){
                auto [w, e] = adj[u][it[u]++];
                if(e == pare[u]) continue;       // parent tree edge, handled later
                if(!tin[w]){                      // tree edge
                    tin[w] = ++timer; par[w] = u; pare[w] = e;
                    st.pb(w);
                } else if(!done[e]){              // back edge: orient u -> w
                    done[e] = 1; ored[e] = {u, w}; outd[u]++;
                }
            } else {
                st.pop_back();
                int p = par[u];
                if(p){                            // post-order: fix edge u<->p
                    if(outd[u] & 1){ ored[pare[u]] = {u, p}; outd[u]++; }
                    else { ored[pare[u]] = {p, u}; outd[p]++; }
                } else if(outd[u] & 1) bad = true; // root must be even
            }
        }
    }

    if(bad){ cout << "IMPOSSIBLE\n"; return 0; }
    string out; out.reserve(m * 12);
    for(int i = 0; i < m; i++){
        out += to_string(ored[i].f); out += ' ';
        out += to_string(ored[i].s); out += '\n';
    }
    cout << out;
}