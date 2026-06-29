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

int n,d;
vector<vector<int>> adj;
vector<int> eo,ev;                      // CSR of adj for the hot decomposition (vector<vector> was cache-hostile)
vector<int> sz,par,dst;
vector<char> rem;
vector<int> best;                       // best[c]: nearest selected to centroid c within its block
// vector<vector<pair<int,int>>> anc;   // (centroid, dist(v,centroid)) over centroid ancestors
vector<int> fv,fc,fd;                   // flat triples (owner v, centroid c, dist) collected during decomp
vector<int> off,ac,ad;                  // CSR of anc: ranges off[v]..off[v+1) into ac/ad

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>d;
    adj.assign(n+1,{});
    for(int i=0;i<n-1;i++){int a,b;cin>>a>>b;adj[a].pb(b);adj[b].pb(a);}

    eo.assign(n+2,0);                                                         // build CSR adj once
    for(int u=1;u<=n;u++) eo[u+1]=eo[u]+(int)adj[u].size();
    ev.resize(eo[n+1]);
    for(int u=1;u<=n;u++){int b=eo[u]; for(int v:adj[u]) ev[b++]=v;}

    vector<int> dep(n+1,-1),ord; ord.reserve(n);
    dep[1]=0; ord.pb(1);
    for(size_t h=0;h<ord.size();h++){int u=ord[h];for(int v:adj[u])if(dep[v]<0){dep[v]=dep[u]+1;ord.pb(v);}}
    sort(ord.begin(),ord.end(),[&](int a,int b){return dep[a]>dep[b];});      // deepest first

    sz.assign(n+1,0); par.assign(n+1,0); dst.assign(n+1,0);
    rem.assign(n+1,0); best.assign(n+1,INF);
    // anc.assign(n+1,{});
    fv.reserve((size_t)n*20); fc.reserve((size_t)n*20); fd.reserve((size_t)n*20);
    vector<int> buf; buf.reserve(n);
    vector<int> seeds={1};
    while(!seeds.empty()){
        int s0=seeds.back(); seeds.pop_back();
        if(rem[s0]) continue;
        buf.clear(); buf.pb(s0); par[s0]=0;                                   // gather block, root at s0
        // for(size_t h=0;h<buf.size();h++){int u=buf[h];for(int v:adj[u])if(!rem[v]&&v!=par[u]){par[v]=u;buf.pb(v);}}
        for(size_t h=0;h<buf.size();h++){int u=buf[h];for(int e=eo[u];e<eo[u+1];e++){int v=ev[e];if(!rem[v]&&v!=par[u]){par[v]=u;buf.pb(v);}}}
        int tot=buf.size();
        // for(int i=tot-1;i>=0;i--){int u=buf[i];sz[u]=1;for(int v:adj[u])if(!rem[v]&&v!=par[u])sz[u]+=sz[v];}
        for(int u:buf) sz[u]=1;
        for(int i=tot-1;i>=1;i--){int u=buf[i]; sz[par[u]]+=sz[u];}           // par precedes child => accumulate, no adj scan
        int c=s0,pc=0;                                                        // descend to centroid
        // for(;;){int nx=-1;for(int v:adj[c])if(!rem[v]&&v!=pc&&sz[v]*2>tot){nx=v;break;}if(nx<0)break;pc=c;c=nx;}
        for(;;){int nx=-1;for(int e=eo[c];e<eo[c+1];e++){int v=ev[e];if(!rem[v]&&v!=pc&&sz[v]*2>tot){nx=v;break;}}if(nx<0)break;pc=c;c=nx;}
        buf.clear(); buf.pb(c); par[c]=0; dst[c]=0;                           // dists from centroid -> anc lists
        // for(size_t h=0;h<buf.size();h++){int u=buf[h];for(int v:adj[u])if(!rem[v]&&v!=par[u]){par[v]=u;dst[v]=dst[u]+1;buf.pb(v);}}
        for(size_t h=0;h<buf.size();h++){int u=buf[h];for(int e=eo[u];e<eo[u+1];e++){int v=ev[e];if(!rem[v]&&v!=par[u]){par[v]=u;dst[v]=dst[u]+1;buf.pb(v);}}}
        for(int u:buf){ fv.pb(u); fc.pb(c); fd.pb(dst[u]); }
        rem[c]=1;
        // for(int v:adj[c])if(!rem[v])seeds.pb(v);
        for(int e=eo[c];e<eo[c+1];e++){int v=ev[e];if(!rem[v])seeds.pb(v);}
    }

    int TOT=fv.size();                                                        // pack triples into CSR by owner
    off.assign(n+2,0);
    for(int i=0;i<TOT;i++) off[fv[i]+1]++;
    for(int u=1;u<=n+1;u++) off[u]+=off[u-1];
    ac.resize(TOT); ad.resize(TOT);
    vector<int> pos(off.begin(),off.end());
    for(int i=0;i<TOT;i++){int p=pos[fv[i]]++; ac[p]=fc[i]; ad[p]=fd[i];}

    vector<int> res;
    for(int v:ord){
        int nd=INF;                                                          // nearest selected = min over centroid ancestors
        // for(auto&pr:anc[v]){int cd=pr.s+best[pr.f]; if(cd<nd)nd=cd;}
        for(int i=off[v];i<off[v+1];i++){int cd=ad[i]+best[ac[i]]; if(cd<nd)nd=cd;}
        if(nd>=d){
            res.pb(v);
            // for(auto&pr:anc[v]) if(pr.s<best[pr.f]) best[pr.f]=pr.s;
            for(int i=off[v];i<off[v+1];i++) if(ad[i]<best[ac[i]]) best[ac[i]]=ad[i];
        }
    }
    cout<<res.size()<<"\n";
    for(int i=0;i<(int)res.size();i++) cout<<res[i]<<" \n"[i+1==(int)res.size()];
}