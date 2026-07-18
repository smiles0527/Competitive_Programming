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
    ll n; int m;
    cin >> n >> m;

    int MX = 2*n + 5;
    vector<ll> fact(MX), finv(MX);
    fact[0]=1; for(int i=1;i<MX;i++) fact[i]=fact[i-1]*i%MOD;
    finv[MX-1]=pw(fact[MX-1],MOD-2); for(int i=MX-1;i>0;i--) finv[i-1]=finv[i]*i%MOD;
    auto C=[&](ll a,ll b)->ll{ if(b<0||b>a)return 0; return fact[a]*finv[b]%MOD*finv[a-b]%MOD; };

    vector<ii> p(m);
    for(auto &t : p){ ll y,x; cin>>y>>x; t={y,x}; }
    p.pb({n,n});                                   // destination as final node
    sort(p.begin(), p.end());

    int M = p.size();
    vi dp(M);
    auto paths=[&](ll y1,ll x1,ll y2,ll x2)->ll{   // monotone right/down paths
        if(y2<y1 || x2<x1) return 0;
        return C((y2-y1)+(x2-x1), y2-y1);
    };
    for(int i=0;i<M;i++){
        ll cur = paths(1,1,p[i].f,p[i].s);         // from start, ignoring traps
        for(int j=0;j<i;j++)
            if(p[j].f<=p[i].f && p[j].s<=p[i].s)
                cur=(cur - dp[j]*paths(p[j].f,p[j].s,p[i].f,p[i].s))%MOD;
        dp[i]=(cur%MOD+MOD)%MOD;
    }
    cout << dp[M-1] << '\n';
    return 0;
}