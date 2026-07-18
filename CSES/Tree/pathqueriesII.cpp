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
int val[200005], par[200005], dep[200005], sz[200005], heavy[200005];
int head_[200005], pos_[200005], ord[200005];
int N;
ll seg[1<<19];

inline void supd(int p, ll v) {
    for (seg[p += N] = v, p >>= 1; p; p >>= 1)
        seg[p] = max(seg[p<<1], seg[p<<1|1]);
}
inline ll sqry(int l, int r) {            // inclusive [l,r], 0-indexed
    ll res = LLONG_MIN;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, seg[l++]);
        if (r & 1) res = max(res, seg[--r]);
    }
    return res;
}

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

    int hd = 0, tl = 0;
    ord[tl++] = 1; par[1] = 0; dep[1] = 0;
    static bool vis[200005];
    vis[1] = true;
    while (hd < tl) {
        int u = ord[hd++];
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = true; par[v] = u; dep[v] = dep[u] + 1;
            ord[tl++] = v;
        }
    }
    for (int i = 1; i <= n; i++) sz[i] = 1, heavy[i] = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (par[u]) {
            sz[par[u]] += sz[u];
            if (heavy[par[u]] == 0 || sz[u] > sz[heavy[par[u]]])
                heavy[par[u]] = u;
        }
    }

    int timer = 0;
    static int stk[200005];
    int sp = 0;
    head_[1] = 1;
    stk[sp++] = 1;
    while (sp) {
        int u = stk[--sp];
        pos_[u] = timer++;
        ord[timer - 1] = u;
        for (int v : g[u]) if (v != par[u] && v != heavy[u]) {
            head_[v] = v;
            stk[sp++] = v;
        }
        if (heavy[u]) {
            head_[heavy[u]] = head_[u];
            stk[sp++] = heavy[u];
        }
    }

    N = 1; while (N < n) N <<= 1;
    for (int i = 0; i < 2*N; i++) seg[i] = LLONG_MIN;
    for (int i = 0; i < n; i++) seg[N + pos_[ord[i]]] = val[ord[i]];
    for (int i = N - 1; i; i--) seg[i] = max(seg[i<<1], seg[i<<1|1]);

    string out;
    out.reserve(1 << 22);
    char buf[24];

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x; cin >> s >> x;
            val[s] = x;
            supd(pos_[s], x);
        } else {
            int a, b; cin >> a >> b;
            ll res = LLONG_MIN;
            while (head_[a] != head_[b]) {
                if (dep[head_[a]] < dep[head_[b]]) swap(a, b);
                res = max(res, sqry(pos_[head_[a]], pos_[a]));
                a = par[head_[a]];
            }
            if (dep[a] > dep[b]) swap(a, b);
            res = max(res, sqry(pos_[a], pos_[b]));
            int len = 0; ll t = res;
            if (t == 0) buf[len++] = '0';
            while (t) { buf[len++] = char('0' + t % 10); t /= 10; }
            while (len) out += buf[--len];
            out += '\n';
        }
    }
    cout << out;
    return 0;
}