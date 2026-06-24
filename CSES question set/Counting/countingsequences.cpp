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

ll pw(ll a, ll b){ ll r=1; a%=MOD; while(b){ if(b&1)r=r*a%MOD; a=a*a%MOD; b>>=1; } return r; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k;
    cin >> n >> k;

    vi fact(k+1), finv(k+1);
    fact[0]=1; for(int i=1;i<=k;i++) fact[i]=fact[i-1]*i%MOD;
    finv[k]=pw(fact[k],MOD-2); for(int i=k;i>0;i--) finv[i-1]=finv[i]*i%MOD;
    auto C=[&](ll a,ll b){ return fact[a]*finv[b]%MOD*finv[a-b]%MOD; };

    ll ans=0;
    for(int i=0;i<=k;i++){
        ll term = C(k,i)*pw(k-i, n)%MOD;        // (k-i)^n sequences using only k-i fixed symbols
        if(i&1) ans=(ans-term+MOD)%MOD; else ans=(ans+term)%MOD;
    }
    cout << ans << '\n';
    return 0;
}