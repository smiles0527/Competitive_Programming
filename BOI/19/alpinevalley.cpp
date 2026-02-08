#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL<<62);

struct E { int to, id; ll w; };

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n,s,q,rt;
  cin >> n >> s >> q >> rt;

  vector<vector<E>> g(n+1);
  vector<int> a(n), b(n), low(n);
  vector<ll> w(n);

  for(int i=1;i<n;i++){
    cin >> a[i] >> b[i] >> w[i];
    g[a[i]].push_back({b[i],i,w[i]});
    g[b[i]].push_back({a[i],i,w[i]});
  }

  vector<char> shop(n+1,0);
  for(int i=0,x;i<s;i++) cin >> x, shop[x]=1;

  int LG=1;
  while((1<<LG)<=n) LG++;

  vector<int> p(n+1), dep(n+1), tin(n+1), tout(n+1);
  vector<ll> d(n+1);
  vector<vector<int>> up(LG, vector<int>(n+1));
  vector<vector<ll>> mn(LG, vector<ll>(n+1,INF));
  vector<vector<int>> ch(n+1);
  vector<int> ord; ord.reserve(n);

  int T=0;

  {
    vector<int> st={rt}, it(n+1);
    while(!st.empty()){
      int u=st.back();
      if(!it[u]) tin[u]=++T, ord.push_back(u);
      if(it[u]<(int)g[u].size()){
        auto e=g[u][it[u]++];
        if(e.to==p[u]) continue;
        p[e.to]=u;
        dep[e.to]=dep[u]+1;
        d[e.to]=d[u]+e.w;
        up[0][e.to]=u;
        ch[u].push_back(e.to);
        st.push_back(e.to);
      } else {
        tout[u]=T;
        st.pop_back();
      }
    }
  }

  auto inside = [&](int r,int u){
    return tin[r]<=tin[u] && tout[u]<=tout[r];
  };

  for(int i=1;i<n;i++){
    int u=a[i], v=b[i];
    if(p[u]==v) low[i]=u;
    else if(p[v]==u) low[i]=v;
    else low[i]=(dep[u]>dep[v]?u:v);
  }

  vector<ll> best(n+1,INF), mag(n+1,INF);

  for(int i=n-1;i>=0;i--){
    int u=ord[i];
    ll x = shop[u] ? d[u] : INF;
    for(int v:ch[u]) x=min(x,best[v]);
    best[u]=x;
    if(x<INF/2) mag[u]=x-2*d[u];
  }

  for(int i=1;i<=n;i++) mn[0][i]=mag[i];
  for(int k=1;k<LG;k++)
    for(int i=1;i<=n;i++){
      up[k][i]=up[k-1][ up[k-1][i] ];
      mn[k][i]=min(mn[k-1][i], mn[k-1][ up[k-1][i] ]);
    }

  auto minPath = [&](int u,int r){
    ll ans=INF;
    for(int k=LG-1;k>=0;k--){
      int v=up[k][u];
      if(v && inside(r,v)){
        ans=min(ans,mn[k][u]);
        u=v;
      }
    }
    return min(ans,mag[r]);
  };

  while(q--){
    int e,r;
    cin >> e >> r;
    int x=low[e];

    if(!inside(x,r)){
      cout << "escaped\n";
      continue;
    }

    ll t=minPath(r,x);
    if(t>=INF/2) cout << "oo\n";
    else cout << d[r]+t << "\n";
  }
}
