#include <bits/stdc++.h>
using namespace std;

struct dsu{
    vector<int> p, r;
    dsu(int n=0){ init(n); }
    void init(int n){
        p.resize(n+1);
        r.assign(n+1,0);
        iota(p.begin(), p.end(), 0);
    }
    int f(int x){ return p[x]==x?x:p[x]=f(p[x]); }
    bool u(int a,int b){
        a=f(a), b=f(b);
        if(a==b) return 0;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return 1;
    }
};

struct e{
    int a,b,w;
};

static inline long long key2(int a,int b){
    if(a>b) swap(a,b);
    return ( (long long)a<<32 ) | (unsigned int)b;
}

long long mst(int n, vector<e> &v){
    sort(v.begin(), v.end(), [](const e&x,const e&y){ return x.w<y.w; });
    dsu d(n);
    long long s=0;
    int c=0;
    for(auto &x: v){
        if(d.u(x.a,x.b)){
            s+=x.w;
            if(++c==n-1) break;
        }
    }
    if(c!=n-1) return (1LL<<62);
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if(!(cin>>n)) return 0;

    unordered_map<long long, pair<int,int>> mp;
    mp.reserve(1<<20);

    vector<e> all, in;
    all.reserve(200000);
    in.reserve(200000);

    for(int i=1;i<=n;i++){
        int k; cin>>k;
        vector<int> v(k);
        for(int j=0;j<k;j++) cin>>v[j];
        vector<int> c(k);
        for(int j=0;j<k;j++) cin>>c[j];

        for(int j=0;j<k;j++){
            int a=v[j], b=v[(j+1)%k], w=c[j];
            long long kk=key2(a,b);
            auto it=mp.find(kk);
            if(it==mp.end()) mp.emplace(kk, make_pair(i,w));
            else{
                int p=it->second.first, w2=it->second.second;
                int ww=min(w,w2);
                all.push_back({p,i,ww});
                in.push_back({p,i,ww});
                mp.erase(it);
            }
        }
    }

    for(auto &kv: mp){
        int p=kv.second.first, w=kv.second.second;
        all.push_back({0,p,w});
    }

    long long a=mst(n+1, all);
    long long b=mst(n, in);
    cout<<min(a,b)<<"\n";
    return 0;
}
