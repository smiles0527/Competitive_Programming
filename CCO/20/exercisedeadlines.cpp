#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    void remove(int x){ p[x]=find(x-1); }
};

struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int n): n(n), f(n+1,0){}
    void add(int i){ for(; i<=n; i+=i&-i) f[i]++; }
    ll sum(int i){ ll s=0; for(; i>0; i-=i&-i) s+=f[i]; return s; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if(!(cin>>N)) return 0;
    vector<int> d(N+1);
    for(int i=1;i<=N;i++){
        cin>>d[i];
        if(d[i]>N) d[i]=N;
    }

    DSU dsu(N);
    vector<int> pos(N+1);
    for(int i=N;i>=1;i--){
        int t=dsu.find(d[i]);
        if(t==0){
            cout<<-1;
            return 0;
        }
        pos[i]=t;
        dsu.remove(t);
    }

    vector<int> A(N+1);
    for(int i=1;i<=N;i++) A[pos[i]]=i;

    Fenwick fw(N);
    ll inv=0;
    for(int i=1;i<=N;i++){
        inv += fw.sum(N) - fw.sum(A[i]);
        fw.add(A[i]);
    }
    cout<<inv;
    return 0;
}
