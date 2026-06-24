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
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int n, q, V;                            // V = #distinct values
vector<ll> sm;                          // node stores value-sum of coins
vector<int> lc, rc;
int cnt = 0;

int newNode(){
    sm.pb(0); lc.pb(0); rc.pb(0);
    return cnt++;                       // id == slot index; sentinel -> 0
}
int upd(int prev, int l, int r, int p, ll v){   // add v at position p
    int nd = newNode();
    if (l == r){ sm[nd] = sm[prev] + v; return nd; }
    int m = (l + r) >> 1;
    if (p <= m){ lc[nd] = upd(lc[prev], l, m, p, v); rc[nd] = rc[prev]; }
    else       { rc[nd] = upd(rc[prev], m+1, r, p, v); lc[nd] = lc[prev]; }
    sm[nd] = sm[lc[nd]] + sm[rc[nd]];
    return nd;
}
ll query(int nd, int l, int r, int ql, int qr){
    if (qr < l || r < ql || !nd) return 0;
    if (ql <= l && r <= qr) return sm[nd];
    int m = (l + r) >> 1;
    return query(lc[nd], l, m, ql, qr) + query(rc[nd], m+1, r, ql, qr);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<ll> x(n + 1), vals;
    for (int i = 1; i <= n; i++){ cin >> x[i]; vals.pb(x[i]); }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    V = vals.size();
    auto pos = [&](ll v){ return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; };
    auto cntle = [&](ll v){ return int(upper_bound(vals.begin(), vals.end(), v) - vals.begin()); }; // #distinct <= v

    int cap = 2 + n * (__lg(max(V,1)) + 2);
    sm.reserve(cap); lc.reserve(cap); rc.reserve(cap);
    newNode();                          // node 0 sentinel

    vector<int> root(n + 1);
    root[0] = 0;
    for (int i = 1; i <= n; i++) root[i] = upd(root[i-1], 1, V, pos(x[i]), x[i]);

    while (q--){
        int a, b; cin >> a >> b;
        ll r = 0;
        while (true){
            int hi = cntle(r + 1);              // compressed prefix of values <= r+1
            ll S = 0;
            if (hi >= 1)
                S = query(root[b], 1, V, 1, hi) - query(root[a-1], 1, V, 1, hi);
            if (S > r) r = S; else break;
        }
        cout << r + 1 << '\n';
    }
    return 0;
}