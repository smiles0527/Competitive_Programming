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
int par[200005], sz[200005], order_[200005];
ll f[200005];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // BFS to fix a parent/child order rooted at 1
    int head = 0, tail = 0;
    order_[tail++] = 1; par[1] = 0;
    static bool vis[200005];
    vis[1] = true;
    while (head < tail) {
        int u = order_[head++];
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = true; par[v] = u;
            order_[tail++] = v;
        }
    }

    // sz[] and down-sum f[1] via reverse order
    for (int i = 1; i <= n; i++) sz[i] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int u = order_[i];
        if (par[u]) {
            sz[par[u]] += sz[u];
            f[par[u]] += f[u] + sz[u];   // down[par] += down[u] + sz[u]
        }
    }
    // here f[1] = sum of distances from root 1

    // reroot in forward order: f[c] = f[u] + n - 2*sz[c]
    for (int i = 1; i < n; i++) {
        int u = order_[i];
        f[u] = f[par[u]] + n - 2LL * sz[u];
    }

    for (int v = 1; v <= n; v++) {
        printf("%lld", f[v]);
        putchar(v == n ? '\n' : ' ');
    }
    return 0;
}