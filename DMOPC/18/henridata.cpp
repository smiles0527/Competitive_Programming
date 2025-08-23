#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> f;
    Fenwick(int n=0): n(n), f(n+1,0) {}
    void add(int i, long long v){ for(; i<=n; i+=i&-i) f[i]+=v; }
    long long sumPrefix(int i){ long long s=0; for(; i>0; i-=i&-i) s+=f[i]; return s; }
    long long rangeSum(int l,int r){ return sumPrefix(r)-sumPrefix(l-1); }
};

struct Qry {
    int l,r,idx;
    long long k;
    bool operator<(const Qry& o) const { return k>o.k; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q; 
    if(!(cin>>N>>Q)) return 0;
    vector<long long> A(N+1), pref(N+1);
    for(int i=1;i<=N;i++){ cin>>A[i]; pref[i]=pref[i-1]+A[i]; }
    vector<pair<long long,int>> elems;
    elems.reserve(N);
    for(int i=1;i<=N;i++) elems.push_back({A[i],i});
    sort(elems.begin(), elems.end(), [](auto& x, auto& y){ return x.first>y.first; });
    vector<Qry> qs(Q);
    for(int i=0;i<Q;i++){ cin>>qs[i].l>>qs[i].r>>qs[i].k; qs[i].idx=i; }
    sort(qs.begin(), qs.end());
    Fenwick fw(N);
    vector<long long> ans(Q);
    int p=0;
    for(auto& qu: qs){
        while(p<N && elems[p].first>=qu.k){ fw.add(elems[p].second, elems[p].first); p++; }
        long long total = pref[qu.r]-pref[qu.l-1];
        long long ge = fw.rangeSum(qu.l, qu.r);
        ans[qu.idx] = -total + 2*ge;
    }
    for(int i=0;i<Q;i++) cout<<ans[i]<<"\n";
    return 0;
}
