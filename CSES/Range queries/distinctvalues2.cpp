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
vector<int> t;                          // range-max over prev[]

void upd(int p, int v){
    for (t[p += sz] = v, p >>= 1; p >= 1; p >>= 1)
        t[p] = max(t[p<<1], t[p<<1|1]);
}
int qry(int l, int r){                  // [l, r)
    int res = 0;
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1){
        if (l & 1) res = max(res, t[l++]);
        if (r & 1) res = max(res, t[--r]);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<int> x(n + 1), pv(n + 1, 0);
    map<int, set<int>> pos;
    for (int i = 1; i <= n; i++){
        cin >> x[i];
        auto& S = pos[x[i]];
        if (!S.empty()) pv[i] = *S.rbegin();   // predecessor = current max < i
        S.insert(i);
    }

    sz = 1;
    while (sz < n) sz <<= 1;
    t.assign(2*sz, 0);
    for (int i = 1; i <= n; i++) t[sz + i - 1] = pv[i];
    for (int i = sz - 1; i >= 1; i--) t[i] = max(t[i<<1], t[i<<1|1]);

    while (q--){
        int op; cin >> op;
        if (op == 1){
            int k, u; cin >> k >> u;
            if (x[k] != u){
                // detach k from its old value's set
                auto& S = pos[x[k]];
                auto it = S.find(k);
                auto nx = next(it);
                int suc = (nx != S.end()) ? *nx : 0;
                int prd = (it != S.begin()) ? *prev(it) : 0;
                S.erase(it);
                if (suc){ pv[suc] = prd; upd(suc - 1, prd); }
                // attach k to new value's set
                x[k] = u;
                auto& T = pos[u];
                auto jt = T.lower_bound(k);             // first > k (k absent)
                int suc2 = (jt != T.end()) ? *jt : 0;
                int prd2 = (jt != T.begin()) ? *prev(jt) : 0;
                T.insert(k);
                pv[k] = prd2; upd(k - 1, prd2);
                if (suc2){ pv[suc2] = k; upd(suc2 - 1, k); }
            }
        } else {
            int a, b; cin >> a >> b;
            cout << (qry(a - 1, b) < a ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}