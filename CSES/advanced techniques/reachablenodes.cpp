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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int e = 0; e < m; e++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
        indeg[b]++;
    }

    vector<int> topo; topo.reserve(n);          // Kahn: forward topo order
    deque<int> q;
    for (int i = 1; i <= n; i++) if (!indeg[i]) q.pb(i);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        topo.pb(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.pb(v);
    }

    vector<bitset<N>> rc(n + 1);                // reachable set per node
    for (int i = topo.size() - 1; i >= 0; i--) {  // reverse topo: successors first
        int u = topo[i];
        rc[u].set(u - 1);
        for (int v : adj[u]) rc[u] |= rc[v];
    }

    string out; out.reserve((size_t)n * 6);
    for (int i = 1; i <= n; i++) {
        out += to_string((ll)rc[i].count());
        out += (i < n) ? ' ' : '\n';
    }
    cout << out;
}