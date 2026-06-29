#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

struct MCMF {
    struct E{ int to, cap, cost, nxt; };
    vector<E> e; vector<int> head, dist, pre; vector<char> inq; int V;
    void init(int n){ V=n; head.assign(n,-1); e.clear(); }
    void add(int u,int v,int cap,int cost){
        e.pb({v,cap,cost,head[u]}); head[u]=e.size()-1;
        e.pb({u,0,-cost,head[v]}); head[v]=e.size()-1;
    }
    bool spfa(int s,int t){
        dist.assign(V,INF); pre.assign(V,-1); inq.assign(V,0);
        deque<int> q; dist[s]=0; q.pb(s); inq[s]=1;
        while(!q.empty()){
            int u=q.front(); q.pop_front(); inq[u]=0;
            for(int i=head[u];i!=-1;i=e[i].nxt) if(e[i].cap>0 && dist[u]+e[i].cost<dist[e[i].to]){
                dist[e[i].to]=dist[u]+e[i].cost; pre[e[i].to]=i;
                if(!inq[e[i].to]){ inq[e[i].to]=1; q.pb(e[i].to); }
            }
        }
        return dist[t]<INF;
    }
    pair<int,ll> run(int s,int t){           // (maxflow, mincost)
        int fl=0; ll cost=0;
        while(spfa(s,t)){
            int f=INF;
            for(int v=t; v!=s; v=e[pre[v]^1].to) f=min(f,e[pre[v]].cap);
            for(int v=t; v!=s; v=e[pre[v]^1].to){ e[pre[v]].cap-=f; e[pre[v]^1].cap+=f; }
            fl+=f; cost+=(ll)f*dist[t];
        }
        return {fl,cost};
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;
    vector<vector<int>> c(n, vector<int>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> c[i][j];

    ll sa=accumulate(a.begin(),a.end(),0LL), sb=accumulate(b.begin(),b.end(),0LL);
    if(sa!=sb){ cout<<-1<<"\n"; return 0; }

    // S=0, rows 1..n, cols n+1..2n, T=2n+1 ; mid edge cost -c to maximize
    int S=0, T=2*n+1;
    MCMF mc; mc.init(2*n+2);
    int eidRC[55][55];
    for(int i=0;i<n;i++) mc.add(S, 1+i, a[i], 0);
    for(int j=0;j<n;j++) mc.add(1+n+j, T, b[j], 0);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ eidRC[i][j]=mc.e.size(); mc.add(1+i, 1+n+j, 1, -c[i][j]); }

    auto [fl, cost] = mc.run(S, T);
    if(fl != sa){ cout<<-1<<"\n"; return 0; }            // can't satisfy margins

    cout << -cost << "\n";
    string out; out.reserve((size_t)n*(n+1));
    for(int i=0;i<n;i++){
        string row(n,'.');
        for(int j=0;j<n;j++) if(mc.e[eidRC[i][j]].cap==0) row[j]='X';   // saturated mid edge = chosen
        out += row; out += '\n';
    }
    cout << out;
}