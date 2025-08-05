#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n,1) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M; if(!(cin>>N>>M)) return 0;
    DSU d(2*N+1);
    auto enemy = [&](int x){ return x+N; };

    while(M--){
        char t; int p,q; cin>>t>>p>>q;
        if(t=='F'){
            d.unite(p,q);
            d.unite(enemy(p),enemy(q));
        }else{
            d.unite(p,enemy(q));
            d.unite(enemy(p),q);
        }
    }

    unordered_set<int> roots;
    for(int i=1;i<=N;++i) roots.insert(d.find(i));
    cout<<roots.size()<<'\n';
    return 0;
}
        