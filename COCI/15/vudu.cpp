#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> f;
    Fenwick(int n=0): n(n), f(n+1,0) {}
    void add(int i,long long v){ for(;i<=n;i+=i&-i) f[i]+=v; }
    long long sum(int i){ long long s=0; for(;i>0;i-=i&-i) s+=f[i]; return s; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if(!(cin>>N)) return 0;
    vector<long long> a(N);
    for(int i=0;i<N;i++) cin>>a[i];
    long long P; 
    cin>>P;

    vector<long long> pref(N+1);
    for(int i=1;i<=N;i++) pref[i]=pref[i-1]+(a[i-1]-P);

    vector<long long> vals=pref;
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());

    Fenwick fw((int)vals.size());
    long long ans=0;
    for(int i=0;i<=N;i++){
        int idx=int(lower_bound(vals.begin(),vals.end(),pref[i])-vals.begin())+1;
        ans+=fw.sum(idx);
        fw.add(idx,1);
    }
    cout<<ans<<"\n";
    return 0;
}

