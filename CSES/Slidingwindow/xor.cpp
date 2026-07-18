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
    vector<int> buf(k);
    ll s = 0, ans = 0;
    ll g = x;                // raw generator value, x_1 = x
    for(int i = 0; i < k; i++){
        buf[i] = (int)g;
        s ^= g;
        if(i+1 < k) g = (a*g + b) % c;
    }
    ans ^= s;
    int pos = 0;
    for(int i = k; i < n; i++){
        g = (a*g + b) % c;
        int out = buf[pos];
        s ^= g ^ out;
        buf[pos] = (int)g;
        pos++; if(pos == k) pos = 0;
        ans ^= s;
    }
    cout << ans << "\n";
    return 0;
}