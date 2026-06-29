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

int n, m, sz;
vector<ll> t;

int descend(ll r){                      // leftmost leaf with value >= r, then decrement
    if (t[1] < r) return 0;
    int p = 1;
    while (p < sz){
        p <<= 1;
        if (t[p] < r) p |= 1;           // left can't fit -> go right
    }
    t[p] -= r;
    int idx = p - sz + 1;
    for (p >>= 1; p >= 1; p >>= 1) t[p] = max(t[p<<1], t[p<<1|1]);
    return idx;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    sz = 1;
    while (sz < n) sz <<= 1;
    t.assign(2*sz, 0);

    for (int i = 0; i < n; i++) cin >> t[sz + i];
    for (int i = sz - 1; i >= 1; i--) t[i] = max(t[i<<1], t[i<<1|1]);

    while (m--){
        ll r; cin >> r;
        cout << descend(r) << ' ';
    }
    cout << '\n';
    return 0;
}