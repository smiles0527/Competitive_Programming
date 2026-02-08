#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

vector<vector<ll>> DP;
string initial=" ";
vector<vector<int>> graph;
vector<ll> costs;

ll dfs(int current,int previous,int state){
    ll &res=DP[current][state];
    if(res!=-1) return res;

    vector<int> ch;
    for(int v:graph[current]) if(v!=previous) ch.push_back(v);

    if(state==0){
        ll sum=0;
        for(int v:ch) sum+=dfs(v,current,1);
        return res=sum;
    }

    if(state==2){
        ll base=0,need=INF;
        for(int v:ch){
            ll a=dfs(v,current,1), b=dfs(v,current,2);
            ll m=min(a,b);
            base+=m;
            need=min(need,b-m);
        }
        if(initial[current]=='Y') return res=costs[current]+base;
        if(need>=INF) return res=INF;
        return res=costs[current]+base+need;
    }

    ll base=0,need=INF;
    for(int v:ch){
        ll a=dfs(v,current,1), b=dfs(v,current,2);
        ll m=min(a,b);
        base+=m;
        need=min(need,b-m);
    }

    if(initial[current]=='Y') return res=base;
    if(need>=INF) return res=INF;
    return res=base+need;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin>>N;
    graph.resize(N+1);
    costs.resize(N+1);
    DP.assign(N+1,vector<ll>(3,-1));

    for(int i=0,a,b;i<N-1;i++){
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    string s; cin>>s; initial+=s;
    for(int i=1;i<=N;i++) cin>>costs[i];

    cout<<dfs(1,-1,1)<<"\n";
    return 0;
}
