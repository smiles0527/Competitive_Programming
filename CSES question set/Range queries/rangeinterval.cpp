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

int n, q, V;                            // V = value-domain size
vector<ll> bit;

void upd(int i, ll v){
    for (; i <= V; i += i & -i) bit[i] += v;
}
ll pre(int i){
    ll r = 0;
    for (; i > 0; i -= i & -i) r += bit[i];
    return r;
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
    auto lo = [&](ll v){ return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; };
    auto hi = [&](ll v){ return int(upper_bound(vals.begin(), vals.end(), v) - vals.begin()); };

    vector<int> A(q), C(q), D(q);
    vector<ll> ans(q, 0);
    // events: (pos, qid, sign), pos in [0,n]
    vector<array<int,3>> ev;
    ev.reserve(2*q);
    for (int i = 0; i < q; i++){
        int a, b, c, d; cin >> a >> b >> c >> d;
        A[i] = a; C[i] = c; D[i] = d;
        ev.pb({b, i, 1});
        ev.pb({a - 1, i, -1});
    }
    sort(ev.begin(), ev.end(), [](const array<int,3>&p, const array<int,3>&r){ return p[0] < r[0]; });

    bit.assign(V + 1, 0);

    int j = 1;                          // sweep pointer over positions
    for (auto& e : ev){
        int pos = e[0], qid = e[1], sgn = e[2];
        while (j <= pos){ upd(lo(x[j]), 1); j++; }   // insert value at index j
        ll cnt = pre(hi(D[qid])) - pre(lo(C[qid]) - 1);
        ans[qid] += sgn * cnt;
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}