#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD=1e9+7;
const int INF=1e9;

int n; vector<ll> a; ll mxa;

ll G(ll H){ ll g=LLONG_MAX; int idx=0; while(idx<n){ ll av=a[idx],q=(av+H-1)/H; g=min(g,av/q); idx=upper_bound(a.begin(),a.end(),q*H)-a.begin(); } return g; }
ll nextH(ll g){ ll t=0, gg=g+1; int idx=0; while(idx<n){ ll av=a[idx],q=av/gg; int hi=(int)(upper_bound(a.begin(),a.end(),(q+1)*gg-1)-a.begin())-1; t=max(t,(a[hi]+q-1)/q); idx=hi+1; } return t; }

vector<ll> bpH, bpG, W;                 // G breakpoints over [hmin,mxa]; bpG increasing; W=H-G
vector<vector<ll>> sp; vector<int> lg;
void buildSparse(){ int sz=W.size(); if(!sz) return; lg.assign(sz+1,0); for(int i=2;i<=sz;i++) lg[i]=lg[i/2]+1; int K=lg[sz]+1; sp.assign(K,vector<ll>(sz)); sp[0]=W; for(int j=1;j<K;j++) for(int i=0;i+(1<<j)<=sz;i++) sp[j][i]=min(sp[j-1][i],sp[j-1][i+(1<<(j-1))]); }
ll qmin(int l,int r){ if(l>r) return LLONG_MAX; int j=lg[r-l+1]; return min(sp[j][l],sp[j][r-(1<<j)+1]); }

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll m; cin>>n>>m; a.resize(n);
    for(auto&v:a) cin>>v;
    sort(a.begin(),a.end()); mxa=a.back();

    // H* sweep (cut current max ceil); L* sweep (cut largest next-floor, min from multiset)
    priority_queue<tuple<ll,ll,ll>> Hp; for(ll v:a) Hp.push({v,v,1});
    vector<ll> p(n,1), cf(n); multiset<ll> mn; priority_queue<ii> Gq;
    for(int i=0;i<n;i++){ cf[i]=a[i]; mn.insert(cf[i]); Gq.push({a[i]/2,i}); }
    vector<ll> Hs(m+1), Ls(m+1);
    for(ll c=1;c<=m;c++){
        auto [cv,ca,cp]=Hp.top(); Hp.pop(); ll np=cp+1; Hp.push({(ca+np-1)/np,ca,np}); Hs[c]=get<0>(Hp.top());
        auto [nf,i]=Gq.top(); Gq.pop(); mn.erase(mn.find(cf[i])); p[i]++; cf[i]=a[i]/p[i]; mn.insert(cf[i]); Gq.push({a[i]/(p[i]+1),i}); Ls[c]=*mn.begin();
    }

    // enumerate G breakpoints only in the needed region [min H*(P), maxa] (sparse there)
    ll hmin=*min_element(Hs.begin()+1,Hs.end()), mnA=a[0], H=hmin;
    while(H<=mxa){ ll g=G(H); bpH.pb(H); bpG.pb(g); if(g>=mnA) break; ll nh=nextH(g); if(nh<=H) nh=H+1; H=nh; }
    for(int k=0;k<(int)bpH.size();k++) W.pb(bpH[k]-bpG[k]);
    buildSparse();

    string out; out.reserve(m*7);
    for(ll c=1;c<=m;c++){
        ll h0=Hs[c], L=Ls[c];
        int k0=(int)(upper_bound(bpH.begin(),bpH.end(),h0)-bpH.begin())-1;   // step containing h0
        ll gh=bpG[k0], ans;
        if(gh>=L) ans=h0-L;                                                  // bound tight
        else{
            int kT=(int)(lower_bound(bpG.begin(),bpG.end(),L)-bpG.begin());  // first step with G>=L
            ll part1=(kT<(int)bpH.size()? max(h0,bpH[kT])-L : LLONG_MAX);
            ll cand0=h0-gh;                                                  // clamped left endpoint
            ll inter=qmin(k0+1, kT<(int)bpH.size()?kT-1:(int)bpH.size()-1);  // interior breakpoint min of H-G(H)
            ans=min({cand0, part1, inter});
        }
        out+=to_string(ans); out+=' ';
    }
    cout<<out<<"\n";
}