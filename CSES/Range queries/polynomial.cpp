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
vector<ll> sm, ls, lc;                  // lazy: add s*i + c over node's index range

ll sumIdx(int l, int r){ return (ll)(l + r) * (r - l + 1) / 2; }

void app(int nd, int l, int r, ll s, ll c){
    sm[nd] += s * sumIdx(l, r) + c * (r - l + 1);
    ls[nd] += s; lc[nd] += c;
}
void push(int nd, int l, int r){
    if (ls[nd] || lc[nd]){
        int m = (l + r) >> 1;
        app(nd<<1, l, m, ls[nd], lc[nd]);
        app(nd<<1|1, m+1, r, ls[nd], lc[nd]);
        ls[nd] = lc[nd] = 0;
    }
}
void build(int nd, int l, int r, vector<ll>& a){
    if (l == r){ sm[nd] = a[l]; return; }
    int m = (l + r) >> 1;
    build(nd<<1, l, m, a);
    build(nd<<1|1, m+1, r, a);
    sm[nd] = sm[nd<<1] + sm[nd<<1|1];
}
void upd(int nd, int l, int r, int ql, int qr, ll s, ll c){
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr){ app(nd, l, r, s, c); return; }
    push(nd, l, r);
    int m = (l + r) >> 1;
    upd(nd<<1, l, m, ql, qr, s, c);
    upd(nd<<1|1, m+1, r, ql, qr, s, c);
    sm[nd] = sm[nd<<1] + sm[nd<<1|1];
}
ll query(int nd, int l, int r, int ql, int qr){
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return sm[nd];
    push(nd, l, r);
    int m = (l + r) >> 1;
    return query(nd<<1, l, m, ql, qr) + query(nd<<1|1, m+1, r, ql, qr);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    sm.assign(4*n, 0);
    ls.assign(4*n, 0);
    lc.assign(4*n, 0);
    build(1, 1, n, a);

    while (q--){
        int op, aa, bb; cin >> op >> aa >> bb;
        if (op == 1){
            upd(1, 1, n, aa, bb, 1, 1 - aa);    // f(i) = i + (1-a)
        } else {
            cout << query(1, 1, n, aa, bb) << '\n';
        }
    }
    return 0;
}