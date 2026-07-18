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
vector<vector<int>> adj;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    adj.assign(n+1,{});
    for(int i=0;i<m;i++){int a,b;cin>>a>>b;adj[a].pb(b);}

    // iterative Tarjan SCC  (su = dfs stack, it = current-arc, reused naming)
    vector<int> disc(n+1,0), low(n+1,0), comp(n+1,0), it(n+1,0);
    vector<char> onstk(n+1,0);
    vector<int> stk, su;
    int timer=0, C=0;
    for(int s0=1;s0<=n;s0++) if(!disc[s0]){
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

    if(C==1){ cout<<0<<"\n"; return 0; }

    vector<int> rep(C+1,0), indeg(C+1,0), outdeg(C+1,0);
    vector<vector<int>> cadj(C+1);
    for(int u=1;u<=n;u++) rep[comp[u]]=u;
    for(int u=1;u<=n;u++) for(int v:adj[u]) if(comp[u]!=comp[v]){
        cadj[comp[u]].pb(comp[v]); outdeg[comp[u]]++; indeg[comp[v]]++;
    }

    vector<int> sources, sinks;
    for(int c=1;c<=C;c++){ if(!indeg[c]) sources.pb(c); if(!outdeg[c]) sinks.pb(c); }

    // greedy disjoint source->sink pairing (persistent visited => sinks terminate => visited sink == matched sink)
    vector<char> vis(C+1,0), used(C+1,0);
    vector<int> cit(C+1,0), pS, pT, st2;
    for(int sc:sources){
        if(vis[sc]) continue;
        st2.clear(); st2.pb(sc); int found=-1;
        while(!st2.empty()){
            int u=st2.back(); vis[u]=1;
            if(outdeg[u]==0 && !used[u]){ found=u; break; }
            bool adv=false;
            while(cit[u]<(int)cadj[u].size()){
                int v=cadj[u][cit[u]++];
                if(!vis[v]){ st2.pb(v); adv=true; break; }
            }
            if(!adv) st2.pop_back();
        }
        if(found!=-1){ used[found]=1; pS.pb(sc); pT.pb(found); }
    }

    int p=pS.size();
    vector<char> mS(C+1,0), mT(C+1,0);
    for(int x:pS) mS[x]=1;
    for(int x:pT) mT[x]=1;
    vector<int> q, r;                                  // leftover sources / sinks
    for(int c:sources) if(!mS[c]) q.pb(c);
    for(int c:sinks)   if(!mT[c]) r.pb(c);
    int a=q.size(), b=r.size();

    vector<ii> e;                                      // (fromComp, toComp)
    for(int i=0;i<p;i++) e.pb({pT[i], pS[(i+1)%p]});   // fuse matched paths into one SCC M
    int mn=min(a,b);
    for(int j=0;j<mn;j++) e.pb({r[j], q[j]});          // one edge serves a leftover sink AND source
    for(int j=mn;j<a;j++) e.pb({pT[0], q[j]});         // feed remaining extra sources
    for(int j=mn;j<b;j++) e.pb({r[j], pS[0]});         // drain remaining extra sinks

    cout<<e.size()<<"\n";
    for(auto&ed:e) cout<<rep[ed.f]<<" "<<rep[ed.s]<<"\n";
}