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

const int N = 100005;
vector<ii> adj[N];                              // (neighbor, edge id)
int num[N], low[N], idx;
int pe[N];                                      // parent edge id, to skip once
vii bridges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ii> edges(m);
    for (int e = 0; e < m; e++) {
        int a, b; cin >> a >> b;
        adj[a].pb({b, e}); adj[b].pb({a, e});
        edges[e] = {a, b};
    }

    for (int i = 1; i <= n; i++) num[i] = -1;

    vector<int> cstk, pstk, est;                // node, child-ptr, parent-edge stacks
    for (int s0 = 1; s0 <= n; s0++) {
        if (num[s0] != -1) continue;
        cstk.pb(s0); pstk.pb(0); est.pb(-1);
        while (!cstk.empty()) {
            int u = cstk.back();
            int &pi = pstk.back();
            if (pi == 0) { num[u] = low[u] = idx++; }
            if (pi < (int)adj[u].size()) {
                auto [v, eid] = adj[u][pi++];
                if (eid == est.back()) continue;        // skip the edge we came in on
                if (num[v] == -1) {
                    cstk.pb(v); pstk.pb(0); est.pb(eid);
                } else {
                    low[u] = min(low[u], num[v]);       // back-edge
                }
            } else {                                    // finished u
                cstk.pop_back(); pstk.pop_back();
                int eid = est.back(); est.pop_back();
                if (!cstk.empty()) {
                    int p = cstk.back();
                    low[p] = min(low[p], low[u]);
                    if (low[u] > num[p]) bridges.pb(edges[eid]);  // tree edge is a bridge
                }
            }
        }
    }

    string out = to_string(bridges.size()) + "\n";
    for (auto &e : bridges) { out += to_string(e.f); out += ' '; out += to_string(e.s); out += '\n'; }
    cout << out;
}