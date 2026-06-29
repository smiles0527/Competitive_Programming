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

struct Node { ll sum, pref, suf, best; };   // all clamped >= 0 except sum
Node mrg(const Node&a, const Node&b){
    return {
        a.sum + b.sum,
        max(a.pref, a.sum + b.pref),
        max(b.suf, b.sum + a.suf),
        max({a.best, b.best, a.suf + b.pref})
    };
}
Node leaf(ll v){ ll g = max(0LL, v); return { v, g, g, g }; }
const Node ID = {0, 0, 0, 0};

int n, m, sz;
vector<Node> t;

void upd(int p, ll v){
    for (t[p += sz] = leaf(v), p >>= 1; p >= 1; p >>= 1)
        t[p] = mrg(t[p<<1], t[p<<1|1]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    sz = 1;
    while (sz < n) sz <<= 1;
    t.assign(2*sz, ID);

    for (int i = 0; i < n; i++){ ll x; cin >> x; t[sz + i] = leaf(x); }
    for (int i = sz - 1; i >= 1; i--) t[i] = mrg(t[i<<1], t[i<<1|1]);

    while (m--){
        int k; ll x; cin >> k >> x;
        upd(k - 1, x);
        cout << t[1].best << '\n';
    }
    return 0;
}