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

int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<int> ea(m), eb(m), fo(n+2,0), ro(n+2,0), indeg(n+1,0);
    for(int i=0;i<m;i++){ cin>>ea[i]>>eb[i]; fo[ea[i]+1]++; ro[eb[i]+1]++; indeg[eb[i]]++; }
    for(int u=1;u<=n+1;u++){ fo[u]+=fo[u-1]; ro[u]+=ro[u-1]; }
    vector<int> fg(m), rg(m), pf(fo.begin(),fo.end()), pr(ro.begin(),ro.end());
    for(int i=0;i<m;i++){ fg[pf[ea[i]]++]=eb[i]; rg[pr[eb[i]]++]=ea[i]; }   // fg: succ of a ; rg: pred of b

    vector<int> ord; ord.reserve(n);                                        // Kahn topo order
    for(int u=1;u<=n;u++) if(!indeg[u]) ord.pb(u);
    for(size_t h=0;h<ord.size();h++){ int u=ord[h]; for(int e=fo[u];e<fo[u+1];e++) if(--indeg[fg[e]]==0) ord.pb(fg[e]); }

    // width<=2 DP: ord[i] is always a chain tail; g(i) = feasible other tails (0 = empty chain).
    // g(i+1) = (ord[i]->ord[i+1] ? g(i):{}) U (exists w in g(i): w->ord[i+1] or w=0 ? {ord[i]}:{})
    vector<char> inG(n+1,0);
    vector<int> members; members.reserve(n);
    vector<int> wit(n+1,0);                                                 // option2 witness pred (0 => starts a chain)
    bool zeroIn = true;                                                     // g(1) = {0}

    for(int i=0;i+1<n;i++){
        int cur=ord[i], nxt=ord[i+1];
        bool a=false,b=false; int w=0;
        for(int e=ro[nxt];e<ro[nxt+1];e++){ int p=rg[e]; if(p==cur) a=true; if(inG[p]&&!b){ b=true; w=p; } }
        if(zeroIn&&!b){ b=true; w=0; }                                      // empty other chain can begin anywhere
        wit[nxt]=w;
        if(a){ if(b&&!inG[cur]){ inG[cur]=1; members.pb(cur); } }           // carry g(i); option2 may also add cur
        else { for(int x:members) inG[x]=0; members.clear(); zeroIn=false; if(b){ inG[cur]=1; members.pb(cur); } }  // reset
    }

    if(members.empty()&&!zeroIn){ cout<<"NO\n"; return 0; }

    int other = members.empty()?0:members.back();                          // any element of g(n)
    vector<int> pred(n+1,0);
    for(int i=n-2;i>=0;i--){                                                // backtrack: other==cur => option2 else option1
        int cur=ord[i], nxt=ord[i+1];
        if(other==cur){ pred[nxt]=wit[nxt]; other=wit[nxt]; }
        else pred[nxt]=cur;
    }

    vector<int> nxtv(n+1,0);
    for(int v=1;v<=n;v++) if(pred[v]) nxtv[pred[v]]=v;
    vector<vector<int>> paths;
    for(int v=1;v<=n;v++) if(pred[v]==0){ vector<int> p; int c=v; while(c){ p.pb(c); c=nxtv[c]; } paths.pb(move(p)); }

    cout<<"YES\n";
    auto outp=[&](vector<int>&p){ cout<<p.size(); for(int x:p) cout<<' '<<x; cout<<"\n"; };
    outp(paths[0]);
    if(paths.size()==2) outp(paths[1]); else cout<<0<<"\n";                 // second chain may be empty
}
