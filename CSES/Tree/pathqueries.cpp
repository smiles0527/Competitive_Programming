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
ll val[200005];
int tin[200005], tout_[200005];
ll bit[200005];

void upd(int i, ll d) { for (; i <= n; i += i & -i) bit[i] += d; }
ll qry(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
void radd(int l, int r, ll d) { upd(l, d); if (r + 1 <= n) upd(r + 1, -d); }

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

    static int st[200005], it[200005], par[200005];
    int timer = 0, sp = 0;
    st[sp] = 1; par[1] = 0; it[1] = 0;
    tin[1] = ++timer;
    while (sp >= 0) {
        int u = st[sp];
        if (it[u] < (int)g[u].size()) {
            int v = g[u][it[u]++];
            if (v == par[u]) continue;
            par[v] = u; it[v] = 0;
            tin[v] = ++timer;
            st[++sp] = v;
        } else {
            tout_[u] = timer;
            sp--;
        }
    }

    for (int v = 1; v <= n; v++) radd(tin[v], tout_[v], val[v]);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s; ll x; cin >> s >> x;
            radd(tin[s], tout_[s], x - val[s]);
            val[s] = x;
        } else {
            int s; cin >> s;
            cout << qry(tin[s]) << '\n';
        }
    }
    return 0;
}