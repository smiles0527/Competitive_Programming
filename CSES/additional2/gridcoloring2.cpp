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

int n,m;
vector<vector<int>> adj;     // 2-SAT implication graph

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    vector<string> gr(n);
    for(auto&r:gr) cin>>r;

    int V=n*m, NN=2*V;
    adj.assign(NN,{});
    auto id=[&](int i,int j){ return i*m+j; };
    // var x per cell; node 2x = "x=1" (col1), 2x+1 = "x=0" (col0). col0=(o+1)%3, col1=(o+2)%3.
    vector<int> c0(V),c1(V);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){ int o=gr[i][j]-'A',e=id(i,j); c0[e]=(o+1)%3; c1[e]=(o+2)%3; }
    auto col=[&](int u,int b){ return b?c1[u]:c0[u]; };
    auto lit=[&](int u,int b){ return 2*u+(b?0:1); };                 // "u=b" literal node
    auto add=[&](int a,int b){ adj[a].pb(b); };                       // implication a->b
    auto forbid=[&](int u,int bu,int w,int bw){ int a=lit(u,bu),b=lit(w,bw); add(a,b^1); add(b,a^1); };  // ¬(u=bu ∧ w=bw)
    auto edge=[&](int u,int w){ for(int bu=0;bu<2;bu++)for(int bw=0;bw<2;bw++) if(col(u,bu)==col(w,bw)) forbid(u,bu,w,bw); };

    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        int u=id(i,j);
        if(j+1<m) edge(u,id(i,j+1));
        if(i+1<n) edge(u,id(i+1,j));
    }

    // iterative Tarjan SCC (su = dfs stack, it = current-arc)  [reused from New Flight Routes]
    vector<int> disc(NN,0), low(NN,0), comp(NN,0), it(NN,0);
    vector<char> onstk(NN,0);
    vector<int> stk, su;
    int timer=0, C=0;
    for(int s0=0;s0<NN;s0++) if(!disc[s0]){
        su.pb(s0);
        while(!su.empty()){
            int u=su.back();
            if(!disc[u]){ disc[u]=low[u]=++timer; stk.pb(u); onstk[u]=1; }
            bool rec=false;
            while(it[u]<(int)adj[u].size()){
                int v=adj[u][it[u]++];
                if(!disc[v]){ su.pb(v); rec=true; break; }
                if(onstk[v]) low[u]=min(low[u],disc[v]);
            }
            if(rec) continue;
            if(low[u]==disc[u]){                       // root of an SCC
                ++C; int x;
                do{ x=stk.back(); stk.pop_back(); onstk[x]=0; comp[x]=C; }while(x!=u);
            }
            su.pop_back();
            if(!su.empty()) low[su.back()]=min(low[su.back()],low[u]);
        }
    }

    for(int x=0;x<V;x++) if(comp[2*x]==comp[2*x+1]){ cout<<"IMPOSSIBLE\n"; return 0; }

    string out; out.reserve((size_t)n*(m+1));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int u=id(i,j);
            int b = comp[2*u] < comp[2*u+1] ? 1 : 0;   // smaller comp = topo-later = literal true
            out += char('A'+col(u,b));
        }
        out += '\n';
    }
    cout<<out;
}