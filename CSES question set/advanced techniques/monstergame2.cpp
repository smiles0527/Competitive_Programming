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

const int V = 1000000;                           // query domain x in [1, V]
const ll INF = 4e18;

struct Line { ll k, b; ll eval(ll x) { return k * x + b; } };

Line tr[4 * V + 5];                             // Li Chao node lines, init to +inf
bool has[4 * V + 5];

void insert(int nd, int lo, int hi, Line ln) {  // min Li Chao
    int mid = (lo + hi) >> 1;
    if (!has[nd]) { tr[nd] = ln; has[nd] = true; return; }
    bool lf = ln.eval(lo) < tr[nd].eval(lo);
    bool md = ln.eval(mid) < tr[nd].eval(mid);
    if (md) swap(tr[nd], ln);                    // ln now the worse line at mid
    if (lo == hi) return;
    if (lf != md) insert(nd << 1, lo, mid, ln);          // crossing on left half
    else          insert(nd << 1 | 1, mid + 1, hi, ln);  // crossing on right half
}
ll query(int nd, int lo, int hi, int x) {
    if (!has[nd]) return INF;
    ll r = tr[nd].eval(x);
    if (lo == hi) return r;
    int mid = (lo + hi) >> 1;
    if (x <= mid) return min(r, query(nd << 1, lo, mid, x));
    else          return min(r, query(nd << 1 | 1, mid + 1, hi, x));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;
    vi s(n + 1), fa(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> fa[i];

    insert(1, 1, V, {x, 0});                     // implicit kill-0: pay s_i * x
    ll dp = 0;
    for (int i = 1; i <= n; i++) {
        dp = query(1, 1, V, s[i]);               // dp[i] = min_{j<i} dp[j] + s_i f_j
        insert(1, 1, V, {fa[i], dp});            // monster i as a future "previous kill"
    }

    cout << dp << "\n";
}