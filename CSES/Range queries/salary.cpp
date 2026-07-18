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

int n, q, V;
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

    vector<ll> cur(n + 1);
    vector<ll> vals;
    for (int i = 1; i <= n; i++){ cin >> cur[i]; vals.pb(cur[i]); }

    vector<char> op(q);
    vector<ll> A(q), B(q);              // op '!' : (k,x) ; op '?' : (a,b)
    for (int i = 0; i < q; i++){
        cin >> op[i] >> A[i] >> B[i];
        if (op[i] == '!') vals.pb(B[i]); // new salary value
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    V = vals.size();
    auto idx = [&](ll v){ return int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; };

    bit.assign(V + 1, 0);
    for (int i = 1; i <= n; i++) upd(idx(cur[i]), 1);

    for (int i = 0; i < q; i++){
        if (op[i] == '!'){
            int k = (int)A[i]; ll x = B[i];
            upd(idx(cur[k]), -1);
            cur[k] = x;
            upd(idx(x), 1);
        } else {
            int lo = idx(A[i]);                                   // first index >= a
            int hi = int(upper_bound(vals.begin(), vals.end(), B[i]) - vals.begin()); // first index > b (0-based) = #vals <= b
            cout << pre(hi) - pre(lo - 1) << '\n';
        }
    }
    return 0;
}