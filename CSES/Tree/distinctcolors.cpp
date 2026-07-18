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
int col[200005], par[200005], ord[200005];
set<int>* S[200005];
int ans[200005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> col[i];
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

    for (int i = n - 1; i >= 0; i--) {   // children before parent
        int u = ord[i];
        if (!S[u]) S[u] = new set<int>();
        S[u]->insert(col[u]);
        ans[u] = (int)S[u]->size();
        int p = par[u];
        if (p) {
            if (!S[p]) S[p] = new set<int>();
            if (S[p]->size() < S[u]->size()) swap(S[p], S[u]);  // small into large
            for (int c : *S[u]) S[p]->insert(c);
            S[u]->clear();
        }
    }

    for (int v = 1; v <= n; v++) {
        cout << ans[v];
        cout << (v == n ? '\n' : ' ');
    }
    return 0;
}