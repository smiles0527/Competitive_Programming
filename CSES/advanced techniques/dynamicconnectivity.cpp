#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int par[100005], sz[100005], comp;
vector<pair<int*, int>> hist;                   // (address, old value) for rollback

int find(int x) { while (par[x] != x) x = par[x]; return x; }   // no path compression

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    hist.pb({&par[b], par[b]}); par[b] = a;
    hist.pb({&sz[a], sz[a]});   sz[a] += sz[b];
    hist.pb({&comp, comp});     comp--;
}
int snapshot() { return hist.size(); }
void rollback(int s) {
    while ((int)hist.size() > s) {
        auto [addr, val] = hist.back(); hist.pop_back();
        *addr = val;
    }
}

int K;                                           // number of segment-tree leaves (= k+1)
vector<vii> seg;                                 // seg[node] = edges active on that node
void addEdge(int node, int lo, int hi, int l, int r, ii e) {
    if (r < lo || hi < l) return;
    if (l <= lo && hi <= r) { seg[node].pb(e); return; }
    int mid = (lo + hi) >> 1;
    addEdge(node << 1, lo, mid, l, r, e);
    addEdge(node << 1 | 1, mid + 1, hi, l, r, e);
}

string out;
void dfs(int node, int lo, int hi) {
    int s = snapshot();
    for (auto &e : seg[node]) unite(e.f, e.s);
    if (lo == hi) { out += to_string(comp); out += ' '; }
    else {
        int mid = (lo + hi) >> 1;
        dfs(node << 1, lo, mid);
        dfs(node << 1 | 1, mid + 1, hi);
    }
    rollback(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) { par[i] = i; sz[i] = 1; }
    comp = n;

    K = k + 1;                                   // time points 0..k
    seg.assign(4 * K, {});

    map<ii, int> birth;                          // edge -> time it became active
    auto key = [](int a, int b) { return ii{min(a, b), max(a, b)}; };

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        birth[key(a, b)] = 0;                    // initial edges alive from time 0
    }

    for (int t = 1; t <= k; t++) {
        int ty, a, b; cin >> ty >> a >> b;
        ii e = key(a, b);
        if (ty == 1) birth[e] = t;              // created at time t -> alive [t, ...]
        else {
            int bt = birth[e];                  // remove: edge was alive [bt, t-1]
            addEdge(1, 0, K - 1, bt, t - 1, e);
            birth.erase(e);
        }
    }
    for (auto &kv : birth)                        // still-alive edges live to the end
        addEdge(1, 0, K - 1, kv.s, K - 1, kv.f);

    dfs(1, 0, K - 1);
    out.back() = '\n';
    cout << out;
}