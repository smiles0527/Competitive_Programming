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

int n, q;
vector<ll> sm;
vector<int> lc, rc;
int cnt = 0;

int newNode(){
    sm.pb(0); lc.pb(0); rc.pb(0);
    // return ++cnt;                    // bug: id one ahead of slot index
    return cnt++;                       // id == slot index; sentinel -> 0
}
int build(int l, int r, vector<ll>& a){
    int nd = newNode();
    if (l == r){ sm[nd] = a[l]; return nd; }
    int m = (l + r) >> 1;
    lc[nd] = build(l, m, a);
    rc[nd] = build(m+1, r, a);
    sm[nd] = sm[lc[nd]] + sm[rc[nd]];
    return nd;
}
int upd(int prev, int l, int r, int p, ll v){
    int nd = newNode();
    if (l == r){ sm[nd] = v; return nd; }
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

    int cap = 2*n + (q + 5) * (__lg(max(n,1)) + 2) + 10;
    sm.reserve(cap); lc.reserve(cap); rc.reserve(cap);
    newNode();                          // node 0 sentinel

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> root;                   // root[k] = version root for array k
    root.pb(build(1, n, a));            // array index 0 == "array 1"

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int k, p; ll x; cin >> k >> p >> x;
            root[k-1] = upd(root[k-1], 1, n, p, x);
        } else if (op == 2){
            int k, aa, bb; cin >> k >> aa >> bb;
            cout << query(root[k-1], 1, n, aa, bb) << '\n';
        } else {
            int k; cin >> k;
            root.pb(root[k-1]);         // copy-on-write: share root
        }
    }
    return 0;
}