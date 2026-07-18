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
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    ll x, a, b, c;
    cin >> x >> a >> b >> c;
    vector<int> v(n), suf(n);
    ll g = x;                // raw generator value, x_1 = x
    for(int i = 0; i < n; i++){
        v[i] = (int)g;
        g = (a*g + b) % c;
    }
    for(int i = n-1; i >= 0; i--)            // suf[i] = OR(i .. block end)
        suf[i] = (i%k==k-1 || i==n-1) ? v[i] : (v[i] | suf[i+1]);
    ll ans = 0;
    int cur = 0;                             // pre[r] = OR(block start .. r), rolled forward
    for(int r = 0; r < k-1; r++) cur = (r%k==0) ? v[r] : (cur | v[r]);
    for(int l = 0; l + k - 1 < n; l++){
        int r = l + k - 1;
        cur = (r%k==0) ? v[r] : (cur | v[r]);
        ans ^= suf[l] | cur;
    }
    cout << ans << "\n";
    return 0;
}