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
vector<ll> sm, lz;                      // lazy assign; lz=-1 means none

void app(int nd, int l, int r, ll v){ sm[nd] = v * (r - l + 1); lz[nd] = v; }
void push(int nd, int l, int r){
    if (lz[nd] != -1){
        int m = (l + r) >> 1;
        app(nd<<1, l, m, lz[nd]);
        app(nd<<1|1, m+1, r, lz[nd]);
        lz[nd] = -1;
    }
}
void assign(int nd, int l, int r, int ql, int qr, ll v){
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr){ app(nd, l, r, v); return; }
    push(nd, l, r);
    int m = (l + r) >> 1;
    assign(nd<<1, l, m, ql, qr, v);
    assign(nd<<1|1, m+1, r, ql, qr, v);
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

    vector<ll> x(n + 1), psum(n + 1, 0);
    for (int i = 1; i <= n; i++){ cin >> x[i]; psum[i] = psum[i-1] + x[i]; }

    vector<vector<ii>> byA(n + 1);      // byA[a] = list of (b, query-id)
    for (int i = 0; i < q; i++){
        int a, b; cin >> a >> b;
        byA[a].pb({b, i});
    }

    sm.assign(4*n, 0);
    lz.assign(4*n, -1);

    vector<array<int,3>> stk;           // runs (val, l, r) over current frontier
    vector<ll> ans(q);

    for (int a = n; a >= 1; a--){
        int R = a;                                  // merged right end
        while (!stk.empty() && stk.back()[0] <= x[a]){ R = max(R, stk.back()[2]); stk.pop_back(); }
        assign(1, 1, n, a, R, x[a]);                // prefmax over [a,R] becomes x[a]
        stk.pb({ (int)x[a], a, R });
        for (auto& Qr : byA[a]){
            int b = Qr.f, id = Qr.s;
            ll S = query(1, 1, n, a, b);
            ans[id] = S - (psum[b] - psum[a-1]);
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}