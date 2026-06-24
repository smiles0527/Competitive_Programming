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
vector<ll> bit;

void upd(int i, ll v){
    for (; i <= n; i += i & -i) bit[i] += v;
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
    bit.assign(n + 1, 0);
    for (int i = 1; i <= n; i++){
        cin >> cur[i];
        upd(i, cur[i]);
    }

    while (q--){
        int t; cin >> t;
        if (t == 1){
            int k; ll u; cin >> k >> u;
            upd(k, u - cur[k]);         // apply delta
            cur[k] = u;
        } else {
            int a, b; cin >> a >> b;
            cout << pre(b) - pre(a-1) << '\n';
        }
    }
    return 0;
}