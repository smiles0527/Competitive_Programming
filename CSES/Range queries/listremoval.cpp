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

int n;
vector<ll> bit;

void upd(int i, ll v){
    for (; i <= n; i += i & -i) bit[i] += v;
}
int findk(ll k){                        // smallest idx with prefix sum == k
    int pos = 0, LOG = 31 - __builtin_clz(n);
    for (int pw = 1 << LOG; pw; pw >>= 1){
        if (pos + pw <= n && bit[pos + pw] < k){
            pos += pw;
            k -= bit[pos];
        }
    }
    return pos + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    vector<ll> x(n + 1);
    bit.assign(n + 1, 0);
    for (int i = 1; i <= n; i++){
        cin >> x[i];
        upd(i, 1);                      // present
    }

    for (int i = 0; i < n; i++){
        ll p; cin >> p;
        int idx = findk(p);
        cout << x[idx] << ' ';
        upd(idx, -1);                   // remove
    }
    cout << '\n';
    return 0;
}