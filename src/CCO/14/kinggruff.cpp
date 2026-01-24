#include <bits/stdc++.h>
using namespace std;

struct PR {
    struct E { int v; long long c; int r; };
    int n,s,t;
    vector<vector<E>> g;
    vector<long long> ex;
    vector<int> h,ct,cur;
    vector<char> inq;
    queue<int> q;
    PR(int n): n(n), g(n), ex(n), h(n), ct(2*n+5), cur(n), inq(n,0) {}
    void ae(int u,int v,long long c){
        E a{v,c,(int)g[v].size()}, b{u,0,(int)g[u].size()};
        g[u].push_back(a); g[v].push_back(b);
    }
    void enq(int v){
        if(!inq[v] && v!=s && v!=t && ex[v]>0){ inq[v]=1; q.push(v); }
    }
    void push(int u,E &e){
        if(e.c==0 || h[u]!=h[e.v]+1) return;
        long long f=min(ex[u], e.c);
        e.c-=f; g[e.v][e.r].c+=f;
        ex[u]-=f; ex[e.v]+=f;
        enq(e.v);
    }
    void rel(int u){
        int mh=INT_MAX;
        for(auto &e:g[u]) if(e.c>0) mh=min(mh,h[e.v]);
        int oh=h[u];
        int nh=(mh==INT_MAX?2*n:mh+1);
        h[u]=nh; ct[oh]--; ct[nh]++;
        if(ct[oh]==0){
            for(int v=0; v<n; ++v) if(v!=s && v!=t && h[v]>oh && h[v]<n+1){
                ct[h[v]]--; h[v]=n+1; ct[h[v]]++; enq(v);
            }
        }
        cur[u]=0;
    }
    long long flow(int S,int T){
        s=S; t=T;
        ct[0]=n-1; ct[n]=1;
        h[s]=n; h[t]=0;
        for(auto &e:g[s]){
            if(e.c>0){
                long long f=e.c;
                e.c-=f; g[e.v][e.r].c+=f;
                ex[e.v]+=f; enq(e.v);
            }
        }
        while(!q.empty()){
            int u=q.front(); q.pop(); inq[u]=0;
            while(ex[u]>0){
                if(cur[u]==(int)g[u].size()){
                    rel(u);
                    if(h[u]>=2*n) break;
                }else{
                    push(u,g[u][cur[u]]);
                    if(g[u][cur[u]].c==0) cur[u]++;
                }
            }
        }
        return ex[t];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,a,b; 
    if(!(cin>>n>>m>>a>>b)) return 0;
    --a; --b;

    struct R{int x,y; long long l,c;};
    vector<vector<pair<int,long long>>> g1(n), g2(n);
    vector<R> es(m);
    for(int i=0;i<m;i++){
        int x,y; long long l,c;
        cin>>x>>y>>l>>c; --x; --y;
        es[i]={x,y,l,c};
        g1[x].push_back({y,l});
        g2[y].push_back({x,l});
    }

    const long long INF= (1LL<<62);
    auto dij=[&](int s,const vector<vector<pair<int,long long>>>& G){
        vector<long long> d(n,INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        d[s]=0; pq.push({0,s});
        while(!pq.empty()){
            auto [du,u]=pq.top(); pq.pop();
            if(du!=d[u]) continue;
            for(auto [v,w]:G[u]){
                if(d[v]>du+w){ d[v]=du+w; pq.push({d[v],v}); }
            }
        }
        return d;
    };

    vector<long long> d1=dij(a,g1), d2=dij(b,g2);

    int qn; cin>>qn;
    while(qn--){
        long long D; cin>>D;
        PR pr(n);
        for(auto &e:es){
            if(d1[e.x]==INF || d2[e.y]==INF) continue;
            if(d1[e.x]+e.l+d2[e.y]<=D) pr.ae(e.x,e.y,e.c);
        }
        cout<<pr.flow(a,b)<<'\n';
    }
    return 0;
}
