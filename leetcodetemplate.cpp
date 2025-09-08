#include <bits/stdc++.h>
using namespace std;

// ==== TYPES & SHORTCUTS ====
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) int((x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l,r)(rng); }

template<class T> bool chmin(T& a,const T& b){ if(b<a){ a=b; return true; } return false; }
template<class T> bool chmax(T& a,const T& b){ if(a<b){ a=b; return true; } return false; }

// ==== FAST IO ====
struct FastIO {
    FastIO(){ ios::sync_with_stdio(false); cin.tie(nullptr); }
} fastio;

// ==== DSU ====
struct DSU {
    int n; vector<int> p, r;
    DSU(int n):n(n),p(n),r(n){ iota(all(p),0); }
    int f(int x){ return p[x]==x?x:p[x]=f(p[x]); }
    bool unite(int a,int b){
        a=f(a); b=f(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a; if(r[a]==r[b]) r[a]++;
        return true;
    }
};

// ==== FENWICK ====
struct BIT {
    int n; vector<ll> t;
    BIT(int n):n(n),t(n+1){}
    void add(int i,ll v){ for(;i<=n;i+=i&-i) t[i]+=v; }
    ll sum(int i){ ll s=0; for(;i>0;i-=i&-i) s+=t[i]; return s; }
    ll range(int l,int r){ return sum(r)-sum(l-1); }
};

// ==== SEG TREE ====
struct Seg {
    int n; vector<ll> t;
    Seg(int n):n(n),t(2*n){}
    void build(const vector<ll>& a){ for(int i=0;i<n;i++) t[n+i]=a[i]; for(int i=n-1;i>0;i--) t[i]=t[i<<1]+t[i<<1|1]; }
    void setv(int p,ll v){ for(t[p+=n]=v;p>1;p>>=1) t[p>>1]=t[p]+t[p^1]; }
    ll query(int l,int r){ ll res=0; for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){ if(l&1) res+=t[l++]; if(r&1) res+=t[--r]; } return res; }
};

// ==== GRAPH BASICS ====
vector<ll> dijkstra(int n,int s,const vector<vector<pair<int,int>>>& g){
    const ll INF=4e18; vector<ll> d(n,INF); d[s]=0;
    minpq<pair<ll,int>> pq; pq.push({0,s});
    while(!pq.empty()){
        auto [du,u]=pq.top(); pq.pop();
        if(du!=d[u]) continue;
        for(auto [v,w]:g[u]){
            ll nd=du+w; if(nd<d[v]){ d[v]=nd; pq.push({nd,v}); }
        }
    }
    return d;
}

vector<int> bfs01(int n,int s,const vector<vector<pair<int,int>>>& g){
    deque<int> dq; vector<int> d(n,1e9); d[s]=0; dq.push_front(s);
    while(!dq.empty()){
        int u=dq.front(); dq.pop_front();
        for(auto [v,w]:g[u]){
            int nd=d[u]+w;
            if(nd<d[v]){ d[v]=nd; (w?dq.push_back(v):dq.push_front(v)); }
        }
    }
    return d;
}

int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};

// ==== STRINGS ====
vector<int> kmp_pi(const string& s){
    int n=sz(s); vector<int> p(n);
    for(int i=1;i<n;i++){ int j=p[i-1]; while(j&&s[i]!=s[j]) j=p[j-1]; if(s[i]==s[j]) j++; p[i]=j; }
    return p;
}

vector<int> zf(const string& s){
    int n=sz(s); vector<int> z(n); int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i<=r) z[i]=min(r-i+1,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]]) z[i]++;
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return z;
}

struct RH {
    const ll mod=1000000007, base=911382323;
    vector<ll> p,h;
    RH(const string& s){ int n=sz(s); p.assign(n+1,1); h.assign(n+1,0);
        for(int i=0;i<n;i++){ p[i+1]=p[i]*base%mod; h[i+1]=(h[i]*base+s[i])%mod; }
    }
    ll get(int l,int r){ ll v=(h[r]-h[l]*p[r-l])%mod; if(v<0) v+=mod; return v; }
};

// ==== MATH ====
ll modpow(ll a,ll e,ll m){ ll r=1; while(e){ if(e&1) r=r*a%m; a=a*a%m; e>>=1; } return r; }
ll modinv(ll a,ll m){ return modpow(a,m-2,m); }

// ==== BINARY SEARCH ====
template<class F> ll bsl(ll lo,ll hi,F ok){ while(lo<hi){ ll mid=(lo+hi)/2; if(ok(mid)) hi=mid; else lo=mid+1; } return lo; }
template<class F> ll bsg(ll lo,ll hi,F ok){ while(lo<hi){ ll mid=(lo+hi+1)/2; if(ok(mid)) lo=mid; else hi=mid-1; } return lo; }

// ==== MAIN ====
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T=1;
    // cin >> T;
    while(T--){
        // write solve() here
        cout << "hello contest\n";
    }
}
