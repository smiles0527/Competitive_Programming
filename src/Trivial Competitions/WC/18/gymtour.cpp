#include <bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N,K,F;
  cin>>N>>K>>F;
  vector<int> gym(K);
  for(int i=0;i<K;i++)cin>>gym[i];
  vector<vector<int>> adj(N+1);
  for(int i=1;i<N;i++){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> parent(N+1),dist(N+1);
  vector<int> bfs;
  bfs.reserve(N);
  queue<int> q;
  q.push(1);
  parent[1]=0;
  dist[1]=0;
  while(!q.empty()){
    int u=q.front();q.pop();
    bfs.push_back(u);
    for(int v:adj[u])if(v!=parent[u]){
      parent[v]=u;
      dist[v]=dist[u]+1;
      q.push(v);
    }
  }
  vector<char> onPath(N+1,0);
  for(int x=F;x;x=parent[x])onPath[x]=1;
  vector<char> isGym(N+1,0),isRem(N+1,0);
  for(int g:gym){
    isGym[g]=1;
    if(!onPath[g])isRem[g]=1;
  }
  vector<int> mark(N+1),markRem(N+1);
  for(int i=N-1;i>=0;i--){
    int v=bfs[i];
    mark[v]+=isGym[v];
    markRem[v]+=isRem[v];
    if(v!=1){
      mark[parent[v]]+=mark[v];
      markRem[parent[v]]+=markRem[v];
    }
  }
  long long edgesAll=0,edgesRem=0,md=0;
  for(int v=2;v<=N;v++){
    if(mark[v]>0)edgesAll++;
    if(markRem[v]>0 && !onPath[v])edgesRem++;
  }
  for(int g:gym) md=max<long long>(md,dist[g]);
  long long withoutD=2*edgesAll-md;
  long long withD=dist[F]+edgesRem;
  cout<<min(withoutD,withD)<<"\n";
  return 0;
}
