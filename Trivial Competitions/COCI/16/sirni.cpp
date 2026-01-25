#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 1<<19;
constexpr int MAXM = 10000000+5;
vector<pair<int,int>> V[MAXM];
int p[MAXN], naj[MAXM], bio[MAXM], id[MAXM], root_arr[MAXN], rnk[MAXN];
int find_set(int x){ return root_arr[x]==-1?x:root_arr[x]=find_set(root_arr[x]); }
bool merge_set(int a,int b){
    a=find_set(a); b=find_set(b);
    if(a==b) return false;
    if(rnk[a]>rnk[b]) root_arr[b]=a;
    else if(rnk[b]>rnk[a]) root_arr[a]=b;
    else{ rnk[a]++; root_arr[b]=a; }
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    memset(naj,0,sizeof naj);
    memset(bio,0,sizeof bio);
    memset(id,-1,sizeof id);
    for(int i=0;i<n;i++){
        cin>>p[i];
        naj[p[i]]=p[i];
        if(id[p[i]]<0) id[p[i]]=i;
    }
    for(int v=MAXM-2;v>=0;--v) if(!naj[v]) naj[v]=naj[v+1];
    for(int i=0;i<n;i++){
        int x=p[i];
        if(bio[x]++) continue;
        int y=(x+1<MAXM?naj[x+1]:0);
        if(y&&(2LL*x>=MAXM||naj[2*x]!=y)) V[y-x].emplace_back(i,id[y]);
        for(long long j=2LL*x;j<MAXM&&naj[j];j+=x){
            int z=naj[j];
            if(j+x<MAXM&&naj[j+x]==z) continue;
            V[z-j].emplace_back(i,id[z]);
        }
    }
    memset(root_arr,-1,sizeof root_arr);
    memset(rnk,0,sizeof rnk);
    ll ans=0;
    for(int w=0;w<MAXM;w++){
        for(auto &e:V[w]){
            if(merge_set(e.first,e.second)) ans+=w;
        }
    }
    cout<<ans;
    return 0;

    
}
