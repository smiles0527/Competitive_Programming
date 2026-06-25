#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

const int N = 50000;

int n, m, qq;
vector<int> adj[N + 1];
int low[N + 1], num[N + 1], comp[N + 1], idx, nc;
bool onst[N + 1];
vector<int> stk;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> qq;
    vector<ii> edges(m);
    for (int e = 0; e < m; e++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
        edges[e] = {a, b};
    }

    for (int i = 1; i <= n; i++) num[i] = -1;

    // iterative Tarjan SCC
    vector<int> cstk, pstk;                     // node stack, child-pointer stack
    for (int s0 = 1; s0 <= n; s0++) {
        if (num[s0] != -1) continue;
        cstk.pb(s0); pstk.pb(0);
        while (!cstk.empty()) {
            int u = cstk.back();
            int &pi = pstk.back();
            if (pi == 0) {                      // first visit
                num[u] = low[u] = idx++;
                stk.pb(u); onst[u] = true;
            }
            if (pi < (int)adj[u].size()) {
                int v = adj[u][pi++];
                if (num[v] == -1) { cstk.pb(v); pstk.pb(0); }
                else if (onst[v]) low[u] = min(low[u], num[v]);
            } else {                            // done with u
                if (low[u] == num[u]) {
                    while (true) {
                        int w = stk.back(); stk.pop_back(); onst[w] = false;
                        comp[w] = nc;
                        if (w == u) break;
                    }
                    nc++;
                }
                cstk.pop_back(); pstk.pop_back();
                if (!cstk.empty()) low[cstk.back()] = min(low[cstk.back()], low[u]);
            }
        }
    }

    // condensation (Tarjan numbers comps in reverse topo: comp 0 is a sink)
    vector<vector<int>> cadj(nc);
    for (auto &e : edges) {
        int ca = comp[e.f], cb = comp[e.s];
        if (ca != cb) cadj[ca].pb(cb);
    }

    // comp ids ascending = reverse topo order, so process ascending: successors first
    vector<bitset<N>> rc(nc);
    for (int c = 0; c < nc; c++) {
        rc[c].set(c);
        for (int d : cadj[c]) rc[c] |= rc[d];
    }

    string out; out.reserve((size_t)qq * 4);
    while (qq--) {
        int a, b; cin >> a >> b;
        out += rc[comp[a]].test(comp[b]) ? "YES\n" : "NO\n";
    }
    cout << out;
}