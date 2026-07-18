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
int n, q;
vector<int> g[200005];
int up[LOG][200005], dep[200005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // root at 1, iterative BFS -> par = up[0], dep
    static int order_[200005];
    int head = 0, tail = 0;
    order_[tail++] = 1; up[0][1] = 0; dep[1] = 0;
    static bool vis[200005];
    vis[1] = true;
    while (head < tail) {
        int u = order_[head++];
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = true;
            up[0][v] = u;
            dep[v] = dep[u] + 1;
            order_[tail++] = v;
        }
    }

    for (int j = 1; j < LOG; j++)
        for (int v = 1; v <= n; v++)
            up[j][v] = up[j-1][ up[j-1][v] ];

    while (q--) {
        int a, b; cin >> a >> b;
        int da = dep[a], db = dep[b];
        int x = a, y = b;
        if (dep[x] < dep[y]) swap(x, y);
        int d = dep[x] - dep[y];
        for (int j = 0; j < LOG; j++)
            if (d >> j & 1) x = up[j][x];
        int l;
        if (x == y) l = x;
        else {
            for (int j = LOG - 1; j >= 0; j--)
                if (up[j][x] != up[j][y]) { x = up[j][x]; y = up[j][y]; }
            l = up[0][x];
        }
        cout << (da + db - 2 * dep[l]) << '\n';
    }
    return 0;
}