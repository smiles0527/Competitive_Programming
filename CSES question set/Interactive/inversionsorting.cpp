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
const int MOD = 1e9+7;

int n;

ll rev(int l, int r){
    cout << l << " " << r << "\n" << flush;
    ll x;
    if(!(cin >> x)) exit(0);
    if(x == 0) exit(0); // 0 inversions == identity == win
    return x;
}

int main(){
    cin >> n;
    if(n == 1){
        cout << 1 << " " << 1 << "\n" << flush;
        ll x; cin >> x;
        return 0;
    }

    rev(1, 2);              // probe + ...
    ll cur = rev(1, 2);     // ... restore; cur = I_0

    for(int k = 1; k <= n-1; k++){
        int L = k+1;
        ll C = (ll)L*(L-1)/2;
        ll before = cur;
        ll t = rev(1, L);            // reveals r via internal inversions
        int r = (int)((C - (t - before)) / 2);
        cur = rev(1, L);             // restore sorted prefix + v at tail
        if(r == 0) continue;
        else if(r == 1) cur = rev(k, k+1);
        else { cur = rev(k-r+1, L); cur = rev(k-r+2, L); }
    }
    return 0;
}