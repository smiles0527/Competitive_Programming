#include<bits/stdc++.h>
using namespace std;

struct Edge{int id,to;};

vector<Edge> G[200005];
int ans[200005];
bool vis[200005];

void dfs(int u,int col){
    vis[u]=true;
    for(auto e:G[u]){
        if(ans[e.id]!=-1) continue;   // already decided (painted or left grey)
        if(vis[e.to]) continue;       // leave this road grey
        ans[e.id]=col;               // paint it
        dfs(e.to,col^1);             // alternate colour
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    cin>>N>>M;
    for(int i=1;i<=M;++i){
        int X,Y;cin>>X>>Y;
        G[X].push_back({i,Y});
        G[Y].push_back({i,X});       //connect other edn
        ans[i]=-1;                   // mark grey by default
    }

    for(int i=1;i<=N;++i)
        if(!vis[i]) dfs(i,1);        // start with red

    for(int i=1;i<=M;++i)
        cout<<(ans[i]==-1?'G':ans[i]==0?'B':'R');
    return 0;
}
