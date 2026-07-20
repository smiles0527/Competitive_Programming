#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

int n, m;
ll A, B;
struct E { int to; ll w; };
vector<vector<E>> adj;
vector<array<ll,3>> edges;

lll g128(lll a, lll b){ if(a<0)a=-a; if(b<0)b=-b; while(b){ lll t=a%b; a=b; b=t; } return a; }
string s128(lll x){ if(x==0) return "0"; string s; while(x>0){ s+=char('0'+(int)(x%10)); x/=10; } reverse(s.begin(),s.end()); return s; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> A >> B;            // A = V_R, B = V_S
    adj.assign(n+1, {});
    edges.reserve(m);
    for(int i=0;i<m;i++){
        int a,b; ll w; cin >> a >> b >> w;
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
        edges.push_back({(ll)a,(ll)b,w});
    }

    const ll INF = (ll)4e18;
    vector<ll> dT(n+1), phi(n+1);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;

    string out;
    out.reserve(1<<20);

    for(int T=2;T<=n;T++){
        for(int i=1;i<=n;i++) dT[i]=INF;
        dT[T]=0; pq.push({0,T});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>dT[u]) continue;
            for(auto&e:adj[u]){ ll nd=d+e.w; if(nd<dT[e.to]){ dT[e.to]=nd; pq.push({nd,e.to}); } }
        }

        for(int i=1;i<=n;i++) phi[i]=INF;
        phi[1]=0; pq.push({0,1});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>phi[u]) continue;
            ll gu=dT[u]*A;
            if(d>=gu) continue;              // tie/caught at u -> record but never relay
            for(auto&e:adj[u]){
                int v=e.to;
                ll cand=d+e.w*B;
                ll gv=dT[v]*A;
                if(cand<=gv && cand<phi[v]){ phi[v]=cand; pq.push({cand,v}); }
            }
        }

        lll bnum=0, bden=1;
        for(int v=1;v<=n;v++) if(phi[v]!=INF){          // strategy 1: stay
            lll num=(lll)dT[v]*A;
            if(num*bden>bnum*1){ bnum=num; bden=1; }
        }
        for(auto&ed:edges){                              // strategy 2: walk onto an edge
            int U=(int)ed[0], V=(int)ed[1]; ll w=ed[2];
            for(int s=0;s<2;s++){
                int e=s?V:U, o=s?U:V;
                if(phi[e]==INF) continue;
                if(phi[e]>=dT[e]*A) continue;            // must be strictly ahead to step out
                ll de=dT[e], od=dT[o];
                lll num, den;
                bool rp = (B<=A) || ( (lll)2*phi[e] + (lll)(od-de+w)*B <= (lll)(de+od+w)*A );
                if(rp){ num=(lll)(de+od+w)*A; den=2; }
                else  { num=(lll)A*((lll)de*B - phi[e]); den=(lll)(B-A); }
                if(num*bden > bnum*den){ bnum=num; bden=den; }
            }
        }

        lll rn=bnum, rd=bden*A*B;
        lll gg=g128(rn,rd); if(gg==0)gg=1;
        rn/=gg; rd/=gg;
        out += s128(rn); out += '/'; out += s128(rd); out += '\n';
    }
    cout << out;
    return 0;
}