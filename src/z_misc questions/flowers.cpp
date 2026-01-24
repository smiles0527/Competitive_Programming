#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<long long> t;
    BIT(int n=0): n(n), t(n+1,0) {}
    void init(int n_) { n=n_; t.assign(n+1,0); }
    void update(int i, long long v){ for(; i<=n; i+=i&-i) t[i]=max(t[i],v); }
    long long query(int i){ long long r=0; for(; i>0; i-=i&-i) r=max(r,t[i]); return r; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if(!(cin>>N)) return 0;
    vector<long long> h(N), a(N);
    for(int i=0;i<N;i++) cin>>h[i];
    for(int i=0;i<N;i++) cin>>a[i];
    vector<long long> comp=h;
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    BIT bit((int)comp.size());
    long long ans=0;
    for(int i=0;i<N;i++){
        int pos=lower_bound(comp.begin(),comp.end(),h[i])-comp.begin()+1;
        long long best=bit.query(pos-1);
        long long val=best+a[i];
        bit.update(pos,val);
        if(val>ans) ans=val;
    }
    cout<<ans<<"\n";
    return 0;
}
