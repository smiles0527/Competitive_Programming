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

struct M2 { ll a,b,c,d; };
M2 mul(const M2&x, const M2&y){
    return {
        (x.a*y.a + x.b*y.c)%MOD,
        (x.a*y.b + x.b*y.d)%MOD,
        (x.c*y.a + x.d*y.c)%MOD,
        (x.c*y.b + x.d*y.d)%MOD
    };
}
M2 mpow(M2 b, ll e){
    M2 r{1,0,0,1};
    for(; e; e>>=1){ if(e&1) r=mul(r,b); b=mul(b,b); }
    return r;
}

// s_n = s_{n-1} + e*s_{n-2},  s1=1+e, s2=1+2e
ll fne(ll n, ll e){
    ll ee = e % MOD;
    ll s1 = (1 + ee) % MOD;
    ll s2 = (1 + 2*ee) % MOD;
    if(n == 1) return s1;
    if(n == 2) return s2;
    M2 T{1, ee, 1, 0};                 // (s_n, s_{n-1}) = T*(s_{n-1}, s_{n-2})
    M2 P = mpow(T, n-2);
    return (P.a*s2 + P.b*s1) % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        ll n, k; cin >> n >> k;
        ll ans = 1;
        for(ll p = 2; p*p <= k; p++){
            if(k % p == 0){
                ll e = 0;
                while(k % p == 0){ k /= p; e++; }
                ans = ans * fne(n, e) % MOD;
            }
        }
        if(k > 1) ans = ans * fne(n, 1) % MOD;   // leftover prime, e=1
        cout << ans << '\n';
    }
}