#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> sumS, sumR, lazyAddS, lazyK;
    SegTree(int n): n(n), sumS(4*n+4), sumR(4*n+4), lazyAddS(4*n+4), lazyK(4*n+4) {}
    void build(int idx, int l, int r, const vector<long long>& a){
        if(l==r){ sumS[idx]=a[l]; return; }
        int m=(l+r)>>1, lc=idx<<1, rc=lc|1;
        build(lc,l,m,a); build(rc,m+1,r,a);
        pull(idx);
    }
    void pull(int idx){
        int lc=idx<<1, rc=lc|1;
        sumS[idx]=sumS[lc]+sumS[rc];
        sumR[idx]=sumR[lc]+sumR[rc];
    }
    void applyAddS(int idx, int len, long long x){
        sumS[idx]+=x*len;
        sumR[idx]+=x*lazyK[idx]*len;
        lazyAddS[idx]+=x;
    }
    void applyK(int idx){
        sumR[idx]+=sumS[idx];
        lazyK[idx]+=1;
    }
    void push(int idx, int l, int r){
        if(l==r) return;
        int lc=idx<<1, rc=lc|1;
        int m=(l+r)>>1, llen=m-l+1, rlen=r-m;
        if(lazyK[idx]){
            long long k=lazyK[idx];
            sumR[lc]+=k*sumS[lc]; lazyK[lc]+=k;
            sumR[rc]+=k*sumS[rc]; lazyK[rc]+=k;
            lazyK[idx]=0;
        }
        if(lazyAddS[idx]){
            long long a=lazyAddS[idx];
            sumS[lc]+=a*llen; sumR[lc]+=a*lazyK[lc]*llen; lazyAddS[lc]+=a;
            sumS[rc]+=a*rlen; sumR[rc]+=a*lazyK[rc]*rlen; lazyAddS[rc]+=a;
            lazyAddS[idx]=0;
        }
    }
    void updAddS(int idx, int l, int r, int ql, int qr, long long x){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ applyAddS(idx,r-l+1,x); return; }
        push(idx,l,r);
        int m=(l+r)>>1, lc=idx<<1, rc=lc|1;
        updAddS(lc,l,m,ql,qr,x); updAddS(rc,m+1,r,ql,qr,x);
        pull(idx);
    }
    void updK(int idx, int l, int r, int ql, int qr){
        if(qr<l||r<ql) return;
        if(ql<=l&&r<=qr){ applyK(idx); return; }
        push(idx,l,r);
        int m=(l+r)>>1, lc=idx<<1, rc=lc|1;
        updK(lc,l,m,ql,qr); updK(rc,m+1,r,ql,qr);
        pull(idx);
    }
    void collect(int idx, int l, int r, vector<long long>& out){
        if(l==r){ out[l]=sumR[idx]; return; }
        push(idx,l,r);
        int m=(l+r)>>1, lc=idx<<1, rc=lc|1;
        collect(lc,l,m,out); collect(rc,m+1,r,out);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q;
    if(!(cin>>N>>Q)) return 0;
    vector<long long> a(N+1);
    for(int i=1;i<=N;i++) cin>>a[i];
    SegTree st(N);
    st.build(1,1,N,a);
    for(int q=0;q<Q;q++){
        int t; cin>>t;
        if(t==1){
            int l,r; long long x; cin>>l>>r>>x;
            st.updAddS(1,1,N,l,r,x);
        }else{
            int l,r; cin>>l>>r;
            st.updK(1,1,N,l,r);
        }
    }
    vector<long long> ans(N+1);
    st.collect(1,1,N,ans);
    for(int i=1;i<=N;i++){
        if(i>1) cout<<' ';
        cout<<ans[i];
    }
    cout<<"\n";
    return 0;
}
