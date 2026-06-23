#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
const int LOG = 18;
int n, m;
vector<int> g[200005];
int up[LOG][200005], dep[200005], ord[200005];
ll cnt[200005];

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int j = 0; j < LOG; j++) if (d >> j & 1) a = up[j][a];
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; j--)
        if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
    return up[0][a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int head = 0, tail = 0;
    ord[tail++] = 1; up[0][1] = 0; dep[1] = 0;
    static bool vis[200005];
    vis[1] = true;
    while (head < tail) {
        int u = ord[head++];
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = true; up[0][v] = u; dep[v] = dep[u] + 1;
            ord[tail++] = v;
        }
    }

    for (int j = 1; j < LOG; j++)
        for (int v = 1; v <= n; v++)
            up[j][v] = up[j-1][ up[j-1][v] ];

    while (m--) {
        int a, b; cin >> a >> b;
        int l = lca(a, b);
        cnt[a]++; cnt[b]++; cnt[l]--;
        if (up[0][l]) cnt[up[0][l]]--;   // -1 at parent(LCA); root has no parent
    }

    for (int i = n - 1; i >= 0; i--) {   // reverse BFS = children before parent
        int u = ord[i];
        if (up[0][u]) cnt[up[0][u]] += cnt[u];
    }

    for (int v = 1; v <= n; v++) {
        cout << cnt[v];
        cout << (v == n ? '\n' : ' ');
    }
    return 0;
}