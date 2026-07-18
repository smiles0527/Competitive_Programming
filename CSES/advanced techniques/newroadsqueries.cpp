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

int par[400005];                                // DSU over reconstruction-tree nodes
int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }

int LOG;
vector<int> up[400005];                         // binary lifting (per-node ancestor table)
int dep[400005], day_[400005], top[400005];     // node creation day; current tree-root rep
vector<int> children[400005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    int tot = n;                                // cities are nodes 1..n; internal nodes after
    // vector<int> root(n + 1);                 // OOB: nn can reach 2n-1 -> heap corruption
    vector<int> root(2 * n + 5);                // internal nodes go up to 2n-1
    for (int i = 1; i <= n; i++) { par[i] = i; root[i] = i; day_[i] = 0; }
    for (int d = 1; d <= m; d++) {
        int a, b; cin >> a >> b;
        int ra = find(a), rb = find(b);
        if (ra == rb) continue;                 // already connected; this day irrelevant
        int rta = root[ra], rtb = root[rb];     // current tree-roots of the two components
        int nn = ++tot;                         // new internal node for this union
        day_[nn] = d;
        par[nn] = nn;
        children[nn].pb(rta); children[nn].pb(rtb);
        par[ra] = nn; par[rb] = nn;
        root[nn] = nn;
    }

    // build parent/up tables via DFS over each reconstruction tree
    LOG = 1; while ((1 << LOG) <= tot) LOG++;
    // for (int i = 1; i <= tot; i++) up[i].assign(LOG, 0);   // left up[0] unsized -> up[0][..] OOB in doubling
    for (int i = 0; i <= tot; i++) up[i].assign(LOG, 0);      // node 0 = self-ancestor sentinel

    vector<int> par0(tot + 1, 0);
    vector<char> vis(tot + 1, 0);
    for (int u = 1; u <= tot; u++)
        for (int c : children[u]) par0[c] = u;

    // iterative DFS to set depth and up[][0]
    for (int r = 1; r <= tot; r++) {
        if (par0[r] != 0 || vis[r]) continue;   // r is a forest root
        vector<int> st = {r};
        dep[r] = 0; up[r][0] = 0; vis[r] = 1;
        for (int qi = 0; qi < (int)st.size(); qi++) {
            int u = st[qi];
            for (int c : children[u]) {
                dep[c] = dep[u] + 1; up[c][0] = u; vis[c] = 1;
                st.pb(c);
            }
        }
    }
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= tot; i++)
            up[i][j] = up[ up[i][j-1] ][j-1];

    auto lca = [&](int a, int b) -> int {
        if (find(a) != find(b)) return -1;      // different reconstruction trees -> never
        if (dep[a] < dep[b]) swap(a, b);
        int diff = dep[a] - dep[b];
        for (int j = 0; j < LOG; j++) if (diff >> j & 1) a = up[a][j];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--)
            if (up[a][j] != up[b][j]) { a = up[a][j]; b = up[b][j]; }
        return up[a][0];
    };

    string out;
    while (q--) {
        int a, b; cin >> a >> b;
        int l = lca(a, b);
        out += to_string(l < 0 ? -1 : day_[l]);
        out += '\n';
    }
    cout << out;
}