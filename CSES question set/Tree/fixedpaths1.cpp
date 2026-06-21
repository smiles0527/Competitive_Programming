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
int n, k;
vector<int> g[200005];
int sz[200005];
bool removed[200005];
ll cnt[200005];
ll ans = 0;

int subtree_size(int s) {
    int sp = 0;
    static int st[200005], par[200005], ordr[200005];
    int m = 0;
    st[sp++] = s; par[s] = 0;
    while (sp) {
        int u = st[--sp];
        ordr[m++] = u;
        for (int v : g[u]) if (v != par[u] && !removed[v]) {
            par[v] = u; st[sp++] = v;
        }
    }
    for (int i = m - 1; i >= 0; i--) {
        int u = ordr[i];
        sz[u] = 1;
        for (int v : g[u]) if (v != par[u] && !removed[v]) sz[u] += sz[v];
    }
    return sz[s];
}

int find_centroid(int s, int tot) {
    int u = s, p = 0;
    while (true) {
        int nxt = -1;
        for (int v : g[u]) if (v != p && !removed[v] && sz[v] > tot/2) { nxt = v; break; }
        if (nxt == -1) break;
        sz[u] = tot - sz[nxt];   // reorient size
        p = u; u = nxt;
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // iterative centroid decomposition over a work stack of components
    static int comp[200005];
    int csp = 0;
    comp[csp++] = 1;
    static int par2[200005], st2[200005], dorder[200005];

    while (csp) {
        int start = comp[--csp];
        int tot = subtree_size(start);
        int c = find_centroid(start, tot);
        removed[c] = true;

        // gather depths per child subtree, combine
        cnt[0] = 1;
        vector<int> used = {0};

        for (int ch : g[c]) if (!removed[ch]) {
            // BFS this child subtree, collecting depths
            int sp = 0, m = 0;
            st2[sp++] = ch; par2[ch] = c;
            static int depth[200005];
            depth[ch] = 1;
            dorder[m++] = ch;
            while (sp) {
                int u = st2[--sp];
                for (int v : g[u]) if (v != par2[u] && !removed[v]) {
                    par2[v] = u; depth[v] = depth[u] + 1;
                    st2[sp++] = v; dorder[m++] = v;
                }
            }
            // first count against already-merged subtrees
            for (int i = 0; i < m; i++) {
                int d = depth[dorder[i]];
                if (d <= k) ans += cnt[k - d];
            }
            // then merge
            for (int i = 0; i < m; i++) {
                int d = depth[dorder[i]];
                if (d <= k) { cnt[d]++; used.push_back(d); }
            }
        }

        for (int d : used) cnt[d] = 0;   // clear only touched

        for (int ch : g[c]) if (!removed[ch]) comp[csp++] = ch;
    }

    cout << ans << '\n';
    return 0;
}