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
int n, q;
vector<int> g[200005];
int val[200005], tin[200005], tout_[200005], pos[200005];
ll bit[200005];

void upd(int i, ll d) { for (; i <= n; i += i & -i) bit[i] += d; }
ll qry(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // iterative DFS for tin/tout
    static int st[200005], it[200005];
    static int par[200005];
    int timer = 0, sp = 0;
    st[sp] = 1; par[1] = 0; it[1] = 0;
    tin[1] = ++timer; pos[timer] = 1;
    while (sp >= 0) {
        int u = st[sp];
        if (it[u] < (int)g[u].size()) {
            int v = g[u][it[u]++];
            if (v == par[u]) continue;
            par[v] = u; it[v] = 0;
            tin[v] = ++timer; pos[timer] = v;
            st[++sp] = v;
        } else {
            tout_[u] = timer;
            sp--;
        }
    }

    for (int t = 1; t <= n; t++) upd(t, val[pos[t]]);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x; cin >> s >> x;
            upd(tin[s], (ll)x - val[s]);
            val[s] = x;
        } else {
            int s; cin >> s;
            cout << qry(tout_[s]) - qry(tin[s] - 1) << '\n';
        }
    }
    return 0;
}