#include <bits/stdc++.h>
using namespace std; using ll=long long;
const ll MOD=998244353; const long double NEG=-1e18;

ll mul(ll a,ll b){ return (ll)((__int128)a*b%MOD); }

struct S{
  bool ok; long double lg; ll m;
};

S mk(ll x){
  ll a=llabs(x);
  return {true, logl((long double)a), a%MOD};
}

S mulS(const S& s,ll x){
  ll a=llabs(x);
  return {true, s.lg+logl((long double)a), mul(s.m,a%MOD)};
}

bool big(const S&a,const S&b){ return a.ok && (!b.ok || a.lg>b.lg); }
bool sml(const S&a,const S&b){ return a.ok && (!b.ok || a.lg<b.lg); }

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; cin>>T;
  while(T--){
    int n; cin>>n;
    vector<ll>a(n); for(ll&i:a) cin>>i;

    S P{0,0,1}, Nb{0,0,1}, Ns{0,0,1};
    S bestP{0,0,1}, bestN{0,0,1};
    bool z=0;

    for(ll x:a){
      if(x==0){ z=1; P=Nb=Ns={0,0,1}; continue; }

      S nP{0,0,1}, nNb{0,0,1}, nNs{0,0,1};

      if(x>0){
        S c1=P.ok?mulS(P,x):S{0,0,1}, c2=mk(x);
        nP=big(c1,c2)?c1:c2;
        if(Nb.ok) nNb=mulS(Nb,x);
        if(Ns.ok) nNs=mulS(Ns,x);
      }else{
        if(Nb.ok) nP=mulS(Nb,x);
        S c1=P.ok?mulS(P,x):S{0,0,1}, c2=mk(x);
        nNb=big(c1,c2)?c1:c2;
        nNs=sml(c1,c2)?c1:c2;
      }

      P=nP; Nb=nNb; Ns=nNs;
      if(big(P,bestP)) bestP=P;
      if(sml(Ns,bestN)) bestN=Ns;
    }

    if(bestP.ok) cout<<bestP.m<<"\n";
    else if(z) cout<<0<<"\n";
    else cout<<(MOD-bestN.m)%MOD<<"\n";
  }
}
