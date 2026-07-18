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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k;
    cin >> n >> k;

    vi prev(k+1, 0), cur(k+1, 0);
    prev[0] = 1;                                   // i = 1: only 0 inversions
    for(int i = 2; i <= n; i++){
        for(int j = 0; j <= k; j++){
            ll v = prev[j];                        // sum_{t=0}^{i-1} prev[j-t]
            if(j >= 1)  v += cur[j-1];
            if(j >= i)  v -= prev[j-i];
            v %= MOD; if(v < 0) v += MOD;
            cur[j] = v;
        }
        swap(prev, cur);
    }
    cout << prev[k] << '\n';
    return 0;
}