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
vector<int> adj[N];
int num[N], low[N], idx;
bool art[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int e = 0; e < m; e++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }

    for (int i = 1; i <= n; i++) num[i] = -1;

    vector<int> cstk, pstk, par;                // node, child-ptr, parent stacks
    for (int s0 = 1; s0 <= n; s0++) {
        if (num[s0] != -1) continue;
        int rootChildren = 0;
        cstk.pb(s0); pstk.pb(0); par.pb(0);
        while (!cstk.empty()) {
            int u = cstk.back();
            int &pi = pstk.back();
            int p = par.back();
            if (pi == 0) { num[u] = low[u] = idx++; }
            if (pi < (int)adj[u].size()) {
                int v = adj[u][pi++];
                if (v == p) continue;                   // skip parent (single edge guaranteed)
                if (num[v] == -1) {
                    if (u == s0) rootChildren++;        // count root's tree children
                    cstk.pb(v); pstk.pb(0); par.pb(u);
                } else {
                    low[u] = min(low[u], num[v]);       // back-edge
                }
            } else {                                    // finished u
                cstk.pop_back(); pstk.pop_back(); par.pop_back();
                if (p != 0) {                           // u has a parent
                    low[p] = min(low[p], low[u]);
                    if (p != s0 && low[u] >= num[p]) art[p] = true;  // non-root cut
                }
            }
        }
        if (rootChildren >= 2) art[s0] = true;          // root cut rule
    }

    vector<int> res;
    for (int i = 1; i <= n; i++) if (art[i]) res.pb(i);

    string out = to_string(res.size()) + "\n";
    for (int v : res) { out += to_string(v); out += '\n'; }
    cout << out;
}