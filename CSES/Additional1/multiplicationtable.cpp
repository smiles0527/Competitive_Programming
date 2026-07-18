#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;

    ll need = (n*n+1)/2;
    ll l = 1, r = n*n, ans = r;

    auto cnt = [&](ll x){
        ll res = 0;
        for(ll i = 1; i <= n; i++) res += min(n, x / i);
        return res;
    };

    while(l <= r){
        ll m = (l+r)/2;
        if(cnt(m)>=need) ans=m, r = m-1;
        else l=m+1;
    }
    cout << ans << '\n';
}