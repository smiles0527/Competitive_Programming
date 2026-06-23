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
int n;
vector<int> g[200005];
int par[200005], sz[200005], ord[200005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int hd = 0, tl = 0;
    ord[tl++] = 1; par[1] = 0;
    static bool vis[200005];
    vis[1] = true;
    while (hd < tl) {
        int u = ord[hd++];
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = true; par[v] = u;
            ord[tl++] = v;
        }
    }
    for (int i = 1; i <= n; i++) sz[i] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (par[u]) sz[par[u]] += sz[u];
    }

    int v = 1, half = n / 2;
    while (true) {
        int nxt = -1;
        for (int u : g[v]) if (u != par[v] && sz[u] > half) { nxt = u; break; }
        // upward part n - sz[v] is checked implicitly: if it exceeded half we'd
        // have descended from there; from root there is no upward part
        if (nxt == -1) break;
        par[nxt] = v;          // reorient so the previous node becomes "up"
        sz[v] = n - sz[nxt];   // v's size as seen from nxt's rooting
        v = nxt;
    }

    cout << v << '\n';
    return 0;
}