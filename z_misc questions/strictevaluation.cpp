#include <bits/stdc++.h>
using namespace std; using ll=long long;
struct ST{
    int n; vector<ll> mn,add,setv; vector<uint8_t> has;
    ST(int n):n(n),mn(4*n+5),add(4*n+5),setv(4*n+5),has(4*n+5){}
    void build(int i,int l,int r,const vector<ll>&a){
        if(l==r){ mn[i]=a[l]; return; }
        int m=(l+r)>>1;
        build(i<<1,l,m,a); build(i<<1|1,m+1,r,a);
        mn[i]=min(mn[i<<1],mn[i<<1|1]);
    }
    void app_add(int i,ll v){ mn[i]+=v; if(has[i]) setv[i]+=v; else add[i]+=v; }
    void app_set(int i,ll v){ mn[i]=v; setv[i]=v; add[i]=0; has[i]=1; }
    void push(int i){
        if(has[i]){
            app_set(i<<1,setv[i]); app_set(i<<1|1,setv[i]);
            has[i]=0;
        }
        if(add[i]){
            app_add(i<<1,add[i]); app_add(i<<1|1,add[i]);
            add[i]=0;
        }
    }
    void upd_add(int i,int l,int r,int ql,int qr,ll v){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ app_add(i,v); return; }
        push(i); int m=(l+r)>>1;
        upd_add(i<<1,l,m,ql,qr,v); upd_add(i<<1|1,m+1,r,ql,qr,v);
        mn[i]=min(mn[i<<1],mn[i<<1|1]);
    }
    void upd_set(int i,int l,int r,int ql,int qr,ll v){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ app_set(i,v); return; }
        push(i); int m=(l+r)>>1;
        upd_set(i<<1,l,m,ql,qr,v); upd_set(i<<1|1,m+1,r,ql,qr,v);
        mn[i]=min(mn[i<<1],mn[i<<1|1]);
    }
    ll qry(int i,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return (ll)4e18;
        if(ql<=l&&r<=qr) return mn[i];
        push(i); int m=(l+r)>>1;
        return min(qry(i<<1,l,m,ql,qr),qry(i<<1|1,m+1,r,ql,qr));
    }
};
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N,Q; if(!(cin>>N>>Q)) return 0;
    vector<ll>a(N+1); for(int i=1;i<=N;i++) cin>>a[i];
    ST st(N); st.build(1,1,N,a);
    while(Q--){
        int t,l,r; cin>>t>>l>>r;
        if(t==1){ ll v; cin>>v; st.upd_add(1,1,N,l,r,v); }
        else if(t==2){ ll v; cin>>v; st.upd_set(1,1,N,l,r,v); }
        else{ cout<<st.qry(1,1,N,l,r)<<"\n"; }
    }
    return 0;
}
