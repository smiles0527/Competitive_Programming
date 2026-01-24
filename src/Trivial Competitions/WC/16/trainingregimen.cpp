#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    int c;
};

struct DSU {
    vector<int> p, r;
    vector<ll> mn;
    DSU(int n, const vector<ll>& T): p(n+1), r(n+1,0), mn(n+1) {
        for(int i=1;i<=n;i++){
            p[i]=i;
            mn[i]=T[i];
        }
    }
    int find(int x){
        return p[x]==x?x:p[x]=find(p[x]);
    }
    void unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b) return;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        mn[a]=min(mn[a], mn[b]);
        if(r[a]==r[b]) r[a]++;
    }
    ll getMin(int x){
        return mn[find(x)];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<ll> T(N+1);
    for(int i=1;i<=N;i++){
        cin >> T[i];
    }

    if(N==1){
        cout << 0 << "\n";
        return 0;
    }

    vector<Edge> edges;
    edges.reserve(M);
    for(int i=0;i<M;i++){
        int a,b,c;
        cin >> a >> b >> c;
        edges.push_back({a,b,c});
    }

    sort(edges.begin(), edges.end(),
         [](auto &A, auto &B){ return A.c < B.c; });

    DSU dsu(N, T);
    ll currentBest = T[1];
    ll trainingCost = 0;
    int prevLevel = 1;
    ll answer = -1;

    int idx = 0;
    while(idx < M){
        int lvl = edges[idx].c;
        // train from prevLevel up to lvl
        trainingCost += ll(lvl - prevLevel) * currentBest;
        prevLevel = lvl;

        // unlock all edges with requirement == lvl
        while(idx < M && edges[idx].c == lvl){
            dsu.unite(edges[idx].u, edges[idx].v);
            ++idx;
        }

        currentBest = dsu.getMin(1);
        // check if town N is now reachable
        if(dsu.find(1) == dsu.find(N)){
            answer = trainingCost;
            break;
        }
    }

    if(answer < 0) {
        cout << -1 << "\n";
    } else {
        cout << answer << "\n";
    }

    return 0;
}
