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

struct Node { ll sum, best; };          // best = max prefix sum (>=0)
Node mrg(const Node&a, const Node&b){
    return { a.sum + b.sum, max(a.best, a.sum + b.best) };
}
Node leaf(ll v){ return { v, max(0LL, v) }; }
const Node ID = {0, 0};

int n, q, sz;
vector<Node> t;

void upd(int p, ll v){
    for (t[p += sz] = leaf(v), p >>= 1; p >= 1; p >>= 1)
        t[p] = mrg(t[p<<1], t[p<<1|1]);
}
ll qry(int l, int r){                   // [l, r)
    Node rl = ID, rr = ID;
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1){
        if (l & 1) rl = mrg(rl, t[l++]);
        if (r & 1) rr = mrg(t[--r], rr);
    }
    return mrg(rl, rr).best;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    sz = 1;
    while (sz < n) sz <<= 1;
    t.assign(2*sz, ID);

    for (int i = 0; i < n; i++){ ll x; cin >> x; t[sz + i] = leaf(x); }
    for (int i = sz - 1; i >= 1; i--) t[i] = mrg(t[i<<1], t[i<<1|1]);

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