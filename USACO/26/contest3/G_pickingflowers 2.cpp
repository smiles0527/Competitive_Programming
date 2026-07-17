#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m,k,l; cin>>n>>m>>k>>l;
    vector<int> s(k),t(l);
    for(int &x:s) cin>>x;
    for(int &x:t) cin>>x;

    vector<vector<int>> g(n+1);
    while(m--){
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> d(n+1,-1),o;
    queue<int> q;
    d[1]=0,q.push(1);
    while(q.size()){
        int u=q.front(); q.pop();
        o.push_back(u);
        for(int v:g[u]) if(d[v]<0)
            d[v]=d[u]+1,q.push(v);
    }

    vector<int> f(n);
    int mx=0;
    for(int x:s){
        int h=d[x];
        mx=max(mx,h);
        if(f[h]){
            cout<<string(n-1,'0')<<"\n";
            return;
        }
        f[h]=x;
    }

    vector<char> a(n+1),b(n+1);
    a[1]=1;

    for(int u:o) if(a[u])
        for(int v:g[u]) if(d[v]==d[u]+1)
            if(!f[d[v]]||f[d[v]]==v) a[v]=1;

    for(int x:t)
        if(d[x]>mx||x==f[mx]) b[x]=1;

    for(int i=n-1;i>=0;i--){
        int u=o[i];
        for(int v:g[u]) if(d[v]==d[u]+1&&b[v])
            if(!f[d[v]]||f[d[v]]==v) b[u]=1;
    }

    for(int i=2;i<=n;i++) cout<<(a[i]&&b[i]);
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin>>T;
    while(T--) solve();
}