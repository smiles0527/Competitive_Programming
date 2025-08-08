#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node{ ll mn,lz; int idx; };
vector<Node> st;
int N,Q;
void build(int p,int l,int r, vector<ll>& ps){
    if(l==r){
        st[p].mn=ps[l];
        st[p].idx=l;
        return;
    }
    int m=(l+r)>>1;
    build(p<<1,l,m,ps);
    build(p<<1|1,m+1,r,ps);
    if(st[p<<1].mn<=st[p<<1|1].mn){
        st[p].mn=st[p<<1].mn;
        st[p].idx=st[p<<1].idx;
    } else {
        st[p].mn=st[p<<1|1].mn;
        st[p].idx=st[p<<1|1].idx;
    }
}
inline void apply(int p,ll v){
    st[p].mn+=v;
    st[p].lz+=v;
}
inline void push(int p){
    if(st[p].lz){
        apply(p<<1,st[p].lz);
        apply(p<<1|1,st[p].lz);
        st[p].lz=0;
    }
}
void upd(int p,int l,int r,int ql,int qr,ll v){
    if(ql>r||qr<l) return;
    if(ql<=l&&r<=qr){
        apply(p,v);
        return;
    }
    push(p);
    int m=(l+r)>>1;
    upd(p<<1,l,m,ql,qr,v);
    upd(p<<1|1,m+1,r,ql,qr,v);
    if(st[p<<1].mn<=st[p<<1|1].mn){
        st[p].mn=st[p<<1].mn;
        st[p].idx=st[p<<1].idx;
    } else {
        st[p].mn=st[p<<1|1].mn;
        st[p].idx=st[p<<1|1].idx;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N>>Q;
    vector<int>B(N);
    ll s=0;
    for(int i=0;i<N;i++){cin>>B[i];s+=B[i];}
    vector<pair<int,int>> ops(Q);
    for(int i=0;i<Q;i++) cin>>ops[i].first>>ops[i].second;
    if(s!=N-1){
        for(int i=0;i<=Q;i++) cout<<"0 0\n";
        return 0;
    }
    vector<ll>D(N);
    for(int i=0;i<N;i++) D[i]= (ll)B[i]-1;
    vector<ll> PS(N+1);
    for(int i=1;i<=N;i++) PS[i]=PS[i-1]+D[i-1];
    st.assign(4*(N+1), {});
    build(1,1,N,PS);
    auto answer=[&](){
        int id=st[1].idx;
        int k = (id==N?0:id);
        cout<<"1 "<<k<<"\n";
    };
    answer();
    for(auto &op:ops){
        int x=op.first, y=op.second;
        ll dx=D[x], dy=D[y];
        ll delta=dy-dx;
        if(delta){
            upd(1,1,N,x+1,N,delta);
            upd(1,1,N,y+1,N,-delta);
        }
        swap(B[x],B[y]);
        swap(D[x],D[y]);
        answer();
    }
    return 0;
}
