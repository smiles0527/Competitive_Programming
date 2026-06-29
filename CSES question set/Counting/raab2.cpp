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

const int MX = 5000;
vector<int> dat;          // Eulerian A(n,k), flat: row n holds k=0..n-1
vector<ll> off, fact, finv;

inline ll geA(int n, int k){
    if(n==0) return k==0;
    if(k<0 || k>=n) return 0;
    return dat[off[n]+k];
}
ll pw(ll a, ll b){ ll r=1; a%=MOD; while(b){ if(b&1) r=r*a%MOD; a=a*a%MOD; b>>=1; } return r; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact.assign(MX+1,1); finv.assign(MX+1,1);
    for(int i=1;i<=MX;i++) fact[i]=fact[i-1]*i%MOD;
    finv[MX]=pw(fact[MX],MOD-2);
    for(int i=MX;i>0;i--) finv[i-1]=finv[i]*i%MOD;
    auto C=[&](int n,int r)->ll{ if(r<0||r>n||n<0) return 0; return fact[n]*finv[r]%MOD*finv[n-r]%MOD; };

    off.assign(MX+2,0); off[1]=1;                 // row0 length 1
    for(int n=1;n<=MX;n++) off[n+1]=off[n]+n;
    dat.assign(off[MX+1],0);
    dat[0]=1;                                     // A(0,0)
    for(int n=1;n<=MX;n++)                         // A(n,k)=(k+1)A(n-1,k)+(n-k)A(n-1,k-1)
        for(int k=0;k<n;k++)
            dat[off[n]+k]=(int)(((ll)(k+1)*geA(n-1,k)+(ll)(n-k)*geA(n-1,k-1))%MOD);

    int t; cin >> t;
    while(t--){
        int n,a,b; cin >> n >> a >> b;
        int fp=n-a-b, m=a+b;
        if(fp<0){ cout << 0 << '\n'; continue; }
        ll d=0;                                    // d(m,b)=sum (-1)^(m-j) C(m,j) A(j,b)
        for(int j=0;j<=m;j++){
            ll term=C(m,j)*geA(j,b)%MOD;
            if((m-j)&1) d=(d-term+MOD)%MOD; else d=(d+term)%MOD;
        }
        ll N=C(n,fp)*d%MOD;                        // N = C(n,t) d(m,b)
        cout << fact[n]*N%MOD << '\n';             // games = n! * N
    }
    return 0;
}