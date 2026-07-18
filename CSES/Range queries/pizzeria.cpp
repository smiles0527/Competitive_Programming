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
vector<ll> ta, tc;                      // a_b = p_b - b ; c_b = p_b + b

void upd(vector<ll>& t, int p, ll v){
    for (t[p += sz] = v, p >>= 1; p >= 1; p >>= 1)
        t[p] = min(t[p<<1], t[p<<1|1]);
}
ll qry(vector<ll>& t, int l, int r){    // [l, r)
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
    ta.assign(2*sz, LLONG_MAX);
    tc.assign(2*sz, LLONG_MAX);

    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> p[i];
        ta[sz + i - 1] = p[i] - i;       // 0-indexed leaf i-1 holds building i
        tc[sz + i - 1] = p[i] + i;
    }
    for (int i = sz - 1; i >= 1; i--){
        ta[i] = min(ta[i<<1], ta[i<<1|1]);
        tc[i] = min(tc[i<<1], tc[i<<1|1]);
    }

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int k; ll x; cin >> k >> x;
            upd(ta, k - 1, x - k);
            upd(tc, k - 1, x + k);
        } else {
            int k; cin >> k;
            ll left  = qry(ta, 0, k) + k;        // b in [1,k]
            ll right = qry(tc, k - 1, n) - k;    // b in [k,n]
            cout << min(left, right) << '\n';
        }
    }
    return 0;
}