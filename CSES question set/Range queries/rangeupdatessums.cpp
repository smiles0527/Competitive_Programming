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
vector<ll> sm, add, asg;
vector<char> hasAsg;

void applyAsg(int nd, int l, int r, ll v){
    sm[nd] = v * (r - l + 1);
    asg[nd] = v; hasAsg[nd] = 1; add[nd] = 0;
}
void applyAdd(int nd, int l, int r, ll v){
    sm[nd] += v * (r - l + 1);
    add[nd] += v;
}
void push(int nd, int l, int r){
    int m = (l + r) >> 1;
    if (hasAsg[nd]){
        applyAsg(nd<<1, l, m, asg[nd]);
        applyAsg(nd<<1|1, m+1, r, asg[nd]);
        hasAsg[nd] = 0;
    }
    if (add[nd]){
        applyAdd(nd<<1, l, m, add[nd]);
        applyAdd(nd<<1|1, m+1, r, add[nd]);
        add[nd] = 0;
    }
}
void build(int nd, int l, int r, vector<ll>& a){
    if (l == r){ sm[nd] = a[l]; return; }
    int m = (l + r) >> 1;
    build(nd<<1, l, m, a);
    build(nd<<1|1, m+1, r, a);
    sm[nd] = sm[nd<<1] + sm[nd<<1|1];
}
void rangeAdd(int nd, int l, int r, int ql, int qr, ll v){
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr){ applyAdd(nd, l, r, v); return; }
    push(nd, l, r);
    int m = (l + r) >> 1;
    rangeAdd(nd<<1, l, m, ql, qr, v);
    rangeAdd(nd<<1|1, m+1, r, ql, qr, v);
    sm[nd] = sm[nd<<1] + sm[nd<<1|1];
}
void rangeAsg(int nd, int l, int r, int ql, int qr, ll v){
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr){ applyAsg(nd, l, r, v); return; }
    push(nd, l, r);
    int m = (l + r) >> 1;
    rangeAsg(nd<<1, l, m, ql, qr, v);
    rangeAsg(nd<<1|1, m+1, r, ql, qr, v);
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
    add.assign(4*n, 0);
    asg.assign(4*n, 0);
    hasAsg.assign(4*n, 0);
    build(1, 1, n, a);

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int aa, bb; ll x; cin >> aa >> bb >> x;
            rangeAdd(1, 1, n, aa, bb, x);
        } else if (op == 2){
            int aa, bb; ll x; cin >> aa >> bb >> x;
            rangeAsg(1, 1, n, aa, bb, x);
        } else {
            int aa, bb; cin >> aa >> bb;
            cout << query(1, 1, n, aa, bb) << '\n';
        }
    }
    return 0;
}