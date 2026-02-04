#include <bits/stdc++.h>
using namespace std;

struct Node{
    long long q;
    int id;
    bool operator<(Node const& o) const { return q < o.q; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N,A,B,C,T;
    int M,K;
    cin>>N>>M>>K;
    cin>>A>>B>>C;
    cin>>T;
    vector<long long> S(M+1);
    for(int i=1;i<=M;i++) cin>>S[i];

    int rM=0;
    for(int i=1;i<=M;i++){
        __int128 tt=(__int128)(S[i]-1)*B;
        if(tt<=T) rM=i;
        else break;
    }
    if(rM==0){ cout<<0<<"\n"; return 0; }

    long long base=0;
    base += (rM-1);

    int segs=min(M-1,rM);
    vector<long long> L(segs+1), R(segs+1), tL(segs+1), cur(segs+1);

    auto clampmin = [&](long long x, long long y){ return x<y?x:y; };
    auto clampmax = [&](long long x, long long y){ return x>y?x:y; };
    auto cap128 = [&]( __int128 x, long long lo, long long hi){
        if(x<(__int128)lo) return lo;
        if(x>(__int128)hi) return hi;
        return (long long)x;
    };

    priority_queue<Node> pq;
    // overflow??
    auto push_first = [&](int id){
        long long l=L[id], r=R[id], tl=tL[id];

        // cur[id] = farthest reachable station index within [l, r)
        // without spending any extra semiexpress stop in this segment:
        // from l (a mandatory stop), ride local (A) to the right.
        if(tl>T){ cur[id]=l; return; }
        __int128 i0=(__int128)l + ((__int128)T - (__int128)tl)/A;
        long long i0c=cap128(i0, l, r-1);
        cur[id]=i0c;
        base += (cur[id] - l);

        // spending 1 extra stop: put it at s = cur+1 (first currently-unreachable station).
        // then time to s becomes tl + (s-l)*C (semiexpress from l to s).
        // after that, use local (A) to cover further stations.
        long long s=cur[id]+1;
        if(s>=r) return;
        __int128 ts=(__int128)tl + (__int128)(s-l)*C;
        if(ts>T) return;
        __int128 last=(__int128)s + (((__int128)T - ts)/A);
        long long lastc=cap128(last, s, r-1);
        long long q=lastc - cur[id];
        if(q>0) pq.push({q,id});
    };

    auto advance_seg = [&](int id){
        long long l=L[id], r=R[id], tl=tL[id];
        long long i=cur[id];
        long long s=i+1;
        if(s>=r) return;
        __int128 ts=(__int128)tl + (__int128)(s-l)*C;
        if(ts>T) return;
        __int128 last=(__int128)s + (((__int128)T - ts)/A);
        long long lastc=cap128(last, s, r-1);
        if(lastc<=i) return;
        cur[id]=lastc;

        long long s2=cur[id]+1;
        if(s2>=r) return;
        __int128 ts2=(__int128)tl + (__int128)(s2-l)*C;
        if(ts2>T) return;
        __int128 last2=(__int128)s2 + (((__int128)T - ts2)/A);
        long long last2c=cap128(last2, s2, r-1);
        long long q=last2c - cur[id];
        if(q>0) pq.push({q,id});
    };

    for(int i=1;i<=segs;i++){
        L[i]=S[i];
        R[i]=S[i+1];
        tL[i]=(long long)((__int128)(L[i]-1)*B);
        push_first(i);
    }

    int extra=K-M;
    long long add=0;

    while(extra>0 && !pq.empty()){
        auto nd=pq.top(); pq.pop();
        if(nd.q<=0) break;
        add += nd.q;
        extra--;
        advance_seg(nd.id);
    }

    long long ans=base+add;
    if(ans>N-1) ans=N-1;
    cout<<ans<<"\n";
    return 0;
}
