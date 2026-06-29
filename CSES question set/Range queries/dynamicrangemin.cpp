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

int n, q, sz;
vector<ll> t;

void upd(int p, ll v){
    for (t[p += sz] = v, p >>= 1; p >= 1; p >>= 1)
        t[p] = min(t[p<<1], t[p<<1|1]);
}
ll qry(int l, int r){                   // [l, r)
    ll res = LLONG_MAX;
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1){
        if (l & 1) res = min(res, t[l++]);
        if (r & 1) res = min(res, t[--r]);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    sz = 1;
    while (sz < n) sz <<= 1;
    t.assign(2*sz, LLONG_MAX);

    for (int i = 0; i < n; i++) cin >> t[sz + i];
    for (int i = sz - 1; i >= 1; i--) t[i] = min(t[i<<1], t[i<<1|1]);

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int k; ll u; cin >> k >> u;
            upd(k - 1, u);
        } else {
            int a, b; cin >> a >> b;
            cout << qry(a - 1, b) << '\n';
        }
    }
    return 0;
}